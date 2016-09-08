/* socket/iserver1.c */
#include <arpa/inet.h>  /* htons */
#include <stdio.h>      /* fprintf, perror */
#include <stdlib.h>     /* exit */
#include <string.h>     /* memset, strlen */
#include <sys/types.h>  /* accept, bind, setsockopt, socket, write */
#include <sys/socket.h> /* accept, bind, listen, setsockopt, shutdown, socket */
#include <sys/uio.h>    /* write */
#include <unistd.h>     /* close, write */

#define SERVER_ADDR     "127.0.0.1"
#define SERVER_PORT     12345

enum {
    NQUEUESIZE = 5,     /* listenのための待ち行列枠数 */
};

char *message = "Hello!\nGood-bye!!\n";

void sendmessage(int s) {
    char buf[1024];

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        if (write(s, buf, strlen(buf)) == -1) {
            fprintf(stderr, "send error\n");
            return;
        }
    }
    clearerr(stdin);    /* EOF印を消す */
}

int main(void) {
    int s, ws, soval;
    struct sockaddr_in sa, ca;
    socklen_t ca_len;

    /* ソケットを作る */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* アドレス再利用の設定 */
    soval = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
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
        /* 接続を受け入れる */
        fprintf(stderr, "Waiting for a connection...\n");
        ca_len = sizeof(ca);
        if ((ws = accept(s, (struct sockaddr *)&ca, &ca_len)) == -1) {
            perror("accept");
            exit(1);
        }
        fprintf(stderr, "Connection established.\n");

        /* クライアントに通信文を送る */
        sendmessage(ws);

        fprintf(stderr, "Message sent.\n");

        /* 通信を止める */
        if (shutdown(ws, SHUT_RDWR) == -1) {
            perror("shutdown");
            exit(1);
        }

        /* 接続済みソケットを閉じる */
        if (close(ws) == -1) {
            perror("close");
            exit(1);
        }
        /* 次の要求の受け入れへ */
    }
    /* 無限ループ */
}
