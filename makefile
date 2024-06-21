CC = gcc
CFLAGS = -Wall -g
TARGET = calc
SRCS = main.c function.c term.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -f $(OBJS) $(TARGET)