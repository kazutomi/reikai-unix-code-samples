#include <stdio.h>	/* printf, snprintf */
#include <stdlib.h>	/* free, malloc */
char *itoa (int i)
{
    int n = snprintf (NULL, 0, "%d", i);
    char *buf = malloc (n + 1); 
    snprintf (buf, n + 1, "%d", i);
    return buf;
}

int main (void)
{
    char *p = itoa (1234);
    printf ("p=%s\n", p);
    free (p);
}

