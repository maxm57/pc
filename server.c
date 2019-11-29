#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include "structure.h"



/*void *envoi(void* e){

}*/


int main(int argc, char* argv[]){

    //commande à garder : elle va servir maggle
        // getsockname()
    if(argc != 2){
        printf("Nombre d'argument pas bon");
        exit(EXIT_FAILURE);
    }

    key_t key;
    if((key=ftok("file.txt",0))==-1){
        printf("Creation de cle impossible");
        exit(EXIT_FAILURE);
    }

    memoire *mem;

    int memoire_partage;
    if((memoire_partage = shmget(key, sizeof(memoire), IPC_CREAT | 0666))==-1){
        printf("Creation de la memoire partagee impossible");
        exit(EXIT_FAILURE);
    }

    mem = (memoire*)shmat(memoire_partage, NULL, 0);
    
    if((void*)mem == (void*)-1){
        printf("Erreur attachement");
        exit(EXIT_FAILURE);
    }


    //creation socket
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


    //nommage socket
    if(bind(ds, (struct sockaddr*)&ad, sizeof(ad))==-1){
        printf("Renommage impossible");
        exit(EXIT_FAILURE);
    }

    //ecoute
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


    
    mem->p.taille = 3;

    mot* liste = malloc(sizeof(mot)*3);
    mot l[3];
   /* *l[1].m = "test0";
    *liste[0].m = "gre";*/
    /*liste[0].m = "coucou";
    liste[1].m = "ca";
    liste[2].m = "va";*/
    //mem->p.listeMots = l;
    //strcpy(l[0].m, "rebrtb");
    /*strcpy(mem->p.listeMots[0].m, "coucou");
    strcpy(mem->p.listeMots[1].m, "ca");
    strcpy(mem->p.listeMots[2].m, "va");
*/
    //while(1){
        printf("client 1 : %d\n", dsc);
        //phraseM temp;
        int i = 5;

        // CA MARCHE CA
        mot temp;
        strcpy(temp.m, "btrnb");
        unsigned char buffer[sizeof(temp)];
        memcpy(&buffer, &temp, sizeof(temp));

        if(send(dsc, &buffer, sizeof(buffer), 0)==-1){
            printf("Envoi du message impossible");
            exit(EXIT_FAILURE);
        }
    //}
    close(dsc);
    close(ds);


    return 0;
}