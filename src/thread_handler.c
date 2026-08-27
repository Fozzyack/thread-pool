

#include "thread_handler.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

thread_handler_status init_thread_handler(thread_handler_threadpool *pool) {

    // init queue
    pool->queue_count = 0;
    pool->queue_front = 0;
    pool->queue_back = 0;

    int status;
    if ((status = pthread_mutex_init(&(pool->lock), NULL)) != 0) {
        fprintf(stderr, "Error: pthread_mutex_init - status: %d err:%s\n", status, strerror(status));
        return THREAD_HANDLER_ERROR;
    }
    if ((status = pthread_cond_init(&(pool->condition), NULL)) != 0) {
        fprintf(stderr, "Error: pthread_mutex_init - status: %d err:%s\n", status, strerror(status));
        return THREAD_HANDLER_ERROR;
    }

    return THREAD_HANDLER_OK;
}
