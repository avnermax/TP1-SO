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
		// argc determina se entrada inicial eh terminal ou arquivo
		switch(argc){
			case 1:
				printPrompt();
				colletSummons(summons);
				break;
			case 2:
				readData(data, summons);
				break;
			default: printf("Algo errado, Tente novamente");
		}

		cmdInterpreter(act, summons, daddy);

		pid = fork();
		if(pid < 0){
			printf("Erro no fork.\n");
			return 0;
		}

		if(pid != 0){
			// close(fd[0]);
			while(TRUE){
				// printf("pid ant.waitpid: %d\n", getpid());
				waitpid(pid, &iStatus, WUNTRACED);
				// printf("pid dep.waitpid: %d\n", getpid());

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
			// close(fd[1]);
			printf("Filho em execução: %d\n", getpid());
			//if(strcmp(summons,"fim\n")==0)
				//break;
			if(strcmp("cd", act->argv[0]) == 0) {
				if (act->argv[1] == NULL) {
					chdir(getenv("HOME"));
				}else{
					if (chdir(act->argv[1]) < 0)
						printf("%s: diretorio não encontrado\n", act->argv[1]);
				}
			}else{
				execvp(summons, act->argv);
				fprintf(stderr, "\n Failed to exec %s \n", summons);
				perror("Error dup()") ;
			}
		}
	}
	return 0;
}
