/* proc/mysh5.c */
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
    char *userinput[MAXARGV], *av[MAXARGV], *infile, *outfile;
    int i, nwords, ac, status;
    pid_t cpid;

    for (;;) {
        getstr("@ ", cmd, sizeof(cmd));
        if (feof(stdin)) {
            exit(0);
        } else if (ferror(stdin)) {
            perror("getstr");
            exit(1);
        }
        if ((nwords = strtovec(cmd, userinput, MAXARGV)) > MAXARGV) {
            fputs("too many arguments\n", stderr);
            continue;
        }
        nwords--;
        if (nwords == 0)        /* 入力なし */
            continue;

        /* 入出力切替の処理 */
        ac = 0;
        infile = outfile = NULL;
        for (i = 0; i < nwords; i++) {
            if (strcmp(userinput[i], ">") == 0) {
                outfile = userinput[i+1];       /* XXX: NULLポインタかも */
                i++;
            } else if (strcmp(userinput[i], "<") == 0) {
                infile = userinput[i+1];        /* XXX: NULLポインタかも */
                i++;
            } else {
                av[ac++] = userinput[i];
            }
        }
        av[ac] = NULL;

        if ((cpid = fork()) == -1) {
            perror("fork");
            continue;
        } else if (cpid == 0) {
            /* 子プロセス */
            if (infile != NULL) {
                close(0);               /* 標準入力を閉じる */
                if (open(infile, O_RDONLY) == -1) {
                    perror(infile);
                    exit(1);
                }
            }
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
