/* proc/showenv.c */
#include <stdio.h>      /* printf */

extern char **environ;  /* 外部変数 environ を参照するため */

int main(void) {
    char **p = environ;

    while (*p != NULL) {
        printf("%s\n", *p);
        p++;
    }
    return 0;
}
