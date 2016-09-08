/* socket/client.c */
#include <sys/types.h>  /* connect, inet_addr, read, socket, write */
#include <sys/socket.h> /* connect, inet_addr, shutdown, socket */
#include <stdio.h>      /* fprintf, perror */
#include <stdlib.h>     /* exit */
#include <string.h>     /* memset */
#include <netinet/in.h> /* inet_addr */
#include <arpa/inet.h>  /* htons, inet_addr */
#include <sys/uio.h>    /* read, write */
#include <unistd.h>     /* close, read, write */

#define SERVER_ADDR     "127.0.0.1"
#define SERVER_PORT     12345

int main(void) {
    int s, cc;
    struct sockaddr_in sa;
    char buf[1024];

    /* ソケットを作る */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* 接続先の名前を作る */
    memset(&sa, 0, sizeof(sa));
    sa.sin_len = sizeof(sa);            /* sin\_len がある場合 */
    sa.sin_family = AF_INET;
    sa.sin_port = htons(SERVER_PORT);
    sa.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    /* サーバに接続 */
    fprintf(stderr, "Connecting to the server...\n");
    if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("connect");
        exit(1);
    }
    fprintf(stderr, "Connected.\n");

    /* サーバから通信文を受け取って画面に表示する */
    fprintf(stderr, "Message from the server:\n\n");
    while ((cc = read(s, buf, sizeof(buf))) > 0)
        write(1, buf, cc);
    if (cc == -1) {
        perror("read");
        exit(1);
    }
    fprintf(stderr, "\n\nFinished receiving.\n");

    /* 通信を止める */
    if (shutdown(s, SHUT_RDWR) == -1) {
        perror("shutdown");
        exit(1);
    }

    /* ソケットを閉じる */
    if (close(s) == -1) {
        perror("close");
        exit(1);
    }
    return 0;
}
