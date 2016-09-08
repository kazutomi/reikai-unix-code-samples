#include <stdio.h>	/* printf */

int check_bit (unsigned int x, int n)
{
    return (x & (1 << n)) != 0;
}

int main (void)
{
    int i;
    for (i = 0; i < 31; i++) {
	printf ("%d", check_bit (0x20, i));
    }
    printf ("\n");
}
