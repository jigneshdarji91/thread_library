#!/bin/bash

#-------- 0 0 
echo "--------test 1 1 0 0" 1>> tree.log 2>&1
./tree.o 1 1 0 0 1>> tree.log 2>&1

echo "--------test 5 1 0 0" 1>> tree.log 2>&1
./tree.o 5 1 0 0 1>> tree.log 2>&1

echo "--------test 1 5 0 0" 1>> tree.log 2>&1
./tree.o 1 5 0 0 1>> tree.log 2>&1

echo "--------test 5 0 0 0" 1>> tree.log 2>&1
./tree.o 5 0 0 0 1>> tree.log 2>&1

echo "--------test 10 1 0 0" 1>> tree.log 2>&1
./tree.o 10 1 0 0 1>> tree.log 2>&1

echo "--------test 50 1 0 0" 1>> tree.log 2>&1
./tree.o 50 1 0 0 1>> tree.log 2>&1

echo "--------test 10 5 0 0" 1>> tree.log 2>&1
./tree.o 10 5 0 0 1>> tree.log 2>&1

echo "--------test 50 0 0 0" 1>> tree.log 2>&1
./tree.o 50 0 0 0 1>> tree.log 2>&1

#-------- 1 0 
echo "--------test 1 1 1 0" 1>> tree.log 2>&1
./tree.o 1 1 1 0 1>> tree.log 2>&1

echo "--------test 5 1 1 0" 1>> tree.log 2>&1
./tree.o 5 1 1 0 1>> tree.log 2>&1

echo "--------test 1 5 1 0" 1>> tree.log 2>&1
./tree.o 1 5 1 0 1>> tree.log 2>&1

echo "--------test 5 0 1 0" 1>> tree.log 2>&1
./tree.o 5 0 1 0 1>> tree.log 2>&1

echo "--------test 10 1 1 0" 1>> tree.log 2>&1
./tree.o 10 1 1 0 1>> tree.log 2>&1

echo "--------test 50 1 1 0" 1>> tree.log 2>&1
./tree.o 50 1 1 0 1>> tree.log 2>&1

echo "--------test 10 5 1 0" 1>> tree.log 2>&1
./tree.o 10 5 1 0 1>> tree.log 2>&1

echo "--------test 50 0 1 0" 1>> tree.log 2>&1
./tree.o 50 0 1 0 1>> tree.log 2>&1

#-------- 0 1
echo "--------test 1 1 0 1" 1>> tree.log 2>&1
./tree.o 1 1 0 1 1>> tree.log 2>&1

echo "--------test 5 1 0 1" 1>> tree.log 2>&1
./tree.o 5 1 0 1 1>> tree.log 2>&1

echo "--------test 1 5 0 1" 1>> tree.log 2>&1
./tree.o 1 5 0 1 1>> tree.log 2>&1

echo "--------test 5 0 0 1" 1>> tree.log 2>&1
./tree.o 5 0 0 1 1>> tree.log 2>&1

echo "--------test 10 1 0 1" 1>> tree.log 2>&1
./tree.o 10 1 0 1 1>> tree.log 2>&1

echo "--------test 50 1 0 1" 1>> tree.log 2>&1
./tree.o 50 1 0 1 1>> tree.log 2>&1

echo "--------test 10 5 0 1" 1>> tree.log 2>&1
./tree.o 10 5 0 1 1>> tree.log 2>&1

echo "--------test 50 0 0 1" 1>> tree.log 2>&1
./tree.o 50 0 0 1 1>> tree.log 2>&1

#-------- 1 1
echo "--------test 1 1 1 1" 1>> tree.log 2>&1
./tree.o 1 1 1 1 1>> tree.log 2>&1

echo "--------test 5 1 1 1" 1>> tree.log 2>&1
./tree.o 5 1 1 1 1>> tree.log 2>&1

echo "--------test 1 5 1 1" 1>> tree.log 2>&1
./tree.o 1 5 1 1 1>> tree.log 2>&1

echo "--------test 5 0 1 1" 1>> tree.log 2>&1
./tree.o 5 0 1 1 1>> tree.log 2>&1

echo "--------test 10 1 1 1" 1>> tree.log 2>&1
./tree.o 10 1 1 1 1>> tree.log 2>&1

echo "--------test 50 1 1 1" 1>> tree.log 2>&1
./tree.o 50 1 1 1 1>> tree.log 2>&1

echo "--------test 10 5 1 1" 1>> tree.log 2>&1
./tree.o 10 5 1 1 1>> tree.log 2>&1

echo "--------test 50 0 1 1" 1>> tree.log 2>&1
./tree.o 50 0 1 1 1>> tree.log 2>&1
