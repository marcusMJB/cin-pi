#include <stdio.h>
#include <stdlib.h>

typedef struct No{

    int valor;
    struct No *proximo;
}No;

void inserirFinal(No **lista, int num){

    No *aux, *novo = malloc(sizeof(No));

    if(novo != NULL){
        novo->valor = num;
        novo->proximo = NULL;

        if(*lista == NULL){
            *lista = novo;
        }
        else{
            aux = *lista;
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

//função para impressão da tabela
void imprimir(No **lista, int posicao){

    for(int i = 0; i < posicao; i++){

        printf("%d: ", i);

        No *aux = lista[i];
        while(aux != NULL){
            printf("%d -> ", aux->valor);
            aux = aux->proximo;
        }
        printf("NULL\n");
    }
    printf("-------------------------\n");
}

int main(){

    int posicao;
    scanf("%d", &posicao);

    return 0;
}