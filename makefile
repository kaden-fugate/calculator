CC = g++
CFLAGS = -Wall -g
TARGET = calc
SRCS = main.o lexer.o

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

lexer.o: lexer.cpp lexer.hpp
	$(CC) $(CFLAGS) -c lexer.cpp

clean:
	rm -rf *.o calc