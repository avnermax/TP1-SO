#include "funcoes.h"

void printPrompt(){
	printf("summons:> ");
}

void collectSummons(char *summons){
	fgets(summons, SIZE, stdin);
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

	shift[i] = NULL;
	return i;
	printf("Passou no fracArg\n");
}

void readData(FILE *data, char *summons){
	if(!feof(data)){
		fgets(summons, SIZE, data);
		printf("%s\n", summons);
	}else{
		fclose(data);
		exit(EXIT_SUCCESS);
	}
	printf("Passou no readData\n");
}

void cmdInterpreter(Command *act, char *summons, int daddy){
	if(strcmp(summons, "fim\n") == 0){
		printf("Passou no cmdInterpreter\n");
		exit(EXIT_SUCCESS);
	}else{
		act->argc = fracArg(act->argv, summons);

		int x = act->argc - 1;
		int y = strlen(act->argv[x]) - 1;
		if (act->argv[x][y] == '\n')
			act->argv[x][y] = '\0';
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
