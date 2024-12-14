CC = g++
CFLAGS = -Wall -g
TARGET = calc
SRCS = main.cpp main_funcs.cpp
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -f $(OBJS) $(TARGET)