#include "server.h"

int create_server_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void bind_server_socket(int server_sockfd, int port) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to all interfaces
    memset(&(server_addr.sin_zero), '\0', sizeof server_addr.sin_zero);

    if (bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof server_addr) < 0) {
        perror("bind");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }
}

void listen_for_connections(int server_sockfd) {
    if (listen(server_sockfd, 10) < 0) {
        perror("listen");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }
}

int accept_client_connection(int server_sockfd, struct sockaddr_in *client_addr) {
    int client_sockfd;
    socklen_t client_len = sizeof(*client_addr);
    client_sockfd = accept(server_sockfd, (struct sockaddr*)client_addr, &client_len);
    if (client_sockfd < 0) {
        perror("accept");
    }
    return client_sockfd;
}

void handle_client_connection(int client_sockfd) {
    char buf[100];
    int rv;
    while ((rv = read(client_sockfd, buf, sizeof buf)) > 0) {
        write(client_sockfd, buf, rv);
    }
    if (rv < 0) {
        perror("read");
    }
    close(client_sockfd);
}

