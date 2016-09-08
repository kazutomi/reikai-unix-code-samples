/* proc/mysh0.c */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <sys/types.h>  /* fork, wait */
#include <sys/wait.h>   /* wait */
#include <unistd.h>     /* execlp, fork */
#include "mysub.h"

int main(void) {
    char cmd[1024];
    int status;

    for (;;) {
        getstr("@ ", cmd, sizeof(cmd));
        if (fork() == 0) { 
            /* 子プロセス */
            execlp(cmd, cmd, (char *)0);
            perror(cmd);
            exit(1);
        }
        /* 親プロセス */
        if (wait(&status) == (pid_t)-1) {
            perror("wait");
            exit(1);
        }
    }
    exit(0);
}
