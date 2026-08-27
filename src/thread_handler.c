

#include "thread_handler.h"

#define THREAD_COUNT 10
#define QUEUE_SIZE 100

typedef struct {
  void (*fn)(void *arg);
  void *arg;
} thread_handler_task;

void init_thread_handler(void) {}
