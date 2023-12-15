#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sysctl.h>

#include "../helpers/num_cores.h"

typedef struct task {
    char *path;
    char *line;
    regex_t *regex;
    struct task *next;
} regex_task_t;

typedef struct {
    regex_task_t *head;
    regex_task_t *tail;
    pthread_mutex_t lock;
    pthread_cond_t cond;

} task_queue_t;

void init_queue(task_queue_t *q);

void enqueue_task(task_queue_t *q, char *line, char *path, regex_t *regex);

regex_task_t* dequeue(task_queue_t *q);

void *worker_thread(void *arg);

void match_lines_file(char *filePath, char *regexPattern);

#endif