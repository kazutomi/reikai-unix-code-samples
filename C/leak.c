#include <stdlib.h>	/* malloc */
int main (void)
{
    int *p = malloc (sizeof (int));
    *p = 10;
    p = malloc (sizeof (int));
}
