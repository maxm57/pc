#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>




// void *envoi(void* e){

// }


int main(int argc, char* argv[]){

    //commande à garder : elle va servir maggle
        // getsockname()
    if(argc != 2){
        printf("Nombre d'argument pas bon");
        exit(EXIT_FAILURE);
    }

    int ds = socket(PF_INET, SOCK_STREAM,0);
    if(ds == -1){
        printf("Création de socket impossible");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in ad;
    socklen_t lgA = sizeof(struct sockaddr_in);

    ad.sin_family = AF_INET;
    ad.sin_addr.s_addr = INADDR_ANY;
    ad.sin_port = htons(atoi(argv[1]));

    if(bind(ds, (struct sockaddr*)&ad, sizeof(ad))==-1){
        printf("Renommage impossible");
        exit(EXIT_FAILURE);
    }
    if(listen(ds, 7)==-1){
        printf("Impossible de connecter");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client1, client2;

    socklen_t lg = sizeof(struct sockaddr_in);
    int dsc = accept(ds, (struct sockaddr*)&client1, &lg);

    if(dsc == -1){
        printf("Client impossible à connecter");
        exit(EXIT_FAILURE);
    }

    int dsc2 = accept(ds,(struct sockaddr*)&client2, &lg);
    if(dsc2 == -1){
        printf("Client impossible à connecter");
        exit(EXIT_FAILURE);
    }

    while(1){
        //printf("client 1 : %d", dsc);
        printf("client 1 : %d, client 2: %d", dsc, dsc2);
        char msg[BUFSIZ];
        int i = 0;
        if(recv(dsc, msg, sizeof(msg),0)==-1){
            printf("Réception du message impossible");
            exit(EXIT_FAILURE);
        }
        
        printf("recu : %s", msg);
        int r = strlen(msg);

        if(send(dsc, &r, sizeof(int), 0)==-1){
            printf("Envoi du message impossible");
            exit(EXIT_FAILURE);
        }

        while(msg[i] != '\0'){
            msg[i] = '\0';
            i++;
        }
        if(recv(dsc2, msg, sizeof(msg),0)==-1){
            printf("Réception du message impossible");
            exit(EXIT_FAILURE);
        }
        
        printf("recu : %s", msg);
        r = strlen(msg);

        if(send(dsc2, &r, sizeof(int), 0)==-1){
            printf("Envoi du message impossible");
            exit(EXIT_FAILURE);
        }

        while(msg[i] != '\0'){
            msg[i] = '\0';
            i++;
        }
    }
    close(dsc);
    close(ds);
    return 0;
}