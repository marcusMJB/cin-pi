#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib2;     // Atk: Custo Ener. | Def: Bônus de Slot   | Utl: Multiplicador
    
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;                // Identificador único (0 até N-1)
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;       // Contexto de dano enviado pelo Comando
    SubSistema sistemas[]; // O Flexible Array Member (FAM)
};

void subrotinaDefesa(Mecha *m, int slot, int input, int *output){

    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;
    
    *output = input - atrib1 - (slot * atrib2);

    if(*output < 0){
        *output = 0;
    }

    printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[slot].nome, *output);
}

void subrotinaRecupera(Mecha *m, int slot, int input, int *output){

    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;

    *output = atrib1 + (slot * atrib2);
    m->energia_atual += *output;  
    
    printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[slot].nome, m->energia_atual);
}

void subrotinaAtaque(Mecha *m, int slot, int input, int *output){

    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;

    if(m->energia_atual < atrib2){
        *output = 0;
        printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[slot].nome);
    }
    else{
        *output = atrib1 + m->energia_atual + slot - input;

        if(*output < 0){
            *output = 0;
        }

        m->energia_atual -= atrib2;

        printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[slot].nome, *output, m->energia_atual);
    }
}

void ordenar(Mecha **vet, int qtd){
    for (int i = 0; i < qtd - 1; i++)
    {
        for (int j = 0; j < qtd - i - 1; j++)
        {
            if(vet[j]->id > vet[j+1]->id){
                Mecha *aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
        
    }
    
}

int main(){

    int quantidadeMecha;
    scanf("%d", &quantidadeMecha);

    Mecha **vetMechas = malloc(quantidadeMecha * sizeof(Mecha*));

    for (int i = 0; i < quantidadeMecha; i++)
    {
        int id, energiaInicial, qtdSistemas;
        char modelo[50];

        scanf("%d %s %d %d", &id, modelo, &energiaInicial, &qtdSistemas);

        vetMechas[i] = malloc(sizeof(Mecha) + qtdSistemas * sizeof(SubSistema));

        vetMechas[i]->id = id;
        strcpy(vetMechas[i]->modelo, modelo);
        vetMechas[i]->energia_atual = energiaInicial;
        vetMechas[i]->num_sistemas = qtdSistemas;

        for (int j = 0; j < qtdSistemas; j++)
        {
            char tipo;

            scanf(" %c %s %d %d", &tipo, vetMechas[i]->sistemas[j].nome, &vetMechas[i]->sistemas[j].atrib1, &vetMechas[i]->sistemas[j].atrib2);
            
            if(tipo == 'A'){
                vetMechas[i]->sistemas[j].subrotina = subrotinaAtaque;
            }
            else if(tipo == 'D'){
                vetMechas[i]->sistemas[j].subrotina = subrotinaDefesa;
            }

            else if(tipo == 'U'){
                vetMechas[i]->sistemas[j].subrotina = subrotinaRecupera;
            }
        }
        scanf("%d", &vetMechas[i]->valor_wintermute);
    }
    
    ordenar(vetMechas, quantidadeMecha);

    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < quantidadeMecha; i++)
    {
        int dano = vetMechas[i]->valor_wintermute;
        int resultado = 0;

        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", vetMechas[i]->id, vetMechas[i]->modelo, vetMechas[i]->energia_atual);

        //defesa
        for (int j = 0; j < vetMechas[i]->num_sistemas; j++)
        {
            if(vetMechas[i]->sistemas[j].subrotina == subrotinaDefesa){
                vetMechas[i]->sistemas[j].subrotina (vetMechas[i], j, dano, &resultado);
            }
        }

        //recuperação
        for (int j = 0; j < vetMechas[i]->num_sistemas; j++)
        {
            if(vetMechas[i]->sistemas[j].subrotina == subrotinaRecupera){
                vetMechas[i]->sistemas[j].subrotina (vetMechas[i], j, dano, &resultado);
            }
        }

        //ataque
        for (int j = 0; j < vetMechas[i]->num_sistemas; j++)
        {
            if(vetMechas[i]->sistemas[j].subrotina == subrotinaAtaque){
                vetMechas[i]->sistemas[j].subrotina (vetMechas[i], j, dano, &resultado);
            }
        }
           
        printf("ENERGIA FINAL: %d\n", vetMechas[i]->energia_atual);
        printf("-----------------------------------------\n");
    }
    
    printf("Esquadrao pronto para o combate.");

    for (int i = 0; i < quantidadeMecha; i++)
    {
        free(vetMechas[i]);
    }
    free(vetMechas);
    vetMechas = NULL;
}