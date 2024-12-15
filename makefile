CC = g++
CFLAGS = -Wall -g
TARGET = calc
SRCS = main.o main_funcs.o variable.o prim_var.o matrix.o

all: main.o main_funcs.o variable.o prim_var.o matrix.o
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

main_funcs.o: main_funcs.cpp main_funcs.hpp
	$(CC) $(CFLAGS) -c main_funcs.cpp

variable.o: variable.cpp variable.hpp
	$(CC) $(CFLAGS) -c variable.cpp

prim_var.o: prim_var.cpp prim_var.hpp
	$(CC) $(CFLAGS) -c prim_var.cpp

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(CFLAGS) -c matrix.cpp

clean:
	rm -rf *.o calc