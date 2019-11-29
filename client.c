#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>


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

    while(1){
        char m[BUFSIZ];
        int i = 0;
        fgets(m, BUFSIZ, stdin);
        printf("taille du message %ld \n", strlen(m));
        char* t = m;

        if(send(dS, t, strlen(m), 0)==-1){
            printf("Envoi du message impossible");
            exit(EXIT_FAILURE);
        }  

        int r;

        if(recv(dS, &r, sizeof(int), 0)==-1){
            printf("Envoi du message impossible");
            exit(EXIT_FAILURE);
        }
        printf("reponse : %d\n",r);
        while(m[i] != '\0'){
            m[i] = '\0';
            i++;
        }
    }
    close(dS);
}