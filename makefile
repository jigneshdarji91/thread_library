CC = gcc
CFLAGS = -g -O0
INCLUDE_DIR = include/
TEST_DIR = .
SRC_DIR = .
LIB_DIR = .
FILES = $(SRC_DIR)/context.c $(SRC_DIR)/queue.c $(SRC_DIR)/thread.c $(SRC_DIR)/semaphore.c $(SRC_DIR)/mythread.c

default: library

library: 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/queue.c  -I$(INCLUDE_DIR) 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/context.c -I$(INCLUDE_DIR) 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/thread.c -I$(INCLUDE_DIR) 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/semaphore.c -I$(INCLUDE_DIR) 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mythread.c -I$(INCLUDE_DIR) 
	ar rcs $(LIB_DIR)/mythread.a queue.o context.o thread.o semaphore.o mythread.o
	rm queue.o context.o thread.o semaphore.o mythread.o

clean:
	rm -f *.o
	rm -f *.a
