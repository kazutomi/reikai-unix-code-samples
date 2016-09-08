/* proc/fork1.c */
#include <stdio.h>      /* fflush, perror, printf, putchar */
#include <stdlib.h>     /* exit */
#include <sys/types.h>  /* fork */
#include <unistd.h>     /* fork, sleep */

int main(void) {
    int i;
    pid_t cpid;

    if ((cpid = fork()) == -1) {
        /* エラー */
        perror("fork");
        exit(1);
    } else if (cpid == 0) {
        /* 子プロセス */
        for (i = 0; i < 10; i++) {
            printf("<%d>", i);
            fflush(stdout);
            sleep(1);  /* 1秒ごとに表示 */
        }
        exit(0);  /* 子プロセスのexit */
    }
    /* 親プロセス */
    for (i = 9; i >= 0; i--) {
        printf("[%d]", i);
        fflush(stdout);
        sleep(2);  /* 2秒ごとに表示 */
    }
    putchar('\n');
    exit(0);  /* 親プロセスのexit */
}
