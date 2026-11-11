#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    int minuto, segundo;
}Tempo; 

typedef struct{

    char nomeMusica[50];
    char nomeCantor[50];
    Tempo t;

}Musica;

//fila
typedef struct no{

    Musica m;
    struct no *proximo;
}No;

void inserirFila(No **fila, Musica musica){

    No *aux, *novo = malloc(sizeof(No));

    if(novo != NULL){
        novo->m = musica;
        novo->proximo = NULL;

        if(*fila == NULL){
            *fila = novo;
        }
        else{
            aux = *fila;
            while(aux->proximo != NULL){
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
    }
    else{
        printf("Erro ao alocar memoria!\n");
    }
}

//teste
void imprimir(No *fila, int hor, int min, int seg){

    while(fila != NULL){
        printf("Titulo: %s\n", fila->m.nomeMusica);
        printf("Duracao restante da playlist: %.2d:%.2d:%.2d\n", hor, min, seg);

        min -= fila->m.t.minuto;
        seg -= fila->m.t.segundo;

        if(seg < 0){
            seg = (seg % 60) + 60;
            min -= 1;
        }
        if(min < 0){
            min = (min % 60) + 60;
            hor -= 1;
        }

        fila = fila->proximo;
    }
}

int main(){

    No *fila = NULL;
    Musica mus;
    int somaMin = 0, somaSeg = 0, somaHor = 0;

    int numMusicas;
    scanf("%d", &numMusicas);
    getchar(); 

    for(int i = 0; i < numMusicas; i++){

        fgets(mus.nomeMusica, 49, stdin);
        mus.nomeMusica[strcspn(mus.nomeMusica, "\n")] = '\0';

        fgets(mus.nomeCantor, 49, stdin);
        mus.nomeCantor[strcspn(mus.nomeCantor, "\n")] = '\0';

        scanf("%d:%d", &mus.t.minuto, &mus.t.segundo);
        getchar();

        somaMin += mus.t.minuto;
        somaSeg += mus.t.segundo;
    
        inserirFila(&fila, mus);
    }

    somaMin += somaSeg / 60;
    somaSeg = somaSeg % 60;
    somaHor += somaMin / 60;
    somaMin = somaMin % 60;
    
    imprimir(fila, somaHor, somaMin, somaSeg);

    return 0;
}