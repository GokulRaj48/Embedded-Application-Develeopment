#include "server.h"

int main() {
    int server_sockfd;
    int client_sockfd;
    struct sockaddr_in client_addr;

    server_sockfd = create_server_socket();
    bind_server_socket(server_sockfd, 54154);
    listen_for_connections(server_sockfd);

    while (1) {
        fprintf(stderr, "\nServer waiting for client connection...");
        client_sockfd = accept_client_connection(server_sockfd, &client_addr);
        if (client_sockfd < 0) {
            continue;
        }
        fprintf(stderr, "\n********* CLIENT CONNECTION ESTABLISHED ********");
        handle_client_connection(client_sockfd);
        fprintf(stderr, "\n********* CLIENT CONNECTION TERMINATED ********");
    }

    close(server_sockfd);
    return 0;
}

