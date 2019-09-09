#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
	int fd[2];
	pid_t childpid;
	//printf("%d <> %d\n",fd[0],fd[1]);
	pipe(fd);
	//printf("%d <> %d\n",fd[0],fd[1]);
	if((childpid = fork()) == -1){
	printf("erro");perror("fork");
	return(1);
	}
	
	
	if(childpid == 0){
		/* Processo filho fecha seu lado de entrada do pipe*/
		close(fd[0]);
		
	printf("bye Word\n");
	sleep(2);}
	else {
		/* Processo pai fecha a saida do pipe */
		//printf("%d <> %d\n",fd[0],fd[1]);		
		close(fd[1]);
		sleep(2);
	printf("Hello Word\n");}
	return 0;
}
