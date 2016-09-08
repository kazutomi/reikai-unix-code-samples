/* proc/fork0.c */
#include <stdio.h>      /* fflush, printf */
#include <stdlib.h>     /* exit */
#include <sys/types.h>  /* fork, getpid */
#include <unistd.h>     /* fork, getpid, sleep */

int main(void) {
    int i = 1234;
    pid_t pid;

    pid = getpid();
    printf("before fork: pid=%d, i=%d\n", pid, i);
    fflush(stdout);
    fork(); 
    pid = getpid();
    printf("after fork: pid=%d, i=%d\n", pid, i);
    sleep(1);  /* このsleepは重要ではない */
    exit(0);
}
