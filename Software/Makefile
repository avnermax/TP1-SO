CC = gcc
CFLAGS = -g -Wall
CLIBS = -lm
OBJS = ord.o memoria.o
TARGET = tp
all: $(TARGET)

tp: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o tp cache.c $(CLIBS)
funcoes.o: ord.c ord.h
	$(CC) $(CFLAGS) -c ord.c $(CLIBS)
memoria.o: memoria.c memoria.h
	$(CC) $(CFLAGS) -c memoria.c $(CLIBS)
clean:
	rm -rf $(OBJS) tp
