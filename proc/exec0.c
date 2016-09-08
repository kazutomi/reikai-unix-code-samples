/* proc/exec0.c */
#include <stdio.h>      /* fflush, printf */
#include <unistd.h>     /* execlp */

int main(void) {
    printf("Invoking ls.\n");
    fflush(stdout);
    execlp("ls", "ls", (char *)0);
    printf("Done.\n");  /* execlp に成功したら実行されない */
    return 0;
}
