/* socket/chatserver.c */
#include <arpa/inet.h>  /* htons */
#include <stdio.h>      /* fprintf, perror */
#include <stdlib.h>     /* exit */
#include <string.h>     /* memset, strlen */
#include <sys/select.h> /* FD_ISSET, FD_SET, FD_ZERO, select */
#include <sys/types.h>  /* accept, bind, read, setsockopt, socket, write */
#include <sys/socket.h> /* accept, bind, listen, setsockopt, shutdown, socket */
#include <sys/uio.h>    /* read, write */
#include <unistd.h>     /* close, read, write */

enum {
    SERVER_PORT = 12345,
    NQUEUESIZE = 5,
    MAXNCLIENTS = 10,           /* 最大クライアント数 */
};

int clients[MAXNCLIENTS];       /* クライアントに繋がっている記述子の一覧 */
int nclients = 0;               /* 現在接続しているクライアント数 */

void sorry(int ws) {
    char *message = "Sorry, it's full.\n";
    
    write(ws, message, strlen(message)); 
}

/* 記述子wsを記述子一覧から取り除く */
void delete_client(int ws) {
    int i;

    for (i = 0; i < nclients; i++) {
        if (clients[i] == ws) {
            clients[i] = clients[nclients - 1];
            nclients--;
            break;
        }
    }
}

/* ソケットwsから来る1行を全てのクライアントに送る */
void talks(int ws) {
    int i, cc;
    char c;

    do {
        if ((cc = read(ws, &c, 1)) == -1) {
            perror("read");
            exit(1);
        } else if (cc == 0) {         /* EOF; クライアントが通信路を切った */
            shutdown(ws, SHUT_RDWR); 
            close(ws); 
            delete_client(ws);
            fprintf(stderr, "Connection closed on descriptor %d.\n", ws);
            return;
        }
        for (i = 0; i < nclients; i++)
            write(clients[i], &c, 1); 
    } while (c != '\n');
}

int main(void) {
    int s, soval;
    struct sockaddr_in sa;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    soval = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    memset(&sa, 0, sizeof(sa));
    sa.sin_len = sizeof(sa);            /* sin\_len がある場合 */
    sa.sin_family = AF_INET;
    sa.sin_port = htons(SERVER_PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(s, NQUEUESIZE)) {
        perror("listen");
        exit(1);
    }

    fprintf(stderr, "Ready.\n");
    for (;;) {
        int i, maxfd;
        fd_set readfds;

        /* selectのための記述子集合を作る */
        FD_ZERO(&readfds);      /* 御破算で願いましては */
        FD_SET(s, &readfds);    /* 接続待ちソケットを見張る */
        maxfd = s;
        /* 繋がっているクライアントからの発言がないか見張る */
        for (i = 0; i < nclients; i++) {
            FD_SET(clients[i], &readfds);
            if (clients[i] > maxfd)
                maxfd = clients[i];
        }

        /* いずれかの記述子の準備ができるまで待つ */
        if (select(maxfd+1, &readfds, NULL, NULL, NULL) < 0) {
            perror("select");
            exit(1);
        }

        /* 新しい接続か */
        if (FD_ISSET(s, &readfds)) {
            struct sockaddr_in ca;
            socklen_t ca_len;
            int ws;

            ca_len = sizeof(ca);
            if ((ws = accept(s, (struct sockaddr *)&ca, &ca_len)) == -1) {
                perror("accept");
                continue;
            }
            if (nclients >= MAXNCLIENTS) {
                /* もう満杯 */
                sorry(ws);
                shutdown(ws, SHUT_RDWR); 
                close(ws); 
                fprintf(stderr, "Refused a new connection.\n");
            } else {
                clients[nclients] = ws; /* 記述子一覧に加える */
                nclients++;
                fprintf(stderr, "Accepted a connection on descriptor %d.\n", ws);
            }
        }

        /* 発言があったらそれを全クライアントに送る */
        for (i = 0; i < nclients; i++) {
            if (FD_ISSET(clients[i], &readfds)) {
                talks(clients[i]);
                break;  /* talksはclients[]の中身とnclientsを変えることがある */
            }
        }

        /* 繰り返しの先頭に戻って再びselectする */
    }
}
