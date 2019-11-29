#include <stdio.h>

typedef struct mot{
    char m[20];
    int disparu;
}mot;

typedef struct phraseM{
    int taille;
    mot* listeMots;
}phraseM;

typedef struct memoire{
    phraseM p;

}memoire;