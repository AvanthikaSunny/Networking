#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main()
{
int sock;
struct sockaddr_in serv_addr;

char buffer[1024];
char message[1024];

// Create socket
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock < 0) {
printf("Socket creation error\n");
return -1;
}

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);

inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

// Connect
if (connect(sock, (struct sockaddr*)&serv_addr,
sizeof(serv_addr)) < 0) {
printf("Connection Failed\n");
return -1;
}

while (1) {
// Send to server
printf("Client: ");
fgets(message, 1024, stdin);
send(sock, message, strlen(message), 0);

if (strncmp(message, "exit", 4) == 0)
break;

// Receive from server
memset(buffer, 0, sizeof(buffer));
read(sock, buffer, 1024);
printf("Server: %s", buffer);

if (strncmp(buffer, "exit", 4) == 0)
break;
}

close(sock);
return 0;
}