#include "funcoes.h"

void print_prompt(){
	char s[SIZE];
	printf("\033[1;31m%s\033[0m \033[1;34m %d summons:\033[0m ",getcwd(s, 100),getpid());
}

void collet_summons(char *summons){
	int i;
	scanf("%s",summons);
	i=strlen(summons)-2;
	summons=realloc(summons,i*sizeof(char));
	printf("A\n");
	//strcpy(altern,summons);
}

int frac_orde(char **shift,char *summons){
/*Comment:
	Usa strtok pra separar a linha de comando em palavras p/ consulta.
*/
	int i= 0;
	char *aux, *div;
	strcpy(div, summons);
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

void frac_summons(char *summons,Command **act, int j){
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
