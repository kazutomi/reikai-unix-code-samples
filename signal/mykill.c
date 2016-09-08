#include <sys/types.h>	/* kill */
#include <stdlib.h>	/* atoi */
#include <signal.h>	/* kill */
int main (int argc, char *argv [])
{
    pid_t pid = atoi (argv [1]);
    kill (pid, SIGTERM);
}
