CC = gcc
CFLAGS = -g -O0
TEST_DIR = test_cases
FILES = context.c queue.c thread.c semaphore.c mythread.c

default: one ping passing tree 

one: $(TEST_DIR)/one.c $(FILES)
	$(CC) -o one.o $(TEST_DIR)/one.c $(FILES) $(CFLAGS) 

ping: $(TEST_DIR)/ping.c $(FILES)
	$(CC) $(CFLAGS) -o ping.o $(TEST_DIR)/ping.c $(FILES) 

passing: $(TEST_DIR)/passing.c $(FILES)
	$(CC) $(CFLAGS) -o passing.o $(TEST_DIR)/passing.c $(FILES) 

tree: $(TEST_DIR)/tree.c $(FILES)
	$(CC) $(CFLAGS) -o tree.o $(TEST_DIR)/tree.c $(FILES) 

library: libmythread.a
	$(CC) $(CFLAGS) -c queue.c
	$(CC) $(CFLAGS) -c context.c
	$(CC) $(CFLAGS) -c thread.c
	$(CC) $(CFLAGS) -c semaphore.c
	$(CC) $(CFLAGS) -c mythread.c
	ar -cvq libmythread.a queue.o context.o thread.o semaphore.o mythread.o
	rm queue.o context.o thread.o semaphore.o mythread.o

clean:
	rm -f *.o
