
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#define TRUE 1
#define FALSE 0
typedef struct Ordem {
	char *name;
        int argc;
        char *argv[10];
}Command;


static char summonsIn= '\0';
static int register_ch = 0;

void frac_summons(char *summons, Command *act ){
/*Comment:
	Usa strtok pra separar a linha de comando em palavras p/ consulta.
*/
	char *aux;
	aux= strtok (summons," \n");
	int i= 0;
	while (aux != NULL) {
		act->argv[i] = aux;
		aux= strtok (NULL, " \n");
		i++;
	}
	act->argc = i;
	act->argv[i++] = NULL;
}



int main(int argc, char* argv[]) {
	int i, iStatus, fd[2];
	pipe(fd);
	pid_t pid;
	static char *summons,*altern,**parameters[10];
	summons=(char*)malloc(150*sizeof(char));
	altern=(char*)malloc(150*sizeof(char));
	Command act ;
	//welcomeMessage();
	for(i = 0; i < 10; i++)
		parameters[i] = malloc(sizeof(char) * 2);

	lap:while(TRUE) {

		printf("\nsummons: ");
		fgets(summons,150,stdin);
		i=strlen(summons)-2;
		summons=realloc(summons,i*sizeof(char));
		if(strcmp(summons,"exit\n")==0 || strcmp(summons,"end\n")==0 || strcmp(summons,"quit\n")==0 ||strcmp(summons,"fim\n")==0)
			break;
		else{
			frac_summons(summons,&act);
			pid=fork();
			if(pid==0){
				close(fd[1]);
				//printf("\n\tCriado o processo %d", pid);
				execvp(act.argv[0],act.argv);
				fprintf(stderr, "\n Failed to exec %s \n",summons);
				//printf("");
				//dup2(fd[0], 0);
				//printf("\n\tfim do processo %d", pid);
			}
			else{
				close(fd[0]);
				//printf("\nCriado o processo %d", pid);

				//perror("Error dup()") ;

      				while(TRUE){
         				//printf("\nEsperando o status do filho de %d.",pid);
         				waitpid(pid,&iStatus,WCONTINUED);
         				//printf("\nStatus do filho %d pego: %d",pid, iStatus);
         				if(WIFEXITED(iStatus)){
						//printf("\n1 Filho %d terminou normalmente",pid);
						//printf("\n1 O status de término foi %d.", WEXITSTATUS(iStatus));
          					break;
         				}
         				if(WIFSIGNALED(iStatus)){
            					//printf("\n2 Filho %d, recebeu %d sinal e terminou", pid, iStatus);
            					//printf("\n2 O sinal que terminou o filho %d foi %d.", pid, WTERMSIG(iStatus));
	    					break;
         				}
         				if(WIFSTOPPED(iStatus)){
            					//printf("\n3 Filho %d, recebeu sinal stop %d",iStatus);
            					//printf("\n3 O sinal que parou o filho %d foi %d.\n",pid, WSTOPSIG(iStatus));
         				}
     				}
				//waitpid( pid,&status,FALSE);


			}

		}
	}

	return 0;
}
