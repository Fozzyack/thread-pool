
CC = gcc
CFLAGS = -std=gnu17 -Wall -Wextra -Werror -Wpedantic -pthread -Iinclude

TARGET = bin/thread-pool
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

default : $(TARGET)

clean:
	rm -rf obj/
	rm -rf bin/

$(TARGET) : $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o : src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ 
