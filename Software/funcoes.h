#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0
#define SIZE 512

typedef struct T_Command{
	int argc;
	char *argv[SIZE];
}Command;

void printPrompt();

void collectSummons(char *summons);

int fracArg(char **shift, char *summons);

void fracSummons(char *summons, Command *act, int j);

void readData(FILE *data, char *summons);

void cmdInterpreter(Command *act, char *summons, int daddy);

FILE * opData(char *arq);
