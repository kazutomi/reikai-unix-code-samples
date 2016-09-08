#include <stdio.h>	/* printf */
#include <stddef.h>	/* offsetof */
struct foo {
    char c1;
    int  i;
    char c2;
    long double ld;
};

int main (void)
{
    struct foo f;
    printf ("padding   <->c1: %d\n", offsetof (struct foo, c1));
    printf ("padding c1<-> i: %d\n", offsetof (struct foo, i)
                        - offsetof (struct foo, c1) - sizeof (f.c1));
    printf ("padding i <->c2: %d\n", offsetof (struct foo, c2)
                        - offsetof (struct foo, i) - sizeof (f.i));
    printf ("padding c2<->ld: %d\n", offsetof (struct foo, ld)
                        - offsetof (struct foo, c2) - sizeof (f.c2));
    printf ("char's alignment      : %d\n", __alignof__ (char));
    printf ("int's alignment       : %d\n", __alignof__ (int));
    printf ("long doule's alignment: %d\n", __alignof__ (long double));
}
