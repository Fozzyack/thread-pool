# Thread Pool (Work in Progress)

An early-stage thread-pool implementation in C using POSIX threads. This is a
learning project and is not finished yet.

Currently, the project:

- Initializes a mutex, condition variable, and fixed-size task queue.
- Starts and joins ten threads.
- Prints `Running thread` from each thread before it exits.

Task submission, queue processing, worker loops, and cleanup are still to be
implemented.

## Build and Run

Requires GCC, GNU Make, and a POSIX-compatible system.

```sh
make
./bin/thread-pool
```

Remove build artifacts with:

```sh
make clean
```

## Layout

```text
include/thread_handler.h  Thread-pool types and declarations
src/thread_handler.c      Thread-pool implementation
src/main.c                Example program
Makefile                  Build commands
```
