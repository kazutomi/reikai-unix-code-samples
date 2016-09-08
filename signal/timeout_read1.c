#include <signal.h>	/* sigaction, sigemptyset */
#include <stdio.h>	/* fflush, printf */
#include <sys/types.h>	/* read, write */
#include <sys/uio.h>	/* read, write */
#include <unistd.h>	/* alarm, read, write */

void alarm_handler (int sig) {  }

ssize_t timeout_read (int fd, void *buf, size_t count, int seconds)
{
    int ret;
    struct sigaction act;
    act.sa_handler = alarm_handler;
    act.sa_flags   = 0;
    sigemptyset (&act.sa_mask);
    sigaction (SIGALRM, &act, NULL);
    alarm (seconds);
    ret = read (fd, buf, count);
    alarm (0);
    return ret;
}

int main (void)
{
    char buf [1024];
    ssize_t ret;
    printf ("Please type your name: ");
    fflush (stdout);
    ret = timeout_read (STDIN_FILENO, buf, sizeof (buf), 3);
    if (ret == -1)
        printf ("timed out\n");
    else
        write (STDOUT_FILENO, buf, ret);
}
