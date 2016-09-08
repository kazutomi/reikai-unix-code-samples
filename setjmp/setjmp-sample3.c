#include <setjmp.h>	/* longjmp */
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */
static jmp_buf env;
void foo (void)
{
    longjmp (env, 1);
}
int main (int argc, char *argv [])
{
    int i = argc;
    int (*setjmp_p)(jmp_buf) = setjmp;

    if (setjmp_p (env) != 0) {
        printf ("i = %d\n", i);
        exit (0);
    }
    i = argc + 99;
    foo ();
    return i;
}
