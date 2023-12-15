#include "file_reader.h"

void init_queue(task_queue_t *q) {
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->cond, NULL);
}

void enqueue_task(task_queue_t *q, char *line, regex_t *regex) {
    regex_task_t *new_task = malloc(sizeof(regex_task_t));
    new_task->line = strdup(line);
    new_task->regex = regex;
    new_task->next = NULL;

    pthread_mutex_lock(&q->lock);
    if (q->tail) {
        q->tail->next = new_task;
    } else {
        q->head = new_task;
    }
    q->tail = new_task;

    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->lock);
}

void enqueue_sentinel(task_queue_t *q) {
    regex_task_t *sentinel_task = malloc(sizeof(regex_task_t));
    sentinel_task->line = NULL;  
    sentinel_task->next = NULL;

    pthread_mutex_lock(&q->lock);
    if (q->tail) {
        q->tail->next = sentinel_task;
    } else {
        q->head = sentinel_task;
    }
    q->tail = sentinel_task;
    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->lock);
}

regex_task_t* dequeue(task_queue_t *q) {
    pthread_mutex_lock(&q->lock);
    while (q->head == NULL) {
        pthread_cond_wait(&q->cond, &q->lock);
    }

    regex_task_t *task = q->head;
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    pthread_mutex_unlock(&q->lock);
    return task;
}


// Thread execution to get matches for each line
void *worker_thread(void *arg) {
    task_queue_t *queue = (task_queue_t *)arg;
    while (1) {
        regex_task_t *task = dequeue(queue);
        if (task == NULL || task->line == NULL) {  
            free(task);
            break;
        }

        int offset = 0;
        regmatch_t match_t[1];

        while (regexec(task->regex, task->line + offset, 1, match_t, 0) == 0) {
            if (match_t[0].rm_so != (size_t) - 1) {
                int start = offset + match_t[0].rm_so;
                int end = offset + match_t[0].rm_eo;
                printf("Match found at position %d to %d: %.*s\n", start, end, end - start, &task->line[start]);
                offset += match_t[0].rm_eo;
            } else {
                break;
            }
        }

        free(task->line);
        free(task); 
    }

    return NULL;
}

void match_lines_file(char *filePath, char *regexPattern) {

    regex_t regex;
    int ret;

    ret = regcomp(&regex, regexPattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    FILE *file;
    char line[1024];

    file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    task_queue_t q;
    init_queue(&q);
    
    const int NUM_THREADS = get_number_of_cores();
    pthread_t workers[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&workers[i], NULL, worker_thread, &q);
    }

    while (fgets(line, sizeof(line), file)) {
        enqueue_task(&q, line, &regex);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        enqueue_sentinel(&q);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(workers[i], NULL);
    }
    
    regfree(&regex);

    fclose(file);
}