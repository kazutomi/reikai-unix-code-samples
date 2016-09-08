#include <stdio.h>	/* fflush, printf */
#include <stdlib.h>	/* atoi */
#include <unistd.h>	/* sleep */
int main (int argc, char *argv[])
{
    int i = 0, n = atoi (argv [1]);
    char c [] = {'.', 'o', 'O'};
    for (i = 0; i < n; i++) {
        printf ("%c\033[D", c [i % 3]);
        fflush (stdout);
        sleep (1);
    }
}
