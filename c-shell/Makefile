CC = gcc
CFLAGS = -std=c23 \
         -D_POSIX_C_SOURCE=200809L \
         -D_XOPEN_SOURCE=700 \
         -Wall -Wextra -Werror \
         -Wno-unused-parameter \
         -fno-asm \
         -Iinclude

SRC_DIR = src
INC_DIR = include
TARGET = shell.out

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, %.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean