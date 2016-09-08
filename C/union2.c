#include <assert.h>	/* assert */
#include <stdio.h>	/* fprintf, printf */

union any_t {
    char   c;
    int    i;
    float  f;
    double d;
};
enum any_discr { ANY_CHAR, ANY_INT, ANY_FLOAT, ANY_DOUBLE };
struct any_t2 {
    enum any_discr discr;
    union any_t u;
};


struct any_t2
any_add (struct any_t2 x, struct any_t2 y)
{
    struct any_t2 ret;
    if (x.discr != y.discr) {
	fprintf (stderr, "different type addition");
        assert (0);
    }
    ret.discr = x.discr;
    switch (x.discr) {
    case ANY_CHAR:   ret.u.c = x.u.c + y.u.c; break;
    case ANY_INT:    ret.u.i = x.u.i + y.u.i; break;
    case ANY_FLOAT:  ret.u.f = x.u.f + y.u.f; break;
    case ANY_DOUBLE: ret.u.d = x.u.d + y.u.d; break;
    default:
	assert (0);
	break;
    }
    return ret;
}

int main (void)
{
    struct any_t2 a1, a2, a3;
    a1.u.i = 999;
    a1.discr = ANY_INT;
    printf ("%d\n", a1.u.i);
    a2.u.i = 1;
    a2.discr = ANY_INT;
    a3 = any_add (a1, a2);
    printf ("%d\n", a3.u.i);
}
