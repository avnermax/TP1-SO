#include "funcoes.h"

int main(int argc, char* argv[]){
	int fd[NPIPES], dir, in, out, p;
	char *summons, *summonsBckp, *nameFile1, *nameFile2;
	Command *act;
	FILE *data;

	summons = (char*) malloc(SIZE * sizeof(char));		// armazena linha relacionada ao comando.
	summonsBckp = (char*) malloc(SIZE * sizeof(char));	// backup da linha de comando.
	act = (Command*) malloc(NPIPES * sizeof(Command*));	// armazena o tamanho e os comandos já separados.

	nameFile1 = (char*) malloc(SIZE * sizeof(char));
	nameFile2 = (char*) malloc(SIZE * sizeof(char));

	if(pipe(fd) == -1){
		perror("Falha ao criar o pipe.");
		exit(EXIT_FAILURE);
	}

	pid_t pid;
	system("clear");

	if(argc == 2) data = opData(argv[1]);

	while(TRUE){

		switch(argc){ // Determina se a execução ocorrerá pelo arquivo de entrada ou não.
			case 1:
				printPrompt();
				collectSummons(summons);
			break;

			case 2:
				readData(data, summons);
			break;

			default: printf("Algo errado, tente novamente.");
		}

		strcpy(summonsBckp, summons); // Faz o backup da linha de comando.
		if(strcmp(summons, "\n") != 0){
			cmdInterpreter(act, summons); // Interpreta e separa os comandos.
		}else{
			strcpy(summons, " "); // Reseta o summons.
			continue;
		}

		pid = fork();
		switch(pid){
			case -1:
				perror("Erro no fork.");
				exit(EXIT_FAILURE);
			break;

			case 0:
				p = existePipe(summonsBckp);
				if(p){
					// Depois do pipe.
					dir = existeRedirecao(summonsBckp, p);
					if(dir == 3){
						strcpy(nameFile2, act[3].argv[0]);
						// Abre/cria arquivo para gravar os dados passados no pipe.
						out = open(nameFile2, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
						dup2(out, 1);
						close(in);
						close(out);
						executaCmd(act, fd, 0, 0);
					}else{
						if(dir == 4){
							strcpy(nameFile2, act[3].argv[0]);
							// Abre arquivo para pegar os dados.
							in = open(nameFile2, O_RDONLY);
							if(in != -1){
								dup2(in, 0);
							}else{
								printf("Erro ae abrir o arquivo\n");
							}
							close(in);
							close(out);
							executaCmd(act, fd, 0, 0);
						}else{
							close(STD_OUTPUT); // fecha saída padrão.
							dup(fd[1]); // Faz saída padrão ir para o pipe.
							executaCmd(act, fd, 0, 0);
						}
					}
				}else{
					// Caso não exista pipe.
					dir = existeRedirecao(summonsBckp, p);
					if(dir == 1){
						strcpy(nameFile1, act[1].argv[0]);
						// Abre/cria arquivo para gravar os dados passados no pipe.
						out = open(nameFile1, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
						dup2(out, 1);
						close(in);
						close(out);
					}else{
						if(dir == 2){
							strcpy(nameFile1, act[1].argv[0]);
							// Abre arquivo para pegar os dados.
							in = open(nameFile1, O_RDONLY);
							if(in != -1){
								dup2(in, 0);
							}else{
								printf("Erro ae abrir o arquivo\n");
							}
							close(in);
							close(out);
						}
					}

					executaCmd(act, fd, 0, 0);
				}
			break;

			default:
				wait(NULL);

				p = existePipe(summonsBckp);
				if(p){
					// Antes do pipe.
					dir = existeRedirecao(summonsBckp, 0);
					if(dir == 1){
						strcpy(nameFile1, act[1].argv[0]);
						// Abre/cria arquivo para gravar os dados passados no pipe.
						out = open(nameFile1, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
						dup2(out, 1);
						close(in);
						close(out);

						executaCmd(act, fd, 1, 0);
					}else{
						if(dir == 2){
							strcpy(nameFile1, act[1].argv[0]);
							// Abre arquivo para pegar os dados.
							in = open(nameFile1, O_RDONLY);
							if(in != -1){
								dup2(in, 0);
							}else{
								printf("Erro ae abrir o arquivo\n");
							}
							close(in);
							close(out);

							executaCmd(act, fd, 1, 0);
						}else{
							close(STD_INPUT); // Fecha entrada padrão.
							dup(fd[0]); // Faz entrada padrão ir para o pipe.

							executaCmd(act, fd, 1, 0);
						}
					}
				}
			break;
		}
	}
	return 0;
}
