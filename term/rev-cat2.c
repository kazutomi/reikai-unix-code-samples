#include <curses.h>	/* putp, setupterm, tigetstr */
#include <stdio.h>	/* fclose, fgets, fopen, fputs, printf, putchar */
#include <stdlib.h>	/* free */
#include <string.h>	/* strdup, strlen, strstr */
#include <term.h>	/* putp, setupterm, tigetstr */

int main (int argc, char *argv [])
{
    FILE *fp;
    char buf [1024], *rev, *sgr0;
    char *pattern  = argv [1];
    char *filename = argv [2];

    setupterm (NULL, 0, NULL);
    rev  = strdup (tigetstr ("rev"));
    sgr0 = strdup (tigetstr ("sgr0"));

    fp = fopen (filename, "r");
    while (1) {
        char *p = buf, *q;
        if (fgets (buf, sizeof (buf), fp) == NULL)
            break;
        while (1) {
            q = strstr (p, pattern);
            if (q == NULL) {
                fputs (p, stdout);
                break;
            }
            while (p != q)
                putchar (*p++);
            putp (rev);
            printf ("%s", pattern);
            putp (sgr0);
            p += strlen (pattern);
        }
    }
    free (rev);
    free (sgr0);
    fclose (fp);
}
