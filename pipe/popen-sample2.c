#include <stdio.h>	/* fprintf, pclose, popen */
int main (void)
{
    FILE *fp;
    fp = popen ("tee foo1 > foo2", "w");
    fprintf (fp, "Hello, world\n");
    pclose (fp);
}
