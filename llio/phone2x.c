/* llio/phone2x.c */
#include <sys/types.h>  /* lseek, open, read, write */
#include <stdio.h>      /* fprintf, perror, printf */
#include <stdlib.h>     /* exit */
#include <string.h>     /* memset */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/uio.h>    /* read, write */
#include <unistd.h>     /* close, lseek, read, write */
#include "mysub.h"      /* \texttt{mysub.c}をリンクしてね */

#define PHONEBOOK "phone2x.dat" /* 電話帳ファイルの名前 */

enum {
    NAMELEN = 32,
    PHONELEN = 16,
};

struct person {
    char name[NAMELEN+1];
    char phone[PHONELEN+1];
    int isprivate;      /* 1なら個人用の項目 */
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
    struct person rec;

    recno = getint("record number? ");
    /* recno * sizeof(rec) が，ファイルにおけるrecno番目の項目の先頭位置 */
    if (lseek(fd, recno * sizeof(rec), SEEK_SET) == -1) {
        perror("lseek");
        return;
    }
    if ((cc = read(fd, &rec, sizeof(rec))) < 0) {
        perror("read");
        return;
    }
    if (cc == 0)
        printf("no item\n");
    else
        printf("item = {%d, \"%s\", \"%s\"}\n",
                rec.isprivate, rec.name, rec.phone);
    return;
}

/* 入力部 */
void input(int fd) {
    int recno;
    struct person rec;

    memset(&rec, 0, sizeof(rec));       /* 領域を0できれいにする */
    recno = getint("record number? ");
    if (lseek(fd, recno * sizeof(rec), SEEK_SET) == -1) {
        perror("lseek");
        return;
    }
    getstr("name? ", rec.name, NAMELEN+1);
    getstr("phone? ", rec.phone, PHONELEN+1);
    rec.isprivate = getint("private? (yes=1, no=0)");
    if (write(fd, &rec, sizeof(rec)) != sizeof(rec)) {
        perror("write");
        return;
    }
    return;
}
