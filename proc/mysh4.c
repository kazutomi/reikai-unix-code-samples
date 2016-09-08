/* proc/mysh4.c */
#include <sys/types.h>  /* fork, open, wait */
#include <stdio.h>      /* feof, ferror, fputs, perror */
#include <stdlib.h>     /* exit */
#include <string.h>     /* strcmp */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/wait.h>   /* wait */
#include <unistd.h>     /* close, execvp, fork */
#include "mysub.h"
#include "myvec.h"

enum {
    MAXARGV = 100,
};

int main(void) {
    char cmd[1024];
    char *av[MAXARGV], *outfile;
    int i, ac, status;
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
            fputs("argument list too long\n", stderr);
            continue;
        }
        ac--;
        if (ac == 0)    /* 入力なし */
            continue;
        /*
         * 出力切替の処理
         */
        outfile = NULL;
        for (i = 0; i < ac; i++) {
            if (!strcmp(av[i], ">")) {
                av[i] = NULL;           /* ここがコマンド引数の終わり */
                ac = i;
                outfile = av[i+1];      /* XXX: ヌルポインタかも */ 
                /* （av の残りは無視される） */
                break;
            }
        }
        if ((cpid = fork()) == -1) {
            perror("fork");
            continue;
        } else if (cpid == 0) {
            /* 子プロセス */
            if (outfile != NULL) {
                close(1);               /* 標準出力を閉じる */
                if (open(outfile, O_WRONLY|O_CREAT|O_TRUNC, 0666) == -1) {
                    perror(outfile);
                    exit(1);
                }
            }
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
