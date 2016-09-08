/* proc/exec1.c */
#include <limits.h>     /* PATH_MAX */
#include <stdio.h>      /* fflush, perror, printf */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /* execl */
#include "mysub.h"

int main(void) {
    char buf[PATH_MAX];

    getstr("directory? ", buf, sizeof(buf));
    printf("Files in %s:\n", buf);
    fflush(stdout);
    execl("/bin/ls", "ls", "-l", buf, (char *)0);
    perror("execl");
    exit(1);
}
