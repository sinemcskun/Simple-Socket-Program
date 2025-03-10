#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "socketUtilize.h"

#define PORT 9000
#define MAX_BUFFER_SIZE 4096

void handleClient(int clientSocketFD) {
    char buffer[MAX_BUFFER_SIZE];
    char *serverName = "Server of Sinem Coşkun";
    int serverNumber = 42;


    ssize_t amountReceived = recv(clientSocketFD, buffer, MAX_BUFFER_SIZE, 0);
    if (amountReceived > 0) {
        buffer[amountReceived] = 0; 
        printf("Message of client: %s\n", buffer);

        int clientNumber = atoi(buffer + strlen(buffer) - 3); 

        char response[MAX_BUFFER_SIZE];
        snprintf(response, MAX_BUFFER_SIZE, "%s %d", serverName, serverNumber);

        send(clientSocketFD, response, strlen(response), 0);
        printf("Response of server was sended: %s\n", response);

        int sum = clientNumber + serverNumber;
        printf("Client number is: %d, Server number is: %d, Sum is: %d\n", clientNumber, serverNumber, sum);
    }

    close(clientSocketFD);
    exit(0);
}

int main() {
    int serverSocketFD = createTCPIpv4Socket();
    struct sockaddr_in *serverAddress = createIPv4Address("", PORT);

    if (bind(serverSocketFD, (struct sockaddr *)serverAddress, sizeof(*serverAddress))) {
        perror("Bind failed");
        return 1;
    }

    if (listen(serverSocketFD, 10)) {
        perror("Listen failed");
        return 1;
    }

    printf("Server is listening on %d...\n", PORT);

    while (1) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);
        int clientSocketFD = accept(serverSocketFD, (struct sockaddr *)&clientAddress, &clientAddressSize);

        if (clientSocketFD < 0) {
            perror("Accept failed");
            continue;
        }

        printf("New client is connected.\n");

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            close(clientSocketFD);
        }else if (pid == 0) {
            close(serverSocketFD);
            handleClient(clientSocketFD);
        }else {
            close(clientSocketFD);
            while(waitpid(-1, NULL, WNOHANG) > 0);
        }
    }

    close(serverSocketFD);
    return 0;
}