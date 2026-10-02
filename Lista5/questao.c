#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nomeMax 100

//verifica se um carro já existe em uma determinada coleção
int possuiCarro(char (*colecao)[nomeMax], int tamanho, char *nome) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(colecao[i], nome) == 0) {
            return 1;
        }
    }
    return 0; 
}

void adicionarColecao(char (**colecao)[nomeMax], int *tamanho, int *capacidade, char *nome) {
    if (*tamanho == *capacidade) {
        *capacidade *= 2;
        *colecao = realloc(*colecao, (*capacidade) * sizeof(char[nomeMax]));
    }
    strcpy((*colecao)[*tamanho], nome);
    (*tamanho)++;
}

//adiciona um carro ao estoque
void adicionarEstoque(char (**nomes)[nomeMax], int **qtds, int *tamanho, int *capacidade, char *nome, int qtd) {
    for (int i = 0; i < *tamanho; i++) {
        if (strcmp((*nomes)[i], nome) == 0) {
            (*qtds)[i] += qtd;
            return;
        }
    }
    
    //verifica se precisa expandir
    if (*tamanho == *capacidade) {
        *capacidade *= 2;
        *nomes = realloc(*nomes, (*capacidade) * sizeof(char[nomeMax]));
        *qtds  = realloc(*qtds, (*capacidade) * sizeof(int));
    }
    
    //Adiciona nos vetores
    strcpy((*nomes)[*tamanho], nome);
    (*qtds)[*tamanho] = qtd;
    (*tamanho)++;
}

void realizarVendas(
    char (*tcar_nomes)[nomeMax], int *tcar_qtds, int tcar_tam,
    char (**julio)[nomeMax], int *julio_tam, int *julio_cap,
    char (**cariani)[nomeMax], int *cariani_tam, int *cariani_cap,
    char (**vendidos)[nomeMax], int *vend_tam, int *vend_cap
) {

    for (int i = 0; i < tcar_tam; i++) {
        if (tcar_qtds[i] > 0 && !possuiCarro(*julio, *julio_tam, tcar_nomes[i])) {
            adicionarColecao(julio, julio_tam, julio_cap, tcar_nomes[i]);
            tcar_qtds[i]--;
            adicionarColecao(vendidos, vend_tam, vend_cap, tcar_nomes[i]);
        }
    }
    
    for (int i = 0; i < tcar_tam; i++) {
        if (tcar_qtds[i] > 0 && !possuiCarro(*cariani, *cariani_tam, tcar_nomes[i])) {
            adicionarColecao(cariani, cariani_tam, cariani_cap, tcar_nomes[i]);
            tcar_qtds[i]--;
            adicionarColecao(vendidos, vend_tam, vend_cap, tcar_nomes[i]);
        }
    }
}


int main() {
    //estoque
    int tcar_cap = 2, tcar_tam = 0;
    char (*tcar_nomes)[nomeMax] = malloc(tcar_cap * sizeof(char[nomeMax]));
    int *tcar_qtds = malloc(tcar_cap * sizeof(int));

    //coleção do Júlio
    int julio_cap = 2, julio_tam = 0;
    char (*julio_nomes)[nomeMax] = malloc(julio_cap * sizeof(char[nomeMax]));

    //coleção do Cariani
    int cariani_cap = 2, cariani_tam = 0;
    char (*cariani_nomes)[nomeMax] = malloc(cariani_cap * sizeof(char[nomeMax]));

    //Vendidos
    int vendidos_cap = 2, vendidos_tam = 0;
    char (*vendidos_nomes)[nomeMax] = malloc(vendidos_cap * sizeof(char[nomeMax]));

    char entrada[nomeMax];
    int qtd;

    while (scanf("%s", entrada) == 1 && strcmp(entrada, "FIM") != 0) {
        scanf("%d", &qtd);
        adicionarEstoque(&tcar_nomes, &tcar_qtds, &tcar_tam, &tcar_cap, entrada, qtd);
    }

    while (scanf("%s", entrada) == 1 && strcmp(entrada, "FIM") != 0) {
        adicionarColecao(&julio_nomes, &julio_tam, &julio_cap, entrada);
    }

    while (scanf("%s", entrada) == 1 && strcmp(entrada, "TOGURO") != 0) {
        adicionarColecao(&cariani_nomes, &cariani_tam, &cariani_cap, entrada);
    }

    realizarVendas(tcar_nomes, tcar_qtds, tcar_tam, &julio_nomes, &julio_tam, &julio_cap, &cariani_nomes, &cariani_tam, &cariani_cap, &vendidos_nomes, &vendidos_tam, &vendidos_cap);


    while (scanf("%s", entrada) == 1) {
        if (strcmp(entrada, "ESTOQUE") == 0) {
            while (scanf("%s", entrada) == 1 && strcmp(entrada, "FIM") != 0) {
                scanf("%d", &qtd);
                adicionarEstoque(&tcar_nomes, &tcar_qtds, &tcar_tam, &tcar_cap, entrada, qtd);
            }
            //tentativa de vendas do novo estoque
            realizarVendas(
                tcar_nomes, tcar_qtds, tcar_tam, 
                &julio_nomes, &julio_tam, &julio_cap, 
                &cariani_nomes, &cariani_tam, &cariani_cap, 
                &vendidos_nomes, &vendidos_tam, &vendidos_cap
            );
            
        } else if (strcmp(entrada, "FINAL") == 0) {
            break;
        }
    }
    
    printf("Colecao do Julio: ");
    for (int i = 0; i < julio_tam; i++) {
        printf("%s", julio_nomes[i]);
        if (i < julio_tam - 1) printf(", ");
    }

    printf("\n");

    printf("Colecao do Cariani: ");
    for (int i = 0; i < cariani_tam; i++) {
        printf("%s", carian
        i_nomes[i]);
        if (i < cariani_tam - 1) printf(", ");
    }

    printf("\n");

    printf("Total de carros vendidos = %d\n", vendidos_tam);
    printf("Carros vendidos: ");
    for (int i = 0; i < vendidos_tam; i++) {
        printf("%s", vendidos_nomes[i]);
        if (i < vendidos_tam - 1) printf(", ");
    }

    printf("\n");

    free(tcar_nomes);
    free(tcar_qtds);
    free(julio_nomes);
    free(cariani_nomes);
    free(vendidos_nomes);

    return 0;
}