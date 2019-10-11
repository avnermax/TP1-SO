#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h> // open function
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<getopt.h>
#include<stdbool.h>

#define STDOUT 1
#define STDERR 2

int main(int argc, char ** argv) {

    //PARENT
    pid_t pid, wpid, pid2;
    int status, status2;
    const int MIN_BUFF_SIZE = 1024;

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
    }
    printf("After creating pipe \n");

    pid = fork();

    if (pid == 0) {
        // First child process (parent of second child)
        printf("First child process before fork again\n");
        pid2 = fork();
        if (pid2 == 0) {
            printf("Second child process begin\n");
            //second child we need to execute the left command

            close(fd[0]);
            printf("Second child |Redirect stdout > stdin\n");
            dup2(fd[1], STDOUT_FILENO); // Redirect stdout to stdin
            close(fd[1]); // NEW

            //test data
            char * test[3];
            test[0] = "ls\0";
            test[1] = "-l\0";
            test[2] = NULL;

            //TODO test to remove
            if (execvp(test[0], test) == -1) {
                perror("shell launch error : error in child process > execvp failed \n");
                exit(errno);
            }
            printf("Second child | After execvp\n");
            exit(errno);

        } else if (pid < 0) {
            perror("shell launch error : error forking second child");
        } else {
            do {
                wpid = waitpid(pid2, & status2, WUNTRACED);
                printf("Second parent\n");
                //Parent
                close(fd[1]);
                printf("Second parent | Redirect stdout > stdin\n");
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]); // NEW
                printf("Second parent | After Redirect stdout > stdin\n");

                //test data : grep toto
                char * test2[3];
                test2[0] = "grep\0";
                test2[1] = "toto\0";
                test2[2] = NULL;
                printf("Second parent | Av dup2 fd stdout\n");

                close(fd[0]); // NEW
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);

                printf("Second parent | Ap dup2 fd stdout\n");
                if (execvp(test2[0], test2) == -1) {
                    perror("shell launch error : error in child process > execvp failed \n");
                    exit(errno);
                }
                exit(errno);
            } while (!WIFEXITED(status2) && !WIFSIGNALED(status2));
        }

    } else if (pid < 0) {
        // Error forking
        perror("shell launch error : error forking");
    } else {
        do {
            close(fd[1]); //NEW close the write end of the pipe in the parent
            //wait child process to finish it execution. So, according to project requirements,
            //we need to print the result of the command after the child process is finished
            wpid = waitpid(pid, & status, WUNTRACED);
            printf("Finished waiting for %d\n", wpid);

            char * line_to_display = malloc(1);
            line_to_display = '\0';

            if (status != 0) {
                printf("Status : %d\n", status);

            } else {
                printf("We are in the first parent \n");
                ssize_t bytes_read = 1;
                do {

                    line_to_display = realloc(line_to_display, 1024);
                    //sizeof(char) = 1 so don't need to do MIN_BUFF_SIZE * sizeof(char)
                    bytes_read = read(fd[0], line_to_display, 1024);

                } while (bytes_read > 0);

                printf("%s\n", line_to_display);
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    printf("Finish ! \n");
    return 0;
}
