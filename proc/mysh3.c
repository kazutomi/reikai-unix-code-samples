/* proc/mysh3.c */
#include <errno.h>      /* errno */
#include <stdio.h>      /* feof, ferror, fprintf, fputs, perror */
#include <stdlib.h>     /* exit */
#include <string.h>     /* strcmp */
#include <sys/types.h>  /* fork, waitpid */
#include <sys/wait.h>   /* waitpid */
#include <unistd.h>     /* execvp, fork */
#include "mysub.h"
#include "myvec.h"      /* strtovecのため（演習問題\ref{practice:任意個引数シェル}） */

enum {
    MAXARGV = 100,
};

int main(void) {
    char cmd[1024];
    char *av[MAXARGV];
    int ac, status, bg;
    pid_t cpid, zpid;

    for (;;) {
        /* 幽霊がいたらwaitする */
        while ((zpid = waitpid(-1, &status, WNOHANG)) > 0)      /* (1) */
            fprintf(stderr, "process %d salvaged\n", zpid);
        if (zpid == -1 && errno != ECHILD) {
            perror("waitpid(2)");
            exit(1);
        }
        getstr("@ ", cmd, sizeof(cmd));
        if (feof(stdin)) {
            exit(0);
        } else if (ferror(stdin)) {
            perror("getstr");
            exit(1);
        }
        if ((ac = strtovec(cmd, av, MAXARGV)) > MAXARGV) {
            fputs("argument list too long\n", stderr);
            continue;
        }
        ac--;   /* 最後のヌルポインタの分を省く */
        if (ac == 0)    /* 入力がなかった */
            continue;
        if (!strcmp(av[ac-1], "&")) {
            av[ac-1] = NULL;
            ac--;
            bg = 1;
            if (ac == 0) {
                fputs("invalid null command\n", stderr);
                continue;
            }
        } else {
            bg = 0;
        }
        if ((cpid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if (cpid == 0) {
            /* 子プロセス */
            execvp(av[0], av);
            perror(av[0]);
            exit(1);
        }
        /* 親プロセス */
        if (!bg) {
            if (waitpid(cpid, &status, 0) == (pid_t)-1) {       /* (2) */
                perror("waitpid(1)");
                exit(1);
            }
            /* 前面のプロセスが終了した */
            fprintf(stderr, "process %d finished\n", cpid);
        }
    }
    exit(0);
}
