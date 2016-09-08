#include <setjmp.h>	/* longjmp, setjmp */
#include <stdio.h>	/* printf */
static jmp_buf env;
void foo1 (void)
{
    if (setjmp  (env) == 1)
        printf ("hello\n");
}
void foo2 (void)
{
    longjmp (env, 1);
}
int main (void)
{
    foo1 ();
    foo2 ();
}
