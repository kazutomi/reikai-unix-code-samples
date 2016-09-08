#include <stdio.h>	/* printf */
#include <stdlib.h>	/* atoi, free, malloc */
int main (int argc, char *argv [])
{
    int i, *data;
    data = malloc (sizeof (int) * (argc - 1));
    for (i = 1; i < argc; i++) {
	data [i - 1] = atoi (argv [i]);
    } 
    for (i = 1; i < argc; i++) {
	printf ("%d\n", data [i - 1]);
    }
    free (data);
}
