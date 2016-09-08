#include <stdio.h>	/* printf */
struct rectangle {
    int x, y;
    int width, height;
};

void rect_print (struct rectangle *p)
{
    printf ("x=%d, y=%d, width=%d, height=%d\n",
	    p->x, p->y, p->width, p->height);
}

int rect_area (struct rectangle *p)
{
    return p->width * p->height;
}

void rect_move1 (struct rectangle *p, int dx, int dy)
{
    p->x += dx;
    p->y += dy;
}

struct rectangle
rect_move2 (struct rectangle r, int dx, int dy)
{
    r.x += dx;
    r.y += dy;
    return r;
}

int point_is_included (struct rectangle *p, int x, int y)
{
    return (p->x <= x) && (x <= p->x + p->width)
	&& (p->y <= y) && (y <= p->y + p->height);
}

int rect_is_overlapped2 (struct rectangle *p1, struct rectangle *p2)
{
    return point_is_included (p1, p2->x,             p2->y)
	|| point_is_included (p1, p2->x + p2->width, p2->y)
	|| point_is_included (p1, p2->x,             p2->y + p2->height)
	|| point_is_included (p1, p2->x + p2->width, p2->y + p2->height);
}

int rect_is_overlapped (struct rectangle *p1, struct rectangle *p2)
{
    return rect_is_overlapped2 (p1, p2) || rect_is_overlapped2 (p2, p1);
}

int main (void)
{
    struct rectangle r1 = {10, 20, 30, 40};
    struct rectangle r2 = {20, 10, 30, 40};
    rect_print (&r1);
    rect_print (&r2);
    printf ("%d\n", rect_area (&r1));
    rect_move1 (&r1, 5, 6);
    rect_print (&r1);
    r1 = rect_move2 (r2, 6, 5);
    rect_print (&r1);
    printf ("%d\n", rect_is_overlapped (&r1, &r1));
    printf ("%d\n", rect_is_overlapped (&r1, &r2));
}
