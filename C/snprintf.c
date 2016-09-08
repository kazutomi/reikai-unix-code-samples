#include <stdio.h>	/* printf, snprintf */
int main (int argc, char *argv[])
{
    char buf [BUFSIZ];
    snprintf (buf, sizeof (buf), "%s", argv [0]);
    printf ("%s\n", buf);
}
