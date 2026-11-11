#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *proximo;
} No;

typedef struct {
    No *topo;
    int tam;
} Pilha;

void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
    pilha->tam = 0;
}

void empilhar(Pilha *pilha, int num) {
    No *novo = malloc(sizeof(No));
    if (novo != NULL) {
        novo->valor = num;
        novo->proximo = pilha->topo;
        pilha->topo = novo;
        pilha->tam++;
    } else {
        printf("Erro ao alocar memoria!\n");
    }
}

int desempilhar(Pilha *pilha) {
    if (pilha->topo != NULL) {
        No *remover = pilha->topo;
        int valor = remover->valor;
        pilha->topo = remover->proximo;
        free(remover);
        pilha->tam--;
        return valor;
    }
    return -1;
}

void imprimirPilha(No *no) {
    if(no == NULL){
        return;
    }
    imprimirPilha(no->proximo);
    printf(" %d", no->valor);
}

void imprimirPino(char *nome, Pilha *p) {
    printf("[%s]-", nome);
    imprimirPilha(p->topo);
    printf("\n");
}

void registrarPasso(int *passo, Pilha *pA, Pilha *pC, Pilha *pB) {
    printf("PASSO %d\n", *passo);
    imprimirPino("origem", pA);
    imprimirPino("destino", pC);
    imprimirPino("auxiliar", pB);
    printf("\n");
    (*passo)++;
}

void moverDisco(Pilha *de, Pilha *para, Pilha *pA, Pilha *pC, Pilha *pB, int *passo) {
    int disco = desempilhar(de);
    empilhar(para, disco);
    registrarPasso(passo, pA, pC, pB);
}

void hanoi(int n, Pilha *de, Pilha *para, Pilha *aux, Pilha *pA, Pilha *pC, Pilha *pB, int *passo) {
    if (n == 1) {
        moverDisco(de, para, pA, pC, pB, passo);
        return;
    }
    hanoi(n - 1, de, aux, para, pA, pC, pB, passo);
    moverDisco(de, para, pA, pC, pB, passo);
    hanoi(n - 1, aux, para, de, pA, pC, pB, passo);
}

int main() {
    int n;
    scanf("%d", &n);

    Pilha pinoA, pinoB, pinoC;
    inicializar(&pinoA);
    inicializar(&pinoB);
    inicializar(&pinoC);


    for (int i = n; i >= 1; i--) {
        empilhar(&pinoA, i);
    }

    int totalPassos;
    totalPassos = (1 << n) - 1;
    printf("%d\n", totalPassos);

    int passo = 1;
    hanoi(n, &pinoA, &pinoC, &pinoB, &pinoA, &pinoC, &pinoB, &passo);

    return 0;
}