#include <setjmp.h>	/* longjmp, setjmp */
#include <stdio.h>	/* fprintf, putchar */
#include <unistd.h>	/* sleep */

static jmp_buf env;

void print_i (int i) {
    fprintf (stderr, "%d ", i);
    if (i >= 5) {
        putchar ('\n');
        longjmp (env, 1);
    }    
}

int main (void)
{
    int i;
    setjmp (env);
    for (i = 0; ; i++) {
        print_i (i);
        sleep (1);
    }
}
