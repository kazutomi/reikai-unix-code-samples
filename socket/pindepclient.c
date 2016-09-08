/* socket/pindepclient.c */
#include <sys/types.h>  /* connect, freeaddrinfo, gai_strerror,
                                        getaddrinfo, read, socket, write */
#include <stdio.h>      /* fprintf, perror */
#include <stdlib.h>     /* exit */
#include <string.h>     /* memset, strlen */
#include <sys/socket.h> /* connect, freeaddrinfo, gai_strerror,
                                           getaddrinfo, shutdown, socket */
#include <netdb.h>      /* freeaddrinfo, gai_strerror, getaddrinfo */
#include <sys/uio.h>    /* read, write */
#include <unistd.h>     /* close, read, write */

char *httpreq = "GET / HTTP/1.0\n\n";   /* トップページを得るためのHTTP要求 */

int main(void) {
    struct addrinfo hints, *addrs;
    int cc, s; 
    char buf[1024];

    /* SOCK_STREAMで繋ぐためのaddrinfo構造体リストを得る */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((cc = getaddrinfo("www.titech.ac.jp", "http", &hints, &addrs)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(cc));
        exit(1);
    }

    /* 得られたaddrinfo構造体リストの先頭要素を使って接続する */
    if ((s = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol))
          == -1) {
        perror("socket");
        exit(1);
    }
    if (connect(s, addrs->ai_addr, addrs->ai_addrlen) == -1) {
        perror("connect");
        exit(1);
    }

    /* addrinfo構造体リストの領域を解放 */
    freeaddrinfo(addrs);

    /* HTTP要求を送る */
    write(s, httpreq, strlen(httpreq)); 
    /* 返答を得て画面に表示 */
    while ((cc = read(s, buf, sizeof(buf))) > 0) 
        write(1, buf, cc); 

    shutdown(s, SHUT_RDWR); 
    close(s); 
    
    return 0;
}
