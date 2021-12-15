#include <assert.h>	/* assert */
#include <stdio.h>	/* printf */

union any_t { 
    char   c;
    int    i;
    float  f;
    double d;
};

enum any_t_discr { ANY_CHAR, ANY_INT, ANY_FLOAT, ANY_DOUBLE };

union any_t
any_add (union any_t x, union any_t y, enum any_t_discr discr)
{
    union any_t ret;
    switch (discr) {
    case ANY_CHAR:   ret.c = x.c + y.c; break;
    case ANY_INT:    ret.i = x.i + y.i; break;
    case ANY_FLOAT:  ret.f = x.f + y.f; break;
    case ANY_DOUBLE: ret.d = x.d + y.d; break;
    default:
	assert (0);
    }
    return ret;
}

int main (void)
{
    union any_t a1, a2, a3;
    a1.i = 999;
    printf ("%d\n", a1.i);
    a2.i = 1;
    a3 = any_add (a1, a2, ANY_INT);
    printf ("%d\n", a3.i);
}
