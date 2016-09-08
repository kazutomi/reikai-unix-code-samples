/* socket/cserver.c */
#include <arpa/inet.h>  /* htons */
#include <stdio.h>      /* fprintf, perror */
#include <stdlib.h>     /* exit */
#include <string.h>     /* memset, strlen */
#include <sys/types.h>  /* accept, bind, fork, setsockopt,
                                      socket, waitpid, write */
#include <sys/socket.h> /* accept, bind, listen,
                                     setsockopt, shutdown, socket */
#include <sys/uio.h>    /* write */
#include <sys/wait.h>   /* waitpid */
#include <unistd.h>     /* close, fork, write */

#define SERVER_ADDR     "127.0.0.1"
#define SERVER_PORT     12345

enum {
    NQUEUESIZE = 5,     /* listenのための待ち行列枠数 */
};

char *message = "Hello!\nGood-bye!!\n";

int main(void) {
    int s, ws, soval, cc;
    struct sockaddr_in sa, ca;
    socklen_t ca_len;

    /* ソケットを作る */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* アドレス再利用の設定 */
    soval = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval))
          == -1) {
        perror("setsockopt");
        exit(1);
    }

    /* ソケットに名前をつける */
    memset(&sa, 0, sizeof(sa));
    sa.sin_len = sizeof(sa);            /* sin\_len がある場合 */
    sa.sin_family = AF_INET;
    sa.sin_port = htons(SERVER_PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("bind");
        exit(1);
    }

    /* 待ち行列を準備 */
    if (listen(s, NQUEUESIZE)) {
        perror("listen");
        exit(1);
    }

    fprintf(stderr, "Ready.\n");

    for (;;) {
        pid_t forkcc;
        int status;

        /* acceptで待たされる前に幽霊を処理する */
        while (waitpid(-1, &status, WNOHANG) > 0);

        /* 接続を受け入れる */
        fprintf(stderr, "Waiting for a connection...\n");
        ca_len = sizeof(ca);
        if ((ws = accept(s, (struct sockaddr *)&ca, &ca_len)) == -1) {
            perror("accept");
            exit(1);
        }
        fprintf(stderr, "Connection established.\n");

        if ((forkcc = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if (forkcc == 0) {
            /* 子プロセス */
            /* 接続待ちソケットは使わない */
            if (close(s) == -1) {
                perror("child: close listening socket");
                exit(1);
            }

            /* クライアントに通信文を送る */
            fprintf(stderr, "Sending the message...\n");
            if ((cc = write(ws, message, strlen(message))) == -1) {
                perror("child: write");
                exit(1);
            }
            fprintf(stderr, "Message sent.\n");

            /* 通信を止める */
            if (shutdown(ws, SHUT_RDWR) == -1) {
                perror("child: shutdown");
                exit(1);
            }

            /* 接続済みソケットを閉じる */
            if (close(ws) == -1) {
                perror("child: close");
                exit(1);
            }
            exit(0);    /* 子プロセスの終了 */
        }
        /* 親プロセス */
        /* 接続済みソケットは使わない */
        if (close(ws) == -1) {
            perror("close");
            exit(1);
        }
        /* 次の要求の受け入れへ */
    }
    /* 無限ループ */
}
