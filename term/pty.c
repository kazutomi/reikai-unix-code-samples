#define _XOPEN_SOURCE	/* grantpt, posix_openpt, ptsname, unlockpt */
#include <sys/types.h>	/* fork, kill, open, read, setsid, write */
#include <signal.h>	/* kill */
#include <stdlib.h>	/* exit, grantpt, posix_openpt, ptsname, unlockpt */
#include <sys/ioctl.h>	/* ioctl */
#include <sys/select.h>	/* FD_ISSET, FD_SET, FD_ZERO, select */
#include <sys/stat.h>	/* open */
#include <fcntl.h>	/* grantpt, open, posix_openpt, ptsname, unlockpt */
#include <sys/uio.h>	/* read, write */
#include <termios.h>	/* tcgetattr, tcsetattr */
#include <unistd.h>	/* close, dup2, execvp, fork, read, setsid, tcgetattr, tcsetattr, write */

int ptym_open (void)
{
    int fd_master = posix_openpt (O_RDWR);
    grantpt (fd_master);
    unlockpt (fd_master);
    return fd_master;
}

int ptys_open (int fd_master)
{
    int fd_slave = open (ptsname (fd_master), O_RDWR);
    return fd_slave;
}

struct termios set_tty_raw (int fd)
{
    struct termios old, new;

    tcgetattr (fd, &old);
    new = old;
    new.c_iflag &= ~(BRKINT | ICRNL | INLCR | IGNCR | INPCK | ISTRIP | IXON);
    new.c_oflag &= ~(OPOST);
    new.c_lflag &= ~(ECHO   | ECHOE | ECHONL | ICANON | IEXTEN | ISIG);
    new.c_cflag &= ~(PARENB | CSIZE);
    new.c_cflag |= CS8;
    new.c_cc [VMIN]  = 1;
    new.c_cc [VTIME] = 0;
    tcsetattr (fd, TCSANOW, &new);
    return old;
}

pid_t pty_fork (int fd_master)
{
    int fd_slave;
    struct termios  termios_slave;
    pid_t pid;

    termios_slave = set_tty_raw (STDIN_FILENO);

    pid = fork ();
    if (pid == 0) {
        setsid ();
        fd_slave  = ptys_open (fd_master);
        ioctl (fd_slave, TIOCSCTTY, (char *)0);
        close (fd_master);
        tcsetattr (fd_slave, TCSANOW, &termios_slave);

        dup2 (fd_slave, STDIN_FILENO);
        dup2 (fd_slave, STDOUT_FILENO);
        dup2 (fd_slave, STDERR_FILENO);
        if (fd_slave > STDERR_FILENO)
            close (fd_slave);
        return 0;
    } else {
        return pid;
    }
}

void loop (int rfd1, int wfd1, int rfd2, int wfd2, pid_t pid)
{
    int nbytes;
    char buf [1024];
    fd_set rfd_set;

    while (1) {
        FD_ZERO (&rfd_set);
        FD_SET (rfd1, &rfd_set);
        FD_SET (rfd2, &rfd_set);
        select ((rfd1 > rfd2 ? rfd1 : rfd2) + 1, &rfd_set, NULL, NULL, NULL);

        if (FD_ISSET (rfd1, &rfd_set)) {
            nbytes = read (rfd1, buf, sizeof (buf));
            if (nbytes <= 0) {
                kill (pid, SIGHUP);
                exit (1);
            }
            write (wfd1, buf, nbytes);
        }
        if (FD_ISSET (rfd2, &rfd_set)) {
            nbytes = read (rfd2, buf, sizeof (buf));
            if (nbytes <= 0) exit (1);
            write (wfd2, buf, nbytes);
        }
    }
}

int main (int argc, char *argv[])
{
    int fd_master = ptym_open ();
    pid_t pid = pty_fork (fd_master);
    if (pid == 0) {
        execvp (argv [1], argv + 1);
    } else {
        loop (STDIN_FILENO, fd_master, fd_master, STDOUT_FILENO, pid);
    }
}
