#include <stdio.h>	/* fwrite */
int main (void)
{
    int i = 0x12345678;
    fwrite (&i, sizeof (i), 1, stdout);
}
