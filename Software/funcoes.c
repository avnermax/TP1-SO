#include "funcoes.h"

void printPrompt(){
	printf("summons:> ");
}

void executaCmd(Command *act, int *fd, int i, int j){
	int x;

	// fecha descritores de arquivo.
	for(x = 0; x < NPIPES; x++) close(fd[x]);

	if(execvp(act[i].argv[j], act[i].argv) == -1){
		perror("execvp");
	}
}

void collectSummons(char *string){
	fgets(string, SIZE, stdin);
	// printf("Passou no collectSummons\n");
}

int existePipe(char *string){
	int p = 0;

	for(int i = 0; i < strlen(string); i++){
		if(string[i] == '|') return i;
	}
	// printf("Passou no existePipe\n");
	return p;
}

int existeRedirecao(char *string, int p){
	int i;

	for(i = p; i < strlen(string) - 1; i++){
		// Se for encontrado pipe antes dos redirecionadores, o valor deles será 3 e 4 respectivamente.
		// Se não encontrar pipe antes e encontrar depois, o valor dos redirecionadores será 1 e 2.
		// E caso não encontrar pipe ou redirecionadores, o valor será 0.
		if(p != 0) p = 2;

		if(string[i] == '=' && string[i + 1] == '>'){ // Saída do programa para o arquivo. OUT
			p = p + 1;
			return p;
		}
		if(string[i] == '<' && string[i + 1] == '='){ // Entrada do programa será o arquivo. IN
			p = p + 2;
			return p;
		}
	}
	// printf("Passou no existeRedirecao\n");
	if(p == 2) p = 0;
	return p;
}

char ** fracPipe(char *string){
	int i = 0;
	char *aux, **shift;

	shift = (char**) malloc(NPIPE * sizeof(char));

	aux = strtok(string, "|");
	while(aux != NULL){
		shift[i] = (char*) malloc(strlen(aux) * sizeof(char));
		strcpy(shift[i], aux);
		aux = strtok(NULL, "|");
		i++;
	}

	shift[i] = NULL;
	// printf("Passou no fracPipe\n");
	return shift;
}

char ** fracRedirecaoOut(char *string){
	int i = 0;
	char *aux, **shift;

	shift = (char**) malloc(NPIPE * sizeof(char));

	aux = strtok(string, "=>");
	while(aux != NULL){
		shift[i] = (char*) malloc(strlen(aux) * sizeof(char));
		strcpy(shift[i], aux);
		aux = strtok(NULL, "=>");
		i++;
	}

	shift[i] = NULL;
	// printf("Passou no fracRedirecaoDir\n");
	return shift;
}

char ** fracRedirecaoIn(char *string){
	int i = 0;
	char *aux, **shift;

	shift = (char**) malloc(NPIPE * sizeof(char));

	aux = strtok(string, "<=");
	while(aux != NULL){
		shift[i] = (char*) malloc(strlen(aux) * sizeof(char));
		strcpy(shift[i], aux);
		aux = strtok(NULL, "<=");
		i++;
	}

	shift[i] = NULL;
	// printf("Passou no fracRedirecaoEsq\n");
	return shift;
}

int fracArg(char **shift, char *string){
	int i = 0;
	char *aux;

	aux = strtok(string, " ");
	while (aux != NULL){
		shift[i] = (char*) malloc(strlen(aux) * sizeof(char));
		strcpy(shift[i], aux);
		aux = strtok(NULL, " ");
		i++;
	}
	shift[i] = NULL;
	// printf("Passou no fracArg\n");
	return i;
}

void cmdRedirecionamento(Command *act, char *string, int x){
	int y, direcao;
	char **stringOut, **stringIn;

	direcao = existeRedirecao(string, 0); // Verifica se existe redirecionamento de entrada ou saída.
	if(direcao == 1){ // Caso encontrar redirecionamento de saída.
		stringOut = fracRedirecaoOut(string); // Fragmenta a string em relação ao redirecionamento de saída.

		for(y = 0; y < NPIPE; y++){
			if(stringOut[y] != NULL){
				if(x == 0) cmdString(act, stringOut[y], y);
				if(x == 1) cmdString(act, stringOut[y], y + 2);
			}
		}
	}else{
		if(direcao == 2){ // Caso econtrar redirecionamento de entrada.
			stringIn = fracRedirecaoIn(string); // Fragmenta a string em relação ao redirecionamento de entrada.

			for(y = 0; y < NPIPE; y++){
				if(stringIn[y] != NULL){
					if(x == 0) cmdString(act, stringIn[y], y);
					if(x == 1) cmdString(act, stringIn[y], y + 2);
				}
			}
		}else{
			// Caso não encontrar nenhum redirecionamento, de entrada ou saída.
			cmdString(act, string, x);
		}
	}
	// printf("Passou no cmdRedirecionamento\n");
}

void cmdString(Command *act, char *string, int x){
	int i, j;

	act[x].argc = fracArg(act[x].argv, string); // Fragmenta e grava na struc cada comando.
	// Normaliza o final do comando, caso ele tenha um '\n'.
	i = act[x].argc - 1;
	j = strlen(act[x].argv[i]) - 1;
	if (act[x].argv[i][j] == '\n') act[x].argv[i][j] = '\0';
	// printf("Passou no cmdString\n");
}

void cmdInterpreter(Command *act, char *string){
	int x = 0;
	char **stringPipe;

	if(strcmp(string, "fim\n") == 0){
		// printf("Passou no cmdInterpreter\n");
		exit(EXIT_SUCCESS);
	}else{
		if(existePipe(string)){ // Verifica se existe pipe.
			stringPipe = fracPipe(string); // Fragmenta a string do comando em duas, em relação ao pipe.

			for(x = 0; x < NPIPE; x++){ // Testa cada string adquirida ao fragmentar pelo pipe.
				if(stringPipe[x] != NULL){
					cmdRedirecionamento(act, stringPipe[x], x);
				}else{
					// Mostrar erro, pois uma string originada na fragmentação é null.
					printf("Algum comando inválido encontrado.\n");
					exit(EXIT_FAILURE);
				}
			}
		}else{
			// Caso não exista pipe, porém existe redirecionamento, ou não existam ambos.
			cmdRedirecionamento(act, string, x);
		}
	}
	// printf("Passou no cmdInterpreter\n");
}

void readData(FILE *data, char *string){
	if(!feof(data)){
		fgets(string, SIZE, data);
	}else{
		fclose(data);
		exit(EXIT_SUCCESS);
	}
	// printf("Passou no readData\n");
}

FILE * opData(char *arq){
	FILE *data = fopen(arq, "r");
	if(data == NULL){
		printf("Arquivo %s inexistente!\n", arq);
		exit(EXIT_FAILURE);
		return 0;
	}
	// printf("Passou no opData\n");
	return data;
}
