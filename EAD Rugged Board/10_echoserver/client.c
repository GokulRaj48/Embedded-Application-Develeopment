#include "client.h"

int create_socket(const char *ip, const char *port) {
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(atoi(port));
    inet_aton(ip, &dest_addr.sin_addr);
    memset(&(dest_addr.sin_zero), '\0', sizeof dest_addr.sin_zero);

    if (connect(sockfd, (struct sockaddr*)&dest_addr, sizeof dest_addr) == -1) {
        perror("connect");
        exit(1);
    }

    return sockfd;
}

void client_loop(int sockfd) {
    char buff1[128], buff2[128];
    while (1) {
        int n = read(0, buff1, sizeof buff1);
        buff1[n] = '\0';
        write(sockfd, buff1, strlen(buff1));
        n = read(sockfd, buff2, sizeof buff2);
        buff2[n] = '\0';
        write(1, buff2, n);
    }
}

