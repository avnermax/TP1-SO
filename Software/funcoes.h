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
#define NPIPES 2

#define STD_INPUT  0    /* file descriptor for standard input */
#define STD_OUTPUT 1    /* file descriptor for standard output */
#define READ  0         /* read file descriptor from pipe */
#define WRITE 1         /* write file descriptor from pipe */

typedef struct T_Command{
	int argc;
	char *argv[SIZE], *string;
}Command;

void printPrompt();

void collectSummons(char *summons);

int existePipe(char *summons);

char ** fracPipe(char *summons);

int fracArg(char **shift, char *string);

void cmdInterpreter(Command *act, char *summons);

void fracSummons(char *summons, Command *act, int j);

void readData(FILE *data, char *summons);

FILE * opData(char *arq);
