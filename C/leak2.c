#include <stdio.h>	/* printf */
#include <stdlib.h>	/* free, malloc */
struct point { int x, y; };

struct point *
make_point (int x, int y)
{
    struct point *p = malloc (sizeof (struct point));
    p->x = x;
    p->y = y;
    return p;
}

int main (void)
{
    int x = 0, y = 0;
    struct point *new;
    while (1) {
	new = make_point (x, y);
	printf ("(%d, %d)\n", new->x, new->y);
	x++, y++;
	free (new);
    }
}
