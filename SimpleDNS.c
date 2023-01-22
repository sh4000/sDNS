#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DNS_PORT 53

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server, client;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Erreur lors de la création de la socket");
        exit(EXIT_FAILURE);
    }
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(DNS_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Erreur lors de la liaison de la socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        char buffer[512];
        socklen_t len = sizeof(client);
        int bytes_received;

        bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                  (struct sockaddr *) &client, &len);
        if (bytes_received < 0) {
            perror("Erreur lors de la réception de la requête");
            continue;
        }

    }

    close(sockfd);
    return 0;
}
