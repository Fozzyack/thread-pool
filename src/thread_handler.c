

#include "thread_handler.h"
#include <pthread.h>

thread_handler_status init_thread_handler(thread_handler_threadpool *pool) {

  // init queue
  pool->queue_count = 0;
  pool->queue_front = 0;
  pool->queue_back = 0;

  pthread_mutex_init(&(pool->lock), NULL);
}
