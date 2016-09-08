#include <stdio.h>	/* printf */
#include <unistd.h>	/* sleep */
int main (void)
{
    int i;

    printf ("enter main\n");
    sleep (1);
    printf ("step 1 failed\n");
    sleep (1);
    for (i = 2; i < 1000; i++) {
        printf ("step %d succeeded\n", i);
        sleep (1);
    }
    printf ("exit main\n");
}
