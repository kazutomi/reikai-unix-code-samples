#include <stdio.h>	/* printf */
struct foo {char a; int b;} f;
int main (void)
{
    printf ("%d, %d, %d\n",  sizeof(char),  sizeof(int), sizeof(struct foo));
    printf ("%p, %p, %p\n", &f, &f.a, &f.b);
}
