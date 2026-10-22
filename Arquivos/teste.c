#include <stdio.h>

typedef struct{

    char nome[50];
    int idade;
    char sexo;

}Pessoa;

int tam = 10;
Pessoa lista[10];
int quant = 0;

int cadastrarPessoa(){

    if(quant < tam){

        Pessoa p;

        scanf("%*c"); //eliminar o buffer do teclado

        printf("\n");
        printf("Nome: ");
        fgets(p.nome, 50, stdin);
        printf("Idade e sexo m ou f: ");
        scanf("%d %c", &p.idade, &p.sexo);
        lista[quant] = p;
        quant++;

        return 1;
    }
    else{
        printf("O vetor esta cheio\n\n");
        return 0;
    }
}

void imprimirDados(){

    for(int i = 0; i < quant; i++){

        printf("\n");
        printf("Nome: %s", lista[i].nome);
        printf("Idade: %d\tSexo: %c\n", lista[i].idade, lista[i].sexo);
    }
}

//escrevendo os dados no arquivo
void salvarArquivo(){

    FILE *arquivo = fopen("lista.txt", "w");

    if(arquivo != NULL){

        fprintf(arquivo, "%d\n", quant);
        for(int i = 0; i < quant; i++){

            fprintf(arquivo, "%s", lista[i].nome);
            fprintf(arquivo, "%d\n", lista[i].idade);
            fprintf(arquivo, "%c\n", lista[i].sexo);
        }

        fclose(arquivo);
    }
    else{
        printf("Erro ao abrir o arquivo!\n");
    }
}

void salvarArquivos2(){

    FILE *arquivo = fopen("lista2.txt", "wb");

    if(arquivo != NULL){
        fprintf(arquivo, "%d\n", quant);
        fwrite(lista, sizeof(Pessoa), quant, arquivo);  
        fclose(arquivo);
    }

    else{
        printf("Erro ao abrir o arquivo!");
    }

}

//lendo do arquivo
void lerArquivo(){

    FILE *arquivo = fopen("lista.txt", "r");

    if(arquivo != NULL){
        
        fscanf(arquivo, "%d\n", &quant);
        for(int i = 0; i < quant; i++){
            Pessoa p;

            fgets(p.nome, 50, arquivo);
            fscanf(arquivo, "%d\n", &p.idade);
            fscanf(arquivo, "%c\n", &p.sexo);

            lista[i] = p;
        }
        
        fclose(arquivo);
    }

    else{
        printf("Erro ao abrir o arquivo\n");
    }
}

void lerArquivos2(){

    FILE *arquivo = fopen("lista2.txt", "rb");

    if(arquivo != NULL){
        fscanf(arquivo, "%d\n", &quant);
        fread(lista, sizeof(Pessoa), quant, arquivo);
        fclose(arquivo);
    }
    else{
        printf("Erro ao abrir o arquivo");
    }
}

int main(){

    int operacao;

    do{

        printf("\n");
        printf("Escolha a operacao:\n0- Sair\n1- Cadastrar\n2- Imprimir\n3- Salvar no arquivo texto\n4- Ler do arquivo texto\n");
        printf("5- Salvar no arquivo binario\n6- Ler do arquivo binario\n");
        scanf("%d", &operacao);

        switch (operacao){

        case 0:
            printf("Volte sempre!\n");
            break;

        case 1:
            cadastrarPessoa();
            break;
            
        case 2:
            imprimirDados();
            break;

        case 3:
            salvarArquivo();
            break;

        case 4:
            lerArquivo();
            break;

        case 5:
            salvarArquivos2();
            break;
            
        case 6:
            lerArquivos2();
            break;    
        
        default:
            printf("Operacao invalida\n\n");
        }

    }while(operacao != 0);

    return 0;
}