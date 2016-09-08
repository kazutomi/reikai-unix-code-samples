/* stdio/launchx.c */
#include <stdio.h>      /* printf */
#include <unistd.h>     /* sleep */

int main(void) {
    int i;

    for (i = 5; i > 0; i--) {
        printf("%d", i);
        sleep(1);
    }
    printf(" go!\n");
    return 0;
}
