
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#	include <signal.h>
#define TRUE 1
#define FALSE 0
typedef struct Ordem {
	char *name;
        int argc;
        char *argv[10];
}Command;


static char summonsIn= '\0';
static int register_ch = 0;

void collet_summons(char *summons){
	int i;
	fgets(summons,150,stdin);
	i=strlen(summons)-2;
	summons=realloc(summons,i*sizeof(char));
	//strcpy(altern,summons);
}
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


/*char ** summonscont(char *altern){
    int i,smsCount = 0;
    char *smsResult;
    char *smsStr[100];
    char limit[] = "|",**smsNo[10];
    smsResult = strtok(altern, limit);
	//printf("\n%s\n",smsResult[3]);
    while(smsResult != NULL){
        smsStr[smsCount]=smsResult;
	//smsNo[smsCount] = &
	smsCount++;
	//printf("\n%s\n",smsStr[smsCount-1]);
	smsResult = strtok(NULL, limit);
    }
	return smsNo;
}
*/
int main(int argc, char* argv[]) {
	int i,j,iStatus,fdp[2],k;
	pipe(fdp);
	pid_t pid;
	static char *summons,*altern,**parameters[10],s[100];
	summons=(char*)malloc(150*sizeof(char));
	//altern=(char*)malloc(150*sizeof(char));
	Command act;
	system("clear");
	//printf("\t pid inicial: %d",pid);
	//printf("\t fdp[ %d],fdp[ %d]\n",fdp[0],fdp[1]);
	k=getpid();
	while(TRUE) {
		printf("\033[1;31m%s\033[0m \033[1;34m %d summons:\033[0m ",getcwd(s, 100),getpid());
		collet_summons(summons);
		if(strcmp(summons,"fim\n")==0){
				printf("%i\n", k);
				kill(k, SIGKILL);
		}
		else{
			frac_summons(summons,&act);
			pid=fork();
			if(pid<0){
				fprintf(stderr, "\n Failed to exec %s \n",summons);
				exit(1);
			}
			if(pid==0){
				close(fdp[1]);
				printf("pid do Filho: %d\n", getpid());
				//if(strcmp(summons,"fim\n")==0)
					//break;

				if(strcmp("cd", act.argv[0]) == 0) {
					if (act.argv[1] == NULL) {
						chdir(getenv("HOME"));
					}
					else if (chdir(act.argv[1]) < 0) {
						printf(" %s: diretorio não encontrado\n", act.argv[1]);
					}
					else{
						//printf("\n\t");
						//goto lap;
						//break;
					}

				}
				else{
					execvp(summons,act.argv);
					fprintf(stderr, "\n Failed to exec %s \n",summons);
					perror("Error dup()") ;
					}

				}
			else{
				close(fdp[0]);
				while(TRUE){
					printf("pid ant.waitpid: %d\n", getpid());
         	pid = waitpid(pid, &iStatus, WUNTRACED);
					printf("pid dep.waitpid: %d\n", getpid());
					if(WIFEXITED(iStatus)) {
						printf("\t WIFEXITED %d\n",pid);
						break;
					}
					if(WIFSIGNALED(iStatus)){
						printf("\t WIFSIGNALED %d\n\t",pid);
						break;
					}
					if(WIFSTOPPED(iStatus)){
						printf("\t WIFSIGNALED %d\n\t",pid);
					}
				}
			}
		}
	}
	return 0;
}
