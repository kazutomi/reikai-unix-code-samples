#include <stdio.h>	/* fgets, printf */
int main (void)
{
    char buf [BUFSIZ];
    printf ("Please type your name: ");
    fgets (buf, sizeof (buf), stdin);
    printf ("hello, %s", buf);
}
