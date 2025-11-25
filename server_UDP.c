#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    if (argc < 2) {
        printf("Usage: ./server <port>\n");
        exit(1);
    }

    portno = atoi(argv[1]);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    printf("UDP Server: Waiting for data...\n");

    len = sizeof(cliaddr);
    memset(buffer, 0, sizeof(buffer));

    n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0,
                 (struct sockaddr *)&cliaddr, &len);
    if (n < 0) {
        perror("Receive failed");
        exit(1);
    }

    printf("Received from client: %s\n", buffer);

    // Echo back the same data
    n = sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&cliaddr, len);
    if (n < 0)
        perror("Send failed");

    close(sockfd);
    return 0;
}
