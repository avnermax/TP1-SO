#include "funcoes.h"

int main(int argc, char* argv[]){
	int fd[NPIPES];
	char *summons, *summonsBckp;
	Command *act;
	FILE *data;

	summons = (char*) malloc(SIZE * sizeof(char));		/* armazena linha relacionada ao comando */
	summonsBckp = (char*) malloc(SIZE * sizeof(char));	/* backup da linha de comando */
	act = (Command*) malloc(NPIPES * sizeof(Command*));	/* armazena o tamanho e os comandos já separados */

	if(pipe(fd) == -1){
		perror("Falha ao criar o pipe.");
		exit(EXIT_FAILURE);
	}

	pid_t pid;
	system("clear");

	if(argc == 2) data = opData(argv[1]);

	while(TRUE){
		switch(argc){ /* determina se a execução ocorrerá pelo arquivo de entrada ou não */
			case 1:
				printPrompt();
				collectSummons(summons);
			break;

			case 2:
				readData(data, summons);
			break;

			default: printf("Algo errado, tente novamente.");
		}

		strcpy(summonsBckp, summons);	/* faz o backup da linha de comando */
		cmdInterpreter(act, summons); 	/* interpreta e separa os comandos */

		pid = fork();
		switch(pid){
			case -1:
				perror("Erro no fork.");
				exit(EXIT_FAILURE);
			break;

			case 0:

				if(existePipe(summonsBckp)){
					close(STD_OUTPUT);		/* fecha saída padrão */
					dup(fd[WRITE]);			/* faz saída padrão ir para o pipe */
					close(fd[READ]);		/* fecha descritores de arquivo */
					close(fd[WRITE]);
				}

				if(execvp(act[0].argv[0], act[0].argv) == -1){
					perror("execvp2");
				}
			break;

			default:
				wait(NULL);

				if(existePipe(summonsBckp)){
					close(STD_INPUT);		/* fecha entrada padrão */
					dup(fd[READ]);			/* faz entrada padrão ir para o pipe */
					close(fd[READ]);		/* fecha descritores de arquivo */
					close(fd[WRITE]);

					if(execvp(act[1].argv[0], act[1].argv) == -1){
						perror("execvp1");
					}
				}
			break;
		}
	}
	return 0;
}
