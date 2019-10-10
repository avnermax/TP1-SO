CC = gcc
CFLAGS = -g -Wall
CLIBS = -lm
OBJS = funcoes.o
TARGET = shellso
all: $(TARGET)

shellso: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o shellso shellso.c $(CLIBS)

funcoes.o: funcoes.c funcoes.h
	$(CC) $(CFLAGS) -c funcoes.c $(CLIBS)

clean:
	rm -rf $(OBJS) shellso
