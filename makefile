CC = gcc
CFLAGS = -g -O0
INCLUDE_DIR = include/
TEST_DIR = test
SRC_DIR = src
LIB_DIR = lib
FILES = $(SRC_DIR)/context.c $(SRC_DIR)/queue.c $(SRC_DIR)/thread.c $(SRC_DIR)/semaphore.c $(SRC_DIR)/mythread.c

default: one ping passing tree 

one: 
	$(CC) -o one.o $(TEST_DIR)/one.c $(LIB_DIR)/mythread.a

ping: $(TEST_DIR)/ping.c $(FILES)
	$(CC) $(CFLAGS) -o ping.o $(TEST_DIR)/ping.c $(FILES) -I$(INCLUDE_DIR) 

passing: $(TEST_DIR)/passing.c $(FILES)
	$(CC) $(CFLAGS) -o passing.o $(TEST_DIR)/passing.c $(FILES) -I$(INCLUDE_DIR) 

tree: $(TEST_DIR)/tree.c $(FILES)
	$(CC) $(CFLAGS) -o tree.o $(TEST_DIR)/tree.c $(FILES) -I$(INCLUDE_DIR) 

library: 
	#$(CC) $(CFLAGS) -c $(SRC_DIR)/queue.c  -I$(INCLUDE_DIR) 
	#$(CC) $(CFLAGS) -c $(SRC_DIR)/context.c -I$(INCLUDE_DIR) 
	#$(CC) $(CFLAGS) -c $(SRC_DIR)/thread.c -I$(INCLUDE_DIR) 
	#$(CC) $(CFLAGS) -c $(SRC_DIR)/semaphore.c -I$(INCLUDE_DIR) 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mythread.c -I$(INCLUDE_DIR) 
	#ar rcs $(LIB_DIR)/mythread.a queue.o context.o thread.o semaphore.o mythread.o
	ar rcs $(LIB_DIR)/mythread.a mythread.o
	#rm queue.o context.o thread.o semaphore.o mythread.o
	rm mythread.o

clean:
	rm -f *.o
