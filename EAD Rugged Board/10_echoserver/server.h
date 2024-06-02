#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int create_server_socket();
void bind_server_socket(int server_sockfd, int port);
void listen_for_connections(int server_sockfd);
int accept_client_connection(int server_sockfd, struct sockaddr_in *client_addr);
void handle_client_connection(int client_sockfd);

#endif // SERVER_H


