

#include "thread_handler.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *thread_function(void *args) {
    (void)args;
    printf("Running thread\n");
    return NULL;
}

// starts threads
thread_handler_status start_thread(thread_handler_threadpool *pool) {
    int status;
    for (int i = 0; i < THREAD_COUNT; i++) {
        if ((status = pthread_create(&(pool->threads[i]), NULL, thread_function, pool)) != 0) {
            fprintf(stderr, "Error: pthread_create - status: %d err:%s\n", status, strerror(status));
            return THREAD_HANDLER_ERROR;
        }
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        if ((status = pthread_join(pool->threads[i], NULL)) != 0) {
            fprintf(stderr, "Error: pthread_join - status: %d err:%s\n", status, strerror(status));
            return THREAD_HANDLER_ERROR;
        }
    }
    return THREAD_HANDLER_OK;
}

// Initialises thread pool
thread_handler_status init_thread_handler(thread_handler_threadpool *pool) {

    // init queue
    pool->queue_count = 0;
    pool->queue_front = 0;
    pool->queue_back = 0;

    int status;
    // init mutex
    if ((status = pthread_mutex_init(&(pool->lock), NULL)) != 0) {
        fprintf(stderr, "Error: pthread_mutex_init - status: %d err:%s\n", status, strerror(status));
        return THREAD_HANDLER_ERROR;
    }
    // init condition
    if ((status = pthread_cond_init(&(pool->condition), NULL)) != 0) {
        fprintf(stderr, "Error: pthread_mutex_init - status: %d err:%s\n", status, strerror(status));
        return THREAD_HANDLER_ERROR;
    }

    return THREAD_HANDLER_OK;
}
