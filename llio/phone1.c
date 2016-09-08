/* llio/phone1.c */
#include <sys/types.h>  /* lseek, open, read, write */
#include <stdio.h>      /* fprintf, perror, printf */
#include <stdlib.h>     /* exit */
#include <string.h>     /* memset */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/uio.h>    /* read, write */
#include <unistd.h>     /* close, lseek, read, write */
#include "mysub.h"      /* \texttt{mysub.c}をリンクしてね */

#define PHONEBOOK "phone1.dat"  /* 電話帳ファイルの名前 */

enum {
    RECLEN = 32,                /* ファイル内での1項目の長さ */
};

/* 関数のプロトタイプ宣言 */
void show(int);
void input(int);

int main(void) {
    int fd;
    int cmd, finish;

    /*
     * show では読み，input では書くので，読み書きで開く．
     * ファイルがなければ作るが，既にファイルがある場合は
     * その内容を消してはいけないので，O_TRUNC は指定しない．
     */
    if ((fd = open(PHONEBOOK, O_RDWR|O_CREAT, 0666)) < 0) {
        perror("open");
        exit(1);
    }
    finish = 0;
    while (!finish) {
        cmd = getint("command (0=show, 1=input, 2=end)? ");
        switch (cmd) {
            case 0:
                show(fd);
                break;
            case 1:
                input(fd);
                break;
            case 2:
                /* 繰り返しを抜ける */
                finish = 1;
                break;
            default:
                fprintf(stderr, "unknown command %d\n", cmd);
                break;
        }
    }
    if (close(fd) < 0) {
        perror("close");
        exit(1);
    }
    return 0;
}

/* 表示部 */
void show(int fd) {
    int recno;
    ssize_t cc;
    char rec[RECLEN+1]; /* +1はヌル文字のため */

    rec[RECLEN] = '\0'; /* あらかじめヌル文字を入れておく */
    recno = getint("record number? ");
    /* recno * RECLEN が，ファイルにおける項目 recno の先頭位置 */
    if (lseek(fd, recno * RECLEN, SEEK_SET) == -1) {
        perror("lseek");
        return;
    }
    if ((cc = read(fd, rec, RECLEN)) < 0) {
        perror("read");
        return;
    }
    if (cc == 0)
        printf("no item\n");
    else
        printf("item = \"%s\"\n", rec);
    return;
}

/* 入力部 */
void input(int fd) {
    int recno;
    char rec[RECLEN+1]; /* +1 はヌル文字のため */

    memset(rec, 0, sizeof(rec));        /* 領域を0で埋めてごみをなくす */
    recno = getint("record number? ");
    if (lseek(fd, recno * RECLEN, SEEK_SET) == -1) {
        perror("lseek");
        return;
    }
    getstr("name? ", rec, sizeof(rec));
    if (write(fd, rec, RECLEN) != RECLEN) {
        perror("write");
        return;
    }
    return;
}
