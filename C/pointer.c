#include <stdio.h>	/* printf */
int main (void)
{
    char c, *p=&c;
    *p = 'A';
    printf ("%c\n", *p);
}
