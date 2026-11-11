#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int Dano;
    struct No *Esq;
    struct No *Dir;
} No;


No* construirArvore() {
    int dano;
    if (scanf("%d", &dano) != 1 || dano < 0) {
        return NULL;
    }

    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    else{
        novo->Dano = dano;

        novo->Esq = construirArvore();
        novo->Dir = construirArvore();
        return novo;
    }

}


void buscarMelhorCaminho(No *raiz, int caminhoAtual[], int tamAtual, int somaAtual, int caminhoO[], int *tamO, int *maiorDano) {
    if (raiz == NULL){ 
        return;
    }

    caminhoAtual[tamAtual] = raiz->Dano;
    tamAtual++;
    somaAtual += raiz->Dano;

    if (raiz->Esq == NULL && raiz->Dir == NULL) {

        if (somaAtual > *maiorDano) {
            *maiorDano = somaAtual;
            *tamO = tamAtual;
            for (int i = 0; i < tamAtual; i++) {
                caminhoO[i] = caminhoAtual[i];
            }
        }
    } else {
        buscarMelhorCaminho(raiz->Esq, caminhoAtual, tamAtual, somaAtual, caminhoO, tamO, maiorDano);
        buscarMelhorCaminho(raiz->Dir, caminhoAtual, tamAtual, somaAtual, caminhoO, tamO, maiorDano);
    }
}


void liberarArvore(No *raiz) {
    if(raiz == NULL){
        return;
    } 
    liberarArvore(raiz->Esq);
    liberarArvore(raiz->Dir);
    free(raiz);
}

int main() {
    No *raiz = construirArvore();

    if (raiz == NULL) {
        printf("Maior Dano: 0\n");
        printf("Caminho Escolhido: \n");
        return 0;
    }

    int caminhoAtual[1000];
    int caminhoO[1000];
    int tamO = 0;
    int maiorDano = -1;

    buscarMelhorCaminho(raiz, caminhoAtual, 0, 0, caminhoO, &tamO, &maiorDano);

    printf("Maior Dano: %d\n", maiorDano);
    printf("Caminho Escolhido: ");
    for (int i = 0; i < tamO; i++) {
        printf("%d", caminhoO[i]);
        if (i < tamO - 1) {
            printf(" -> ");
        }
    }
    printf("\n");

    liberarArvore(raiz);
    return 0;
}