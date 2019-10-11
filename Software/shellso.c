#include "funcoes.h"

int main(int argc, char* argv[]){
	int fd[2];
	char *summons;
	Command *act;
	FILE *data;

	summons = (char*) malloc(SIZE * sizeof(char));
	act = (Command*) malloc(NPIPES * sizeof(Command*));

	if(pipe(fd) == -1){
		perror("Falha ao criar o pipe.");
		exit(EXIT_FAILURE);
	}
	pid_t pid;
	system("clear");

	if(argc == 2) data = opData(argv[1]);

	while(TRUE){
		// "argc" determina se entrada inicial eh terminal ou arquivo
		switch(argc){
			case 1:
				printPrompt();
				collectSummons(summons);
			break;

			case 2:
				readData(data, summons);
			break;

			default: printf("Algo errado, tente novamente.");
		}

		printf("%s\n", summons);
		cmdInterpreter(act, summons);

		pid = fork();
		switch(pid){
			case -1:
				perror("Erro no fork.");
				exit(EXIT_FAILURE);
			break;

			case 0:
				close(fd[STD_OUTPUT]);	// closing standard output
				dup(fd[WRITE]);			// make standard output go to pipe
				close(fd[READ]);		// close file descriptors
				close(fd[WRITE]);

				execvp(act[0].argv[0], act[0].argv);
			break;

			default:
				wait(NULL);

				close(fd[STD_INPUT]);	// close standard input
				dup(fd[READ]);			// make standard output go to pipe
				close(fd[READ]);		// close file descriptors
				close(fd[WRITE]);

				if(existePipe(summons)){
					execvp(act[1].argv[0], act[1].argv);
				}
			break;
		}
	}
	return 0;
}
