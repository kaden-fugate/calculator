CC = g++
CFLAGS = -Wall -g
TARGET = calc
SRCS = main.o lexer.o parser.o interpreter.o

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

lexer.o: lexer.cpp lexer.hpp
	$(CC) $(CFLAGS) -c lexer.cpp

parser.o: parser.cpp parser.hpp
	$(CC) $(CFLAGS) -c parser.cpp

interpreter.o: interpreter.cpp interpreter.hpp
	$(CC) $(CFLAGS) -c interpreter.cpp

clean:
	rm -rf *.o calc