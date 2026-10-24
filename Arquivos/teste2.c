#include <stdio.h>

typedef struct{
    char nome[50];
    int dia, mes, ano;

}Contato;

void escrever(char arq[]){

    Contato c;
    FILE *file = fopen(arq, "ab");

    if(arq != NULL){

        printf("Digite nome e data de nascimento dd mm aaaa:\n");
        scanf("%49[^\n] %d%d%d", c.nome, &c.dia, &c.mes, &c.ano);
        fwrite(&c, sizeof(Contato), 1, file);

        fclose(file);
    }
    else{
        printf("Erro ao abrir arquivo!\n");
    }
}

void leitura(char arq[]){

    Contato c;
    FILE *file = fopen(arq, "rb");

    if(arq != NULL){
        
        while(!feof(file)){

            if(fread(&c, sizeof(Contato), 1, file)){
                printf("\nNome: %s\nData: %d/%d/%d\n", c.nome, c.dia, c.mes, c.ano);
            }      
        }
        fclose(file);
    }
    else{
        printf("Erro ao abrir arquivo!\n");
    }
}

int main(){

    char arquivo[] = {"agenda.dat"};
    escrever(arquivo);
    leitura(arquivo);

    return 0;
}