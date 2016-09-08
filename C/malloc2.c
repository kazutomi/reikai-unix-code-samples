#include <stdio.h>	/* printf */
#include <stdlib.h>	/* atoi, exit */
#define  N 10
int main (int argc, char *argv [])
{
    int i, data [N];
    if (argc - 1 > N) 
	exit (1);
    for (i = 1; i < argc; i++) {
	data [i - 1] = atoi (argv [i]);
    } 
    for (i = 1; i < argc; i++) {
	printf ("%d\n", data [i - 1]);
    }
}
