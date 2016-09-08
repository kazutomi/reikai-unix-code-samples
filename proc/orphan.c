/* proc/orphan.c */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit */
#include <sys/types.h>  /* fork, getpid, getppid */
#include <unistd.h>     /* fork, getpid, getppid, sleep */

int main(void) {
    if (fork() == 0) {
        /* 子プロセス */
        sleep(3);
        printf("\nmy parent is now pid %d\n", getppid());
        exit(0);
    }
    /* 親プロセス */
    printf("parent process, pid %d\n", getpid());
    exit(0);
}
