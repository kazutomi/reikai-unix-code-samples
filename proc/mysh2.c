/* proc/mysh2.c */
#include <stdio.h>      /* feof, ferror, fputs, perror */
#include <stdlib.h>     /* exit */
#include <sys/types.h>  /* fork, wait */
#include <sys/wait.h>   /* wait */
#include <unistd.h>     /* execvp, fork */
#include "mysub.h"
#include "myvec.h"

enum {
    MAXARGV = 100,
};

int main(void) {
    char cmd[1024];
    char *av[MAXARGV];
    int ac, status;
    pid_t cpid;

    for (;;) {
        getstr("@ ", cmd, sizeof(cmd));
        if (feof(stdin)) {
            exit(0);
        } else if (ferror(stdin)) {
            perror("getstr");
            exit(1);
        }
        if ((ac = strtovec(cmd, av, MAXARGV)) > MAXARGV) {
            fputs("too many arguments\n", stderr);
            continue;
        }
        if (ac == 1)    /* 入力なし */
            continue;
        if ((cpid = fork()) == -1) {
            perror("fork");
            continue;
        } else if (cpid == 0) {
            /* 子プロセス */
            execvp(av[0], av);
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
