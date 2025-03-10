#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "socketUtilize.h"

#define PORT 9000
#define MAX_BUFFER_SIZE 16384

int main() {
    int socketFD = createTCPIpv4Socket();
    struct sockaddr_in *serverAddress = createIPv4Address("127.0.0.1", PORT);


    if (connect(socketFD, (struct sockaddr *)serverAddress, sizeof(*serverAddress))) {
        perror("Connection failed");
        return 1;
    }

    printf("Connection is successful to server.\n");


    char name[MAX_BUFFER_SIZE];
    int number;

    printf("Enter your name: ");
    fgets(name, MAX_BUFFER_SIZE, stdin);
    name[strcspn(name, "\n")] = 0; 

    printf("Enter a number between 1 and 100: ");
    scanf("%d", &number);


    char message[MAX_BUFFER_SIZE];

    int requiredSize = snprintf(NULL, 0, "%s %d", name, number);
    if (requiredSize >= MAX_BUFFER_SIZE) {
        printf("Message is too long\n");
    }

    snprintf(message, MAX_BUFFER_SIZE, "%s %d", name, number);


    send(socketFD, message, strlen(message), 0);
    printf("Message was sended to server: %s\n", message);


    char buffer[MAX_BUFFER_SIZE];
    ssize_t amountReceived = recv(socketFD, buffer, MAX_BUFFER_SIZE, 0);
    if (amountReceived > 0) {
        buffer[amountReceived] = 0;
        printf("Response of server: %s\n", buffer);
    }

    close(socketFD);
    return 0;
}