#include <stdio.h>	/* perror, printf */
#include <stdlib.h>	/* exit, free, malloc */
int main (void)
{
    int *p = malloc (sizeof (int));
    if (p == NULL) { 
        perror ("malloc"); exit (1);
    }
    *p = 99;
    printf ("%d\n", *p);
    free (p); 
}
