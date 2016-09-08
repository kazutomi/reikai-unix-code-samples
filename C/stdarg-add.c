#include <stdio.h>      /* printf */
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
int add (int arg_num, ...)
{
    int      i, sum = 0;
    va_list  pvar;
    va_start (pvar, arg_num);
    for (i = 0; i < arg_num; i++) {
        sum += va_arg (pvar, int);
    }
    va_end (pvar);
    return sum;
}

int main (void)
{
    printf ("%d, %d, %d, %d\n", add (0), add (1, 10),
            add (2, 10, 20), add (3, 10, 20, 30));
}
