/* proc/setuser.c */
#include <stdio.h>      /* perror, printf */
#include <stdlib.h>     /* exit, getenv, setenv */

int main(void) {
    printf("USER is %s\n", getenv("USER")); 
    if (setenv("USER", "johndoe", 1) == -1) {
        perror("setenv");
        exit(1);
    }
    printf("USER is now %s\n", getenv("USER")); 
    return 0;
}
