#include <stdio.h>	/* printf */
#include <string.h>	/* strcpy */
int main (void)
{
    char s1 [] = "hello", s2 [10];
    strcpy (s2, s1);
    printf ("%s\n", s2);
}
