#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0
#define SIZE 512

typedef struct Orde {
	int num;
  int argc;
  char *argv[100];
}Command;

void print_prompt();

int frac_orde(char **shift,char *summons);

void frac_summons(char *summons,Command **act, int j);

void read_data(FILE *data, char *summons);

void command_interpreter(Command **act,char *summons,int daddy);

FILE * op_data(char *arq);
