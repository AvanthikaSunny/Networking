// UDP Client - send and receive messages
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
struct sockaddr_in servaddr;
socklen_t len;
// Create socket
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd < 0) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));
// Server info
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);

servaddr.sin_addr.s_addr = INADDR_ANY; // use server IP if remote
len = sizeof(servaddr);
printf("UDP Client running...\n");
while (1) {
// Send message to server
printf("Client: ");
fgets(message, MAXLINE, stdin);
sendto(sockfd, message, strlen(message), 0,
(struct sockaddr *)&servaddr, len);
if (strncmp(message, "exit", 4) == 0)
break;
// Receive reply from server
int n = recvfrom(sockfd, buffer, MAXLINE, 0,
(struct sockaddr *)&servaddr, &len);
buffer[n] = '\0';
printf("Server: %s", buffer);
if (strncmp(buffer, "exit", 4) == 0)
break;
}
close(sockfd);
return 0;
}