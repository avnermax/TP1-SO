#include "funcoes.h"

int main(int argc, char* argv[]){
	int fd[NPIPES], i;
	char *summons, *summonsBckp;
	Command *act;
	FILE *data;

	summons = (char*) malloc(SIZE * sizeof(char));
	summonsBckp = (char*) malloc(SIZE * sizeof(char));
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

		strcpy(summonsBckp, summons);
		cmdInterpreter(act, summons);

		pid = fork();
		switch(pid){
			case -1:
				perror("Erro no fork.");
				exit(EXIT_FAILURE);
			break;

			case 0:
				close(STD_OUTPUT);	// closing standard output
				dup(fd[WRITE]);			// make standard output go to pipe
				close(fd[READ]);		// close file descriptors
				close(fd[WRITE]);

				// close file descriptors
				for(i = 0; i < NPIPES; i++) close(fd[i]);

				if(execvp(act[0].argv[0], act[0].argv) == -1){
					perror("execvp2");
				}
			break;

			default:
				wait(NULL);

				close(STD_INPUT);	// close standard input
				dup(fd[READ]);			// make standard output go to pipe
				close(fd[READ]);		// close file descriptors
				close(fd[WRITE]);

				// close file descriptors
				for(i = 0; i < NPIPES; i++) close(fd[i]);

				if(existePipe(summonsBckp)){
					if(execvp(act[1].argv[0], act[1].argv) == -1){
						perror("execvp1");
					}
				}

			break;
		}
	}
	return 0;
}
