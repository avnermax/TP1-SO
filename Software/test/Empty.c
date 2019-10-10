
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#define TRUE 1
int main()
{
 int fd ;               /* descritor a ser duplicado  */
 int retour1=10 ;       /* valor de retorno de dup  */
 int retour2=10 ;       /* valor de retorno de dup2 */

     if ((fd=open("./fic",O_RDWR|O_CREAT|O_TRUNC,0666))==-1) {
          perror("Error open()") ;
          exit(1) ;
     }
     
     close(0) ;         /* fechamento da saida entrada stdin */

     if ((retour1 = dup(fd)) == -1) {  /* duplicacao */
          perror("Error dup()") ;
          exit(1) ;
     }

     if ((retour2 = dup2(fd,1)) == -1) {  /* duplicacao de stdout */
          perror("Error dup2()") ;
          exit(1) ;
     }   
     sleep(2);
     printf ("valor de retorno de dup()  : %d \n",retour1) ;
     sleep(2);
     printf ("valor de retorno de dup2() : %d \n",retour2) ;   
     exit(0);
}
