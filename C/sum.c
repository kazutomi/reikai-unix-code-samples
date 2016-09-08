#include <stdio.h>	/* printf */
#include <stdlib.h>	/* atoi */
int main (int argc, char *argv [])
{
    int i, sum = 0;
    for (i = 0; i < argc; i++) {
        sum += atoi (argv [i]);
    }
    printf ("%d\n", sum);
}
