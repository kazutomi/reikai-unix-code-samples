/* llio/seekread.c */
#include <sys/types.h>  /* lseek, open, read, write */
#include <stdio.h>      /* fflush, perror, printf, putchar */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/uio.h>    /* read, write */
#include <unistd.h>     /* close, lseek, read, write */

int main(void) {
    int d, cc;
    char buf[5];
    off_t pos;

    if ((d = open("input.file", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }
    if ((pos = lseek(d, 10, SEEK_SET)) == -1) {
        perror("lseek");
        exit(1);
    }
    printf("new offset = %d\n", (int)pos);  /* 位置決め後の場所 */
    if ((cc = read(d, buf, sizeof(buf))) == -1) {
        perror("read");
        exit(1);
    }
    /* 今どこにいる? */
    if ((pos = lseek(d, 0, SEEK_CUR)) == -1) {
        perror("lseek");
        exit(1);
    }
    close(d); 

    printf("offset after read = %d\n", (int)pos);  /* 読んだ後の場所 */
    printf("number of bytes read = %d\n", cc);     /* 読めたバイト数 */
    fflush(stdout);     /* 画面を崩さないため */
    if (cc > 0)
        write(STDOUT_FILENO, buf, cc); 
    putchar('\n');      /* 結果を見やすくするため */
    return 0;
}
