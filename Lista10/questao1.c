#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No *proximo;
} No;

void inserirFinal(No **lista, int num) {
    No *aux, *novo = malloc(sizeof(No));

    if (novo != NULL) {
        novo->valor = num;
        novo->proximo = NULL;

        if (*lista == NULL) {
            *lista = novo;
        } else {
            aux = *lista;
            while (aux->proximo != NULL) {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
    } else {
        printf("Erro ao alocar memoria!\n");
    }
}

// Imprime a tabela hash no formato pos: val -> ... -> NULL
void imprimir(No **lista, int posicao) {
    for (int i = 0; i < posicao; i++) {
        printf("%d: ", i);

        No *aux = lista[i];
        while (aux != NULL) {
            printf("%d -> ", aux->valor);
            aux = aux->proximo;
        }
        printf("NULL\n");
    }
    printf("-------------------------\n");
}

// Dobra o tamanho N e faz o rehash dos elementos existentes
No** rehash(No **tabelaAntiga, int *N) {
    int N_antigo = *N;
    int N_novo = N_antigo * 2;

    No **novaTabela = calloc(N_novo, sizeof(No*));

    if (novaTabela == NULL) {
        printf("Erro ao alocar nova tabela!\n");
        return tabelaAntiga;
    }

    for (int i = 0; i < N_antigo; i++) {
        No *aux = tabelaAntiga[i];
        while (aux != NULL) {
            int novoIndice = aux->valor % N_novo;
            inserirFinal(&novaTabela[novoIndice], aux->valor);

            No *temp = aux;
            aux = aux->proximo;
            free(temp); 
        }
    }

    free(tabelaAntiga);
    *N = N_novo;  
    return novaTabela;
}

void liberarTabela(No **tabela, int N) {
    for (int i = 0; i < N; i++) {
        No *aux = tabela[i];
        while (aux != NULL) {
            No *temp = aux;
            aux = aux->proximo;
            free(temp);
        }
    }
    free(tabela);
}

int main() {
    int N;
    if (scanf("%d", &N) != 1 || N < 0) {
        return 0;
    }

    if(N == 0){
        N = 1;
    }

    No **tabela = calloc(N, sizeof(No*));
    int qtd = 0;
    int K;

    while (scanf("%d", &K) != EOF) {

        if (qtd * 2 >= N) {
            tabela = rehash(tabela, &N);
        }

        int indice = K % N;
        inserirFinal(&tabela[indice], K);
        qtd++;

        imprimir(tabela, N);
    }

    liberarTabela(tabela, N);
    return 0;
}