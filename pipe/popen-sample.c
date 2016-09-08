#include <stdio.h>	/* fgets, pclose, perror, popen, printf */
#include <stdlib.h>	/* exit */
int main (void)
{
    FILE *fp;
    char buf [1024];
    if ((fp = popen ("ls -l *.c | wc", "r")) == NULL) {
        perror ("popen");
        exit (1);
    }
    fgets (buf, sizeof (buf), fp);
    printf ("%s", buf);
    pclose (fp);
}
