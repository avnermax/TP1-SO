#include "funcoes.h"

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
			case 1:
				print_prompt();
				collet_summons(summons);
				break;
			case 2:
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
