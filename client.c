#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include "structure.h"

int main(int argc, char* argv[]){
    
    if(argc != 3){
        printf("Nombre d'argument pas bon");
        exit(EXIT_FAILURE);
    }

    int dS = socket(PF_INET, SOCK_STREAM,0);
    if(dS == -1){
        printf("Création de socket impossible");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in aS;
    aS.sin_family = AF_INET;

    inet_pton(AF_INET, argv[1], &(aS.sin_addr));
    aS.sin_port = htons(atoi(argv[2]));
    socklen_t lgA = sizeof(struct sockaddr_in);

    if(connect(dS, (struct sockaddr *) &aS, lgA)==-1){
        printf("Connexion impossible à la socket");
        exit(EXIT_FAILURE);
    }

    memoire p;
    //p.listeMots = malloc(sizeof(mot)*3);
    mot temp;
    int i;
    //while(1){
    unsigned char buffer[sizeof(mot)];
    if(recv(dS, &buffer, sizeof(buffer), 0)==-1){
        perror("reception du message impossible");
        exit(EXIT_FAILURE);
    }

    memcpy(&temp, &buffer,sizeof(buffer));
    printf("%s", temp.m);
    //printf("%s", l[0].m);
    //}
    close(dS);
}