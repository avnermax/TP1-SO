#include "shellso.h"

char ** interpretaEntrada(char *input){

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

void readInputFile(FILE *file, char *input){
	
	if(!feof(file)){
		fgets(input, 1023, file);
	}
	else{
		fclose(file);
		exit(EXIT_SUCCESS);
	}
}

FILE * openFile(char *arg){

	FILE *file = fopen(arg, "r");
	
	if(file == NULL){
		printf("Arquivo %s inexistente!\n", arg);
		exit(EXIT_FAILURE);
	}
	return file;
}

void readInputStdin(char *input){
	fgets(input, 1023, stdin);
}

void prompt(){
	printf("Sim, mestre? ");	
}
