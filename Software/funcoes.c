#include "funcoes.h"

void printPrompt(){
	char s[SIZE];
	printf("\033[1;31m%s\033[0m \033[1;34m %d summons:\033[0m ",getcwd(s, 100),getpid());
}

void colletSummons(char *summons){
	int i;
	scanf("%s", summons);
	i = strlen(summons)-2;
	summons = realloc(summons, i * sizeof(char));
	//strcpy(altern,summons);
	printf("Passou no collectSummons\n");
}

int fracArg(char **shift, char *summons){
	// Usa strtok pra separar a linha de comando em palavras p/ consulta.
	int i = 0;
	char *aux;

	aux = strtok(summons, " ");

	while (aux != NULL){
		shift[i] = (char*) malloc(strlen(aux) * sizeof(char));
		strcpy(shift[i], aux);
		aux = strtok(NULL, " ");
		i++;
	}

	return i;
	printf("Passou no fracArg\n");
}

void readData(FILE *data, char *summons){
	if(!feof(data)){
		fgets(summons, SIZE, data);
	}else{
		fclose(data);
		exit(EXIT_SUCCESS);
	}
	printf("Passou no readData\n");
}

void cmdInterpreter(Command *act, char *summons, int daddy){
	if(strcmp(summons, "fim\n") == 0){
		kill(daddy, SIGKILL);
	}else{
		act->argc = fracArg(act->argv, summons);
	}
	printf("Passou no cmdInterpreter\n");
}

FILE * opData(char *arq){
	FILE *data = fopen(arq, "r");
	if(data == NULL){
		printf("Arquivo %s inexistente!\n", arq);
		exit(EXIT_FAILURE);
		return 0;
	}
	return data;
	printf("Passou no opData\n");
}
