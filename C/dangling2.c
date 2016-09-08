#include <stdio.h>	/* printf */
#include <stdlib.h>	/* free, malloc */
struct point { int x, y; };
int main (void)
{
    struct point *p = malloc (sizeof (struct point));
    int *q = &p->x;
    p->x = 10; p->y = 20;
    printf ("%d\n", *q);
    free (p);
}
