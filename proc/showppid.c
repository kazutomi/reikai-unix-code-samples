/* proc/showppid.c */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit */
#include <sys/types.h>  /* fork, getpid, getppid */
#include <unistd.h>     /* fork, getpid, getppid, sleep */

int main(void) {
    pid_t pid;

    if ((pid = fork()) == 0) { 
        /* 子プロセス */
        printf("child: parent PID = %d, my PID = %d\n",
                                      getppid(), getpid());
        exit(0);
    } else {
        /* 親プロセス */
        printf("parent: my PID = %d, child PID = %d\n", getpid(), pid);
        for (;;)
            sleep(1);
    }
}
