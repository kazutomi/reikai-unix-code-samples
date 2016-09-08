/* proc/getpath.c */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* getenv */

int main(void) {
    char *pathstr;

    if ((pathstr = getenv("PATH")) != NULL) {
        printf("PATH = %s\n", pathstr);
    } else {
        printf("PATH not set\n");
    }
    return 0;
}
