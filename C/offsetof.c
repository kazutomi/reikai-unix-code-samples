#include <stdio.h>	/* printf */
#include <stddef.h>	/* offsetof */
struct foo {char a; int b;};
int main (void)
{
    printf ("%d\n", offsetof (struct foo, b));
}
