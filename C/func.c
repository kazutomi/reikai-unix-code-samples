#include <stdio.h>	/* printf */
int add (int x, int y) { return x + y; }
int mul (int x, int y) { return x * y; }

int main (void)
{
    int (*func) (int, int);
    func = add;
    printf ("%d\n", func (10, 20));
    func = mul;
    printf ("%d\n", func (10, 20));
}
