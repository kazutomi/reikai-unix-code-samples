/* proc/exec2.c */
#include <limits.h>     /* PATH_MAX */
#include <stdio.h>      /* fflush, perror, printf */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /* execv */
#include "mysub.h"

int main(void) {
    char buf[PATH_MAX];
    char *av[4] = { "ls", "-l", buf, NULL };

    getstr("directory? ", buf, sizeof(buf));
    printf("Files in %s:\n", buf);
    fflush(stdout);
    execv("/bin/ls", av);
    perror("execv");
    exit(1);
}
