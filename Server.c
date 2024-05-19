#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>

const int port_number = 9999;
const int MAX_NUMBER_OF_CLIENTS = 5;

void* ServingAClient(void *arg) {
    // ServingAClient
    int clientSocket = *((int *)arg);
    free(arg);
    char buffer[1024];
    int bytes_read;

    // Communicate with the client
    while ((bytes_read = read(clientSocket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);
        printf("What to send back?: ");
        scanf("%s", buffer);
        write(clientSocket, buffer, bytes_read);  // Echo back the message
        if (strcmp(buffer, "bye") == 0) break;
    }

    // Close the client socket
    close(clientSocket);
    return NULL;
}

void CreateThread(int newsockfd, pthread_t* thread_id) {
    if(pthread_create(thread_id, NULL, ServingAClient, &newsockfd)) {
        perror("pthread create error");
        close(newsockfd);
        exit(1);
    }
}

int main(void) {

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd < 0) {
        perror("Unable to create a socket");
        exit(1);
    }
    
    struct sockaddr_in S_Addr, C_Addr;
    S_Addr.sin_family = AF_INET;
    S_Addr.sin_addr.s_addr = INADDR_ANY;
    S_Addr.sin_port = port_number;

    if(bind(socketfd, (struct sockaddr *) & S_Addr , sizeof(S_Addr) ) < 0) {
        perror("Bind Error");
        close(socketfd);
        exit(1);
    }

    listen(socketfd, MAX_NUMBER_OF_CLIENTS);
    socklen_t C_len = sizeof(C_Addr);

    while(1) {
        int newsockfd;
        newsockfd = accept(socketfd, (struct sockaddr *) &C_Addr, &C_len);
        if (newsockfd < 0) {
            perror("Couldn't accept new client");
            close(socketfd);
            close(newsockfd);
            exit(1);
        }
        pthread_t thread_id;
        CreateThread(newsockfd, &thread_id);
    }

    return 0;
}

