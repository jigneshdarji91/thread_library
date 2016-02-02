CC = gcc
CFLAGS = -g -O0
INCLUDE_DIR = include/
TEST_DIR = .
SRC_DIR = .
LIB_DIR = .
FILES = $(SRC_DIR)/context.c $(SRC_DIR)/queue.c $(SRC_DIR)/thread.c $(SRC_DIR)/semaphore.c $(SRC_DIR)/mythread.c

default: library

thread_test: one ping passing tree

sem_test: sem_one sem_ping sem_passing sem_passing_2

one: 
	$(CC) -o one.o $(TEST_DIR)/one.c $(LIB_DIR)/mythread.a

ping: 
	$(CC) -o ping.o $(TEST_DIR)/ping.c $(LIB_DIR)/mythread.a

passing: 
	$(CC) -o passing.o $(TEST_DIR)/passing.c $(LIB_DIR)/mythread.a

tree: 
	$(CC) -o tree.o $(TEST_DIR)/tree.c $(LIB_DIR)/mythread.a

sem_one: 
	$(CC) -o sem_test_one.o $(TEST_DIR)/sem_test_one.c $(LIB_DIR)/mythread.a

sem_ping: 
	$(CC) -o sem_test_ping.o $(TEST_DIR)/sem_test_ping.c $(LIB_DIR)/mythread.a

sem_passing: 
	$(CC) -o sem_test_passing.o $(TEST_DIR)/sem_test_passing.c $(LIB_DIR)/mythread.a

sem_passing_2: 
	$(CC) -o sem_test_passing_2.o $(TEST_DIR)/sem_test_passing_2.c $(LIB_DIR)/mythread.a

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
