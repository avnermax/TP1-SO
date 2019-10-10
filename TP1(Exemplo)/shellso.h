#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

void prompt();
void shell(int argc, char *argv[]);
char ** interpretaEntrada(char *input);
void readInputFile(FILE *file, char *input);
FILE * openFile(char *arg);
void readInputStdin(char *input);
