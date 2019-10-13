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

typedef struct Ordem {
	char *name;
  int argc;
  char *argv[64];
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
	int daddy,c,i,iStatus, fd[2];
	FILE *arq,*arq1;
	pipe(fd);
	pid_t pid;
	static char *summons,*altern,**parameters[10],s[SIZE];
	summons=(char*)malloc(SIZE*sizeof(char));
	//altern=(char*)malloc(150*sizeof(char));
	Command act ;
	daddy=getpid();

	while(TRUE){
		c = argc;
		if(c<2){
			printf("\033[1;31m%s\033[0m \033[1;34m %d summons:\033[0m ",getcwd(s, 100),getpid());
			fgets(summons,SIZE,stdin);
			i=strlen(summons)-2;
			summons=(char*)realloc(summons,i*sizeof(char));

		}
		else if(c=2){
			FILE *arq1 = fopen(argv[1], "r");
			if(!feof(arq1)){
				fgets(summons, SIZE, arq1);
			}
			else{
				fclose(arq1);
				argc=1;
			}
			if(arq1 == NULL){
				printf("Arquivo %s inexistente!\n", argv[1]);
				exit(EXIT_FAILURE);
			}
		}
		else printf("Arquivo não encontrado\n");

		//printf("\033[1;31m%s\033[0m \033[1;34m %d summons:\033[0m ",getcwd(s, 100),getpid());
		//fgets(summons,150,stdin);
		//i=strlen(summons)-2;
		//summons=realloc(summons,i*sizeof(char));
		if(strcmp(summons,"\n")==0 || strcmp(summons,"\0")==0)
			summons =NULL;
		if(strcmp(summons,"fim\n")==0){
			setbuf(stdin,NULL);
			setbuf(stdout,NULL);
			return 0;
		}

		//for(int i = 0,c=0; i < strlen(summons); i++){
			if(summons[i] == ' ') c++;
		//}
		//act->argv =(char**)malloc(c*sizeof(char*));
		//close(fd[1]);
		frac_summons(summons,&act);
			if(pid=fork()<0){
				exit(EXIT_FAILURE);
			}
			if(pid==0){
				if(strcmp("cd", act.argv[0]) == 0) {
					if (act.argv[1] == NULL) {
						chdir(getenv("HOME"));
					}
				else if (chdir(act.argv[1]) < 0) {
					printf(" %s: diretorio não encontrado\n", act.argv[1]);
				}
				else exit(EXIT_SUCCESS);
				}
				else{
					execvp(act.argv[0],act.argv);
					fprintf(stderr, "\n Failed to exec %s \n",summons);
				}
			}
			else{
				//close(fd[0]);
      				while(TRUE){

         				waitpid(pid,&iStatus,WCONTINUED);
         				if(WIFEXITED(iStatus)){
						break;
         				}
         				if(WIFSIGNALED(iStatus)){
            					break;
         				}
         				if(WIFSTOPPED(iStatus)){

         				}
     				}

			}

		}
	return 0;
}
