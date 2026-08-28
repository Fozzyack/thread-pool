#include "thread_handler.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *thread_function(void *args) {
    thread_handler_threadpool *pool = (thread_handler_threadpool *)args;

    while (1) {
        pthread_mutex_lock(&(pool->lock));

        // while stop is set -> halt the thread
        while (pool->queue_count == 0 && !pool->stop) {
            pthread_cond_wait(&(pool->condition), &(pool->lock));
        }

        if (pool->stop) {
            pthread_mutex_unlock(&(pool->lock));
            pthread_exit(NULL);
        }

        thread_handler_task task = pool->task_queue[pool->queue_front];
        pool->queue_front = (pool->queue_front + 1) % QUEUE_SIZE;
        pool->queue_count--;

        pthread_mutex_unlock(&(pool->lock));
        (*(task.fn))(task.arg);
    }

    return NULL;
}

// starts threads
thread_handler_status start_thread_pool(thread_handler_threadpool *pool) {
    int status;
    for (int i = 0; i < THREAD_COUNT; i++) {
        if ((status = pthread_create(&(pool->threads[i]), NULL, thread_function, pool)) != 0) {
            fprintf(stderr, "Error: pthread_create - status: %d err:%s\n", status, strerror(status));
            return THREAD_HANDLER_ERROR;
        }
    }
    return THREAD_HANDLER_OK;
}

thread_handler_status stop_thread_pool(thread_handler_threadpool *pool) {

    pthread_mutex_lock(&(pool->lock));
    pool->stop = 1;
    pthread_cond_broadcast(&(pool->condition));
    pthread_mutex_unlock(&(pool->lock));

    int status;
    for (int i = 0; i < THREAD_COUNT; i++) {
        if ((status = pthread_join(pool->threads[i], NULL)) != 0) {
            fprintf(stderr, "Error: pthread_join - status: %d err:%s\n", status, strerror(status));
            return THREAD_HANDLER_ERROR;
        }
    }
    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->condition));

    return THREAD_HANDLER_OK;
}

// Initialises thread pool
thread_handler_status init_thread_handler(thread_handler_threadpool *pool) {

    // init stop condition
    pool->stop = 0;

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
