#include <stdio.h>

int main(){

    FILE *file;
    char letra;

    file = fopen("conto.txt", "w");

    if(file != NULL){
        printf("Digite letras ou frases: ");
        scanf("%c", &letra);

        while (letra != '\n')
        {
            fputc(letra, file);
            scanf("%c", &letra);
        }
        fclose(file);

    }
    else{
        printf("\nErro ao abrir o arquivo!\n");
    }
}