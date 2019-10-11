#include "funcoes.h"

void printPrompt(){
	printf("summons:> ");
}

void collectSummons(char *summons){
	fgets(summons, SIZE, stdin);
	printf("Passou no collectSummons\n");
}

int existePipe(char *summons){
	int p = 0;

	for(int i = 0; i < strlen(summons); i++){
		if(summons[i] == '|') p++;
	}
	printf("Passou no existePipe\n");
	return p;
}

char ** fracPipe(char *summons){
	int i = 0, x, tam;
	char *aux, *aux2, **shift;

	shift = (char**) malloc(NPIPES * sizeof(char));

	aux2 = strtok(summons, "|");
	while (aux != NULL){
		shift[i] = (char*) malloc(strlen(aux) * sizeof(char));
		printf("pipe:%d cmd:%s\n", i, aux2);
		strcpy(shift[i], aux2);
		aux = strtok(NULL, "|");

		// Remove espaço vazio no início e no fim da palavra.
		tam = strlen(aux)-2;
		aux2 = (char*) malloc(tam * sizeof(char));
		if(aux[0] == ' ')
			for(x = 1; x <= tam; x++)
				aux2[x - 1] = aux[x];
		i++;
	}

	shift[i] = NULL;
	printf("Passou no fracPipe\n");
	return shift;
}

int fracArg(char **shift, char *string){
	int i = 0;
	char *aux;

	aux = strtok(string, " ");
	while (aux != NULL){
		// shift[i] = (char*) malloc(strlen(aux) * sizeof(char));
		strcpy(shift[i], aux);
		aux = strtok(NULL, " ");
		i++;
	}
	shift[i] = NULL;
	printf("Passou no fracArg\n");
	return i;
}

void cmdInterpreter(Command *act, char *summons){
	int i, j, x;
	char **stringAux;

	if(strcmp(summons, "fim\n") == 0){
		printf("Passou no cmdInterpreter\n");
		exit(EXIT_SUCCESS);
	}else{
		if(existePipe(summons)){
			stringAux = fracPipe(summons);
			for(x = 0; x < NPIPES; x++){
				act[x].string = stringAux[x];
				act[x].argc = fracArg(act[x].argv, act[x].string);
				i = act[x].argc - 1;
				j = strlen(act[x].argv[i]) - 1;
				if (act[x].argv[i][j] == '\n') act[x].argv[i][j] = '\0';
			}
		}else{
			act[0].argc = fracArg(act[0].argv, summons);
			i = act[0].argc - 1;
			j = strlen(act[0].argv[i]) - 1;
			if (act[0].argv[i][j] == '\n') act[0].argv[i][j] = '\0';
		}

	}
	printf("Passou no cmdInterpreter\n");
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

FILE * opData(char *arq){
	FILE *data = fopen(arq, "r");
	if(data == NULL){
		printf("Arquivo %s inexistente!\n", arq);
		exit(EXIT_FAILURE);
		return 0;
	}
	printf("Passou no opData\n");
	return data;
}
