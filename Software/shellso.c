#include "funcoes.h"

int main(int argc, char* argv[]){
	int iStatus, fd[2], daddy;
	char *summons;
	Command *act;
	FILE *data;

	summons = (char*) malloc(SIZE * sizeof(char));
	act = (Command*) malloc(sizeof(Command*));

	pipe(fd);
	pid_t pid;
	system("clear");

	if(argc == 2) data = opData(argv[1]);

	daddy = getpid();
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

		cmdInterpreter(act, summons, daddy);

		pid = fork();
		if(pid < 0){
			printf("Erro no fork.\n");
			exit(EXIT_FAILURE);
		}

		if(pid != 0){
			while(TRUE){
				waitpid(pid, &iStatus, WUNTRACED);

				if(WIFEXITED(iStatus)) {
					printf("\nStatus de termino: %d.\n", WEXITSTATUS(iStatus));
					break;
				}
				if(WIFSIGNALED(iStatus)){
					printf("\nFilho terminou e o sinal que terminou o filho foi: %d\n", WTERMSIG(iStatus));
					break;
				}
				if(WIFSTOPPED(iStatus)){
					printf("\n Filho recebeu sinal de stop. Sinal: %d\n", WSTOPSIG(iStatus));
				}
			}
		}else{
			printf("Filho em execução: %d\n", getpid());
			execvp(act->argv[0], act->argv);
		}
	}
	return 0;
}
