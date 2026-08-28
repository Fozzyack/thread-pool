#ifndef THEAD_HANDLER_H
#define THEAD_HANDLER_H

#include <pthread.h>

#define THREAD_COUNT 10
#define QUEUE_SIZE 100

typedef enum {
    THREAD_HANDLER_OK,
    THREAD_HANDLER_ERROR,
} thread_handler_status;

typedef struct {
    void (*fn)(void *arg);
    void *arg;
} thread_handler_task;

typedef struct {

    pthread_mutex_t lock;
    pthread_t threads[THREAD_COUNT];
    pthread_cond_t condition;
    int stop;

    thread_handler_task task_queue[QUEUE_SIZE];

    int queue_count;
    int queue_front;
    int queue_back;

} thread_handler_threadpool;

thread_handler_status init_thread_handler(thread_handler_threadpool *pool);
thread_handler_status start_thread(thread_handler_threadpool *pool);

#endif // !THEAD_HANDLER_H
