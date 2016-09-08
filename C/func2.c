#include <stdio.h>	/* printf */
int add (int x, int y) { return x + y; }
int sub (int x, int y) { return x - y; }
int mul (int x, int y) { return x * y; }
int div (int x, int y) { return x / y; }
int (*arith[4])(int, int) = {add, sub, mul, div};
int main (void)
{
    printf ("%d, %d, %d, %d\n", 
            arith[0] (20, 10), arith[1] (20, 10),
	    arith[2] (20, 10), arith[3] (20, 10));
}
