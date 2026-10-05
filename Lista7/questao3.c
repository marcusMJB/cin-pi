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
}

void subrotinaRecupera(Mecha *m, int slot, int input, int *output){

    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;

    *output = atrib1 + (slot * atrib2);
    m->energia_atual += *output;   
}

void subrotinaAtaque(Mecha *m, int slot, int input, int *output){

    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;

    if(m->energia_atual < atrib2){
        *output = 0;
    }
    else{
        *output = atrib1 + m->energia_atual + slot - input;

        if(*output < 0){
            *output = 0;
        }

        m->energia_atual -= atrib2;
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

        for (int j = 0; i < qtdSistemas; j++)
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
    
    for (int i = 0; i < quantidadeMecha; i++)
    {
        int dano = vetMechas[i]->valor_wintermute;

        //defesa
        for (int j = 0; j < vetMechas[i]->num_sistemas; j++)
        {
            if(vetMechas[i]->sistemas[j].subrotina == subrotinaDefesa){
                vetMechas[i]->sistemas[j].subrotina (vetMechas[i], j, dano, &dano);
            }
        }

        //recuperação
        for (int j = 0; j < vetMechas[i]->num_sistemas; j++)
        {
            if(vetMechas[i]->sistemas[j].subrotina == subrotinaRecupera){
                vetMechas[i]->sistemas[j].subrotina (vetMechas[i], j, dano, &dano);
            }
        }

        //ataque
        for (int j = 0; j < vetMechas[i]->num_sistemas; j++)
        {
            if(vetMechas[i]->sistemas[j].subrotina == subrotinaAtaque){
                vetMechas[i]->sistemas[j].subrotina (vetMechas[i], j, dano, &dano);
            }
        }
             
    }
    
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");
    printf()

    for (int i = 0; i < quantidadeMecha; i++)
    {
        free(vetMechas[i]);
    }
    free(vetMechas);
    vetMechas = NULL;
}