#include <stdlib.h>	/* free, malloc */
int main (void)
{
    int *p = malloc (sizeof (int));
    free (p);
    *p = 99;
}
