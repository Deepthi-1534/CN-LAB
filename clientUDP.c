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
    struct sockaddr_in servaddr;
    socklen_t len;

    if (argc < 2) {
        printf("Usage: ./client <port>\n");
        exit(1);
    }

    portno = atoi(argv[1]);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(portno);
    servaddr.sin_addr.s_addr = INADDR_ANY; // local machine

    printf("Enter message to send: ");
    scanf("%[^\n]", buffer);

    len = sizeof(servaddr);

    n = sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&servaddr, len);
    if (n < 0) {
        perror("Send failed");
        exit(1);
    }

    memset(buffer, 0, sizeof(buffer));

    n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0,
                 (struct sockaddr *)&servaddr, &len);
    if (n < 0) {
        perror("Receive failed");
        exit(1);
    }

    printf("Server replied: %s\n", buffer);
    close(sockfd);
    return 0;
}
