#include "shellso.h"

void shell(int argc, char *argv[]){

	// variável que armazena a entrada 
	char input[1024];

	// variável que armazena os argumentos da entrada
	char **arguments;

	// variável que armazena o pid do processo filho
	pid_t pid;

	//Variável para armazenar o possível arquivo passado por parâmetro pro shell(modo arquivo)
	FILE *file;

	//caso entre no modo arquivo
	if(argc == 2){
		file = openFile(argv[1]);
	}


    while(1){

    	//pega a entrada do teclado ou do arquivo de entrada
		switch(argc){
			
			//modo interativo
			case 1:	
				// imprime o prompt
    			prompt();

				// lê a entrada e a armazena na string input
				readInputStdin(input);
				break;

			//modo arquivo
			case 2:
				readInputFile(file, input);
				break;
			
			default: printf("Argumentos inválidos\n");
		}

		// processa a entrada e retorna um vetor contendo os argumentos da entrada
		arguments = interpretaEntrada(input);

		//se o vetor de argumentos for vazio, retorna no loop
		if(arguments == NULL){
			continue;
		}

		// cria processo filho e verifica a ocorrência de erro
		if((pid = fork()) < 0){
			printf("erro ao criar o processo\n");
			continue;
		}
		
		// processo filho: altera a imagem do processo filho (executa o programa )
		if(pid == 0){
			if(execvp(arguments[0], arguments) == -1){
				perror("execvp");
			}
			exit(EXIT_SUCCESS);
		}

		// processo pai: espera o filho terminar
		else{
			wait(NULL);
		}
    }

}