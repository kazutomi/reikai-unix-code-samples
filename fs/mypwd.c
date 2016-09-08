/* fs/mypwd.c */
#include <limits.h>     /* PATH_MAX */
#include <stdio.h>      /* perror, printf */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /* getcwd */

int main(void) {
    char buf[PATH_MAX+1];

    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd");
        exit(1);
    }
    printf("%s\n", buf);
    return 0;
}
