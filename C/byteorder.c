#include <stdio.h>	/* printf */
int main (void)
{
    int i = 0x12345678;
    unsigned char *c = (unsigned char *)&i;
    printf ("%x:%x:%x:%x\n", c[0],  c[1],  c[2],  c[3]);
}
