
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

void print_prompt(){
	char s[SIZE];
	printf("\033[1;31m%s\033[0m \033[1;34m %d summons:\033[0m ",getcwd(s, 100),getpid());
}
void collet_summons(char *summons){
	int i;
	scanf("%s",summons);
	i=strlen(summons)-2;
	summons=realloc(summons,i*sizeof(char));
	printf("A\n" );
	//strcpy(altern,summons);
}
int frac_orde(char **shift,char *summons){
/*Comment:
	Usa strtok pra separar a linha de comando em palavras p/ consulta.
*/
	int i= 0;
	char *aux,*div;
	strcpy(div,summons);
	printf("\t%s , %s\n",div,summons);
	shift=calloc(1,sizeof(char*));
	aux= strtok (div,"|");

	while (aux != NULL) {
		shift[i] = aux;
		aux= strtok (NULL, "|");
		i++;
		shift=realloc(shift,i*sizeof(char*));
	}
	return i;
}
void frac_summons(char *summons,Command **act, int j ){
/*Comment:
	Usa strtok pra separar a linha de comando em palavras p/ consulta.
*/
	//printf("%s",summons);
	char *aux;
	aux= strtok (summons," \n");
	int i= 0;
	act[j]->num = j;
	while (aux != NULL) {
		act[j]->argv[i] = aux;
		aux= strtok (NULL, " \n");
		i++;
	}
	act[j]->argc = i;
	act[j]->argv[i++] = NULL;

}



void read_data(FILE *data, char *summons){
	if(!feof(data)){
		fgets(summons, SIZE, data);
	}
	else{
		fclose(data);
		exit(EXIT_SUCCESS);
	}
}

void command_interpreter(Command **act,char *summons,int daddy){
	int cont=0,i=0,c=0;
	char 	**shift;
	printf("B\n" );
	shift=(char**)malloc(SIZE*sizeof(char*));
	while(c<SIZE){
		shift[c]=(char*)malloc(sizeof(char));
		c++;
	}
	if(strcmp(summons,"fim\n")==0){
		printf("%i\n", daddy);
		kill(daddy, SIGKILL);
	}
	printf("\nB\n");

	i=frac_orde(shift,summons);
	printf("\nC\n");
	act=(Command**)malloc(i*sizeof(Command*));
	printf("\nD\n");
	while(cont<i){
		frac_summons(summons,act,cont);
		cont++;
	}
	printf("\nE\n");
}

FILE * op_data(char *arq){
	FILE *data = fopen(arq, "r");
	if(data == NULL){
		printf("Arquivo %s inexistente!\n", arq);
		exit(EXIT_FAILURE);
	}
	return data;
}
/*
char **interpretaEntrada(char *input){

	short argc = 0;
	char **argv, *token;

	// verificar entrada vazia
	if(strcmp(input, "\n") == 0 || strcmp(input, "\0") == 0){
		//retorna um código pra função que chamou, informando a entrada vazia
		return NULL;
	}

	// verifica comando de término do shell
	if(strcmp(input, "fim\n") == 0){
		// mata o shell
		exit(EXIT_SUCCESS);
	}

	//conta a quantidade de argumentos pra alocar o vetor de strings argv
	for(int i = 0; i < strlen(input); i++){
		if(input[i] == ' ') argc++;
	}

	//aloca o vetor de argumentos
	argv = (char**) malloc(argc * sizeof(char*));

	//token recebe o primeiro argumento
    token = strtok(input, " ");

    argc = 0;
    while (token != NULL) {
        argv[argc] = (char*) malloc( strlen(token) * sizeof(char));
        strcpy(argv[argc], token);
        token = strtok(NULL, " ");
        argc++;
    }

    //caso salve o '\n' no fim da string, retira o \n para corrigir o argumento
    if(argv[argc-1][strlen(argv[argc-1])-1] == '\n'){
    	argv[argc-1][strlen(argv[argc-1])-1] = '\0';
   	}

   	//ultima posição do vetor de argumentos aponta para NULL, para indicar fim dos argumentos
   	argv[argc] = NULL;


	return argv;
}
*/

/*
Command ** summonscont(char *altern){
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
	int i,j,iStatus,fdp[2],daddy;
	char *summons,**send;
	summons=(char*)malloc(SIZE*sizeof(char));
	Command **act;
	pipe(fdp);
	pid_t pid;
	FILE *data;
	system("clear");
	daddy=getpid();
	if(argc == 2)
		data = op_data(argv[1]);
	while(TRUE){
		// argc determina se entrada inicial eh terminal ou arquivo
		switch(argc){
			case 1 :
				print_prompt();
				collet_summons(summons);
				break;
			case 2 :
				read_data(data,summons);
				break;
			default: printf("Algo errado, Tente novamente");
		}

		//line=command_interpreter(,daddy);
		//collet_summons(summons);

		command_interpreter(act,summons,daddy);
		//frac_summons(summons,&act);
		//pid=fork();
		if(pid<0){
			fprintf(stderr, "\n Failed to exec %s \n",summons);
			exit(1);
		}
		if(pid==0){
			close(fdp[1]);
			printf("pid do Filho: %d\n", getpid());
			//if(strcmp(summons,"fim\n")==0)
				//break;
			if(strcmp("cd", act[j]->argv[0]) == 0) {
				if (act[j]->argv[1] == NULL) {
					chdir(getenv("HOME"));
				}
				else if (chdir(act[j]->argv[1]) < 0) {
					printf(" %s: diretorio não encontrado\n", act[j]->argv[1]);
				}
				else;

			}
			else{
				execvp(summons,act[j]->argv);
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
	return 0;
}
