#include <stdio.h>	/* fflush, printf */
#include <unistd.h>	/* alarm */
void loop (void)
{
    int i;
    for (i = 0; i < 0xFFFFFF; i++)
        ;
}
int main (void)
{
    alarm (3);
    while (1) {
        loop ();
        printf (".");
        fflush (stdout);
    }
}
