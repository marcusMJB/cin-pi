#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define tam 50

typedef struct
{
    char titulo[tam];
    char genero[tam];
    char studio[tam];
    char console[tam];
    int notas;
    int anoLancamento;

}Jogos;

void printAno(Jogos *vet, int t, int ano){

    int contador = 0;

    for (int i = 0; i < t; i++)
    {
        if(ano == vet[i].anoLancamento){
            printf("%s\n", vet[i].titulo);
            contador++;
        }
    }

    if (contador > 0) {
        printf("Tenho %d jogos || %d.\n", contador, ano);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printLetra(Jogos *vet, int t, char letra){

    int contador = 0;

    for (int i = 0; i < t; i++)
    {
        if(letra == vet[i].titulo[0]){
            printf("%s\n", vet[i].titulo);
            contador++;
        }
    }
    if (contador > 0) {
        printf("Tenho %d jogos || %c.\n", contador, letra);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printStudio(Jogos *vet, int t, char *studio){

    int contador = 0;

    for (int i = 0; i < t; i++)
    {
        if(strcmp(studio, vet[i].studio) == 0){
            printf("%s\n", vet[i].titulo);
            contador++;
        }
    }
    if (contador > 0) {
        printf("Tenho %d jogos || %s.\n", contador, studio);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printConsole(Jogos *vet, int t, char *console){

    int contador = 0;

    for (int i = 0; i < t; i++)
    {
        if(strcmp(console, vet[i].console) == 0){
            printf("%s\n", vet[i].titulo);
            contador++;
        }
    }
    if (contador > 0) {
        printf("Tenho %d jogos || %s.\n", contador, console);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printColecao(Jogos *vet, int t){

    for (int i = 0; i < t; i++)
    {
        printf("%s %d\n", vet[i].titulo, vet[i].notas);
    }
    
}

int main(){

    int numeroJogos;
    scanf("%d", &numeroJogos);

    Jogos *vetjogos = (Jogos *) malloc(numeroJogos * sizeof(Jogos));

    if(vetjogos == NULL){
        return 1;
    }

    for (int i = 0; i < numeroJogos; i++)
    {
        scanf("%s %s %s %s %d %d", vetjogos[i].titulo, vetjogos[i].genero, vetjogos[i].studio, vetjogos[i].console, &vetjogos[i].notas, &vetjogos[i].anoLancamento);

    }

    for (int i = 0; i < numeroJogos; i++)
    {
        if(vetjogos[i].notas > 7){
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");
        }

        else if(vetjogos[i].notas < 4){
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }
    }
    
    
    char opcao[tam];

    while (scanf("%s", opcao) != EOF)
    {
        if(strcmp(opcao, "printAno") == 0){

            int ano;
            scanf("%d", &ano);

            printAno(vetjogos, numeroJogos, ano);
        }
        else if(strcmp(opcao, "printLetra") == 0){

            char letra;
            scanf(" %c", &letra);

            printLetra(vetjogos, numeroJogos, letra);
        }

        else if(strcmp(opcao, "printStudio") == 0){

            char studio[tam];
            scanf("%s", studio);

            printStudio(vetjogos, numeroJogos, studio);
        }

        else if(strcmp(opcao, "printConsole") == 0){

            char console[tam];
            scanf("%s", console);

            printConsole(vetjogos, numeroJogos, console);
        }

        else if(strcmp(opcao, "printColecao") == 0){

            printColecao(vetjogos, numeroJogos);
        }
    }
    
    printf("Enjoei de jogar, agora vou ver TV.");


    free(vetjogos);
    vetjogos = NULL;
}