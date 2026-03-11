// UDP Server - send and receive messages
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
int main() {
int sockfd;
char buffer[MAXLINE];
char message[MAXLINE];
struct sockaddr_in servaddr, cliaddr;
socklen_t len;
// Create socket
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd < 0) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));
memset(&cliaddr, 0, sizeof(cliaddr));
// Server info
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);
// Bind
if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
perror("bind failed");
exit(EXIT_FAILURE);
}
printf("UDP Server running...\n");
len = sizeof(cliaddr);
while (1) {
// Receive message from client
int n = recvfrom(sockfd, buffer, MAXLINE, 0,
(struct sockaddr *)&cliaddr, &len);
buffer[n] = '\0';
printf("Client: %s", buffer);

if (strncmp(buffer, "exit", 4) == 0) {
printf("Client disconnected.\n");
break;
}
// Send reply to client
printf("Server: ");
fgets(message, MAXLINE, stdin);
sendto(sockfd, message, strlen(message), 0,
(struct sockaddr *)&cliaddr, len);
if (strncmp(message, "exit", 4) == 0)
break;
}
close(sockfd);
return 0;
}
 