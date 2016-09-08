#include <stdio.h>	/* printf, snprintf */
char *itoa (int i)
{
    static char buf [1024];
    snprintf (buf, sizeof (buf), "%d", i);
    return buf;
}

int main (void)
{
    char *p = itoa (1234);
    printf ("p=%s\n", p);
}
