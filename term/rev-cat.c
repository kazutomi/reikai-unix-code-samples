#include <stdio.h>	/* fclose, fgets, fopen, fputs, printf, putchar */
#include <string.h>	/* strlen, strstr */
#define  REV   "\033[7m"
#define  SGR0  "\033[0;10m"

int main (int argc, char *argv [])
{
    FILE *fp;
    char buf [1024];
    char *pattern  = argv [1];
    char *filename = argv [2];

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
            printf (REV "%s" SGR0, pattern);
            p += strlen (pattern);
        }
    }
    fclose (fp);
}
