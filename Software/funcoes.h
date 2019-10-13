#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

#define SIZE 512			// tamanho dos argumentos.
#define NPIPE 2				// numero de pipes e redirecionamentos.
#define NPIPES NPIPE * 2	// numero real de pipes que será criado

#define STD_INPUT 0			// descritor para entrada padrão
#define STD_OUTPUT 1	    // descritor para saída padrão

typedef struct T_Command{
	int argc;
	char *argv[SIZE];
}Command;

void printPrompt();

void executaCmd(Command *act, int *fd, int i, int j);

void collectSummons(char *summons);

int existePipe(char *string);

int existeRedirecao(char *string, int p);

char ** fracPipe(char *string);

char ** fracRedirecaoOut(char *string);

char ** fracRedirecaoIn(char *string);

int fracArg(char **shift, char *string);

void cmdRedirecionamento(Command *act, char *string, int x);

void cmdString(Command *act, char *string, int x);

void cmdInterpreter(Command *act, char *string);

void readData(FILE *data, char *string);

FILE * opData(char *arq);
