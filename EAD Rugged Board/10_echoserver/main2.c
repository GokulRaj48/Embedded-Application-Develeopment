#include "client.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Must enter IP and port\n");
        exit(1);
    }

    int sockfd = create_socket(argv[1], argv[2]);
    client_loop(sockfd);
    close(sockfd);
    exit(0);
}

