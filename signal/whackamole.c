#include <signal.h>	/* signal */
#include <stdio.h>	/* printf, putchar, setbuf */
#include <stdlib.h>	/* random, srandom */
#include <time.h>	/* time */
#include <unistd.h>	/* sleep */

int out = 0;
int hit = 0;
int miss = 0;

void whack(int sig)
{
    /* signal (SIGINT, whack); */
    if (out) {
        putchar('!');
        hit++;
        out = 0;
    } else {
        miss++;
    }
}

int main(void)
{
    int i;

    setbuf(stdout, NULL);
    srandom((unsigned long) time(NULL));
    signal(SIGINT, whack);

    printf("*** Whack-a-Mole ***\nInterrupt (^C) "
           "to hit the mole. Game time is 15 seconds.\n");
    for (i = 3; i > 0; i--) {
        printf("%d ", i);
        sleep(1);
    }
    printf("Start!\n");
    for (i = 0; i < 15; i++) {
        if (out) {
            if (random() % 3 < 2) {
                out = 0;
                putchar('_');
            }
        } else if (random() % 6 == 0) {
            out = 1;
            putchar('O');
        }
        sleep(1);
    }
    printf("\nFinish!\n");
    printf("hit = %d, miss = %d\n", hit, miss);
    printf("You score is %d points!\n", hit - miss);
    return 0;
}
