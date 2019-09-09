
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

typedef struct Ordem {
	char *name;
        int argc;
        char *argv[10];
}Command;

void frac_summons(char *summons, Command *act ){		
/*Comment:
	Usa strtok pra separar a linha de comando em palavras p/ consulta.
*/	
	char *aux;
	aux= strtok (summons," \n");	
	int i= 0;
	while (aux != NULL) {
		act->argv[i] = aux;
		aux= strtok (NULL, " \n");
		i++;
	}
	act->argc = i;
	act->argv[i++] = NULL;
}


int main(){
	FILE *fp;
int status;
char path[250];


fp = popen("ls *", "r");
if (fp == NULL)
    /* Handle error */;


while (fgets(path, 250, fp) != NULL)
    printf("%s", path);


status = pclose(fp);
if (status == -1) {
    /* Error reported by pclose() */
    
} else {
    /* Use macros described under wait() to inspect `status' in order
       to determine success/failure of command executed by popen() */
    
}
}
