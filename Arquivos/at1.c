#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int matricula;
    char nome[50];
    float nota1;
    float nota2;
    float media;
} Aluno;

void cadastrarAluno(char nomeArquivo[]){

    FILE *arquivo = fopen(nomeArquivo, "a");
    Aluno aluno;

    if(arquivo != NULL){

        printf("Matricula do aluno: ");
        scanf("%d", &aluno.matricula);
        fprintf(arquivo, "%s: ", "Matricula");
        fprintf(arquivo, "%d\n", aluno.matricula);
        getchar();

        printf("Nome do aluno: ");
        fgets(aluno.nome, 50, stdin);
        fprintf(arquivo, "%s: ", "Nome");
        fprintf(arquivo, "%s\n", aluno.nome);

        printf("Nota 1: ");
        scanf("%f", &aluno.nota1);
        fprintf(arquivo, "%s: ", "Nota 1");
        fprintf(arquivo, "%f\n", aluno.nota1);


        printf("Nota 2: ");
        scanf("%f", &aluno.nota2);
        fprintf(arquivo, "%s: ", "Nota 2");
        fprintf(arquivo, "%f\n", aluno.nota2);

        aluno.media = (aluno.nota1 + aluno.nota2)/2;
        fprintf(arquivo, "%s: ", "Media");
        fprintf(arquivo, "%.2f\n", aluno.media);

        fclose(arquivo);
    }
    else{
        printf("\nErro ao abrir o arquivo\n");
    }
}

void exibirAlunos(char nomeArquivo[]){

    FILE *arquivo = fopen(nomeArquivo, "r");

    Aluno aluno;

    if(arquivo != NULL){

        while(feof(arquivo)){

            printf("Matricula: ");
            fscanf(arquivo, "%d\n", &aluno.matricula);

            printf("Nome: ");
            fgets(aluno.nome, 50, arquivo);

            printf("Nota 1: ");
            fscanf(arquivo, "%f\n", &aluno.nota1);

            printf("Nota 2: ");
            fscanf(arquivo, "%f\n", &aluno.nota2);

            printf("Media: ");
            fscanf(arquivo, "%f\n", &aluno.media);
        }

        fclose(arquivo);
    }
    else{
        printf("\nNenhum registro encontrado.\n");
    }
}

void relatorioAprovados(char nomeArquivo[], char arquivoAprovados[]){

    FILE *arquivo = fopen(nomeArquivo, "r");
    FILE *arquivoApr = fopen(arquivoAprovados, "w");
     
    if(arquivo != NULL){


    }

    else{
        printf("\nErro ao abrir o arquivo!\n");
    }
}

int main(){

    int opcao;

    do{

        printf("Escolha uma das opcoes:\n");
        printf("0- Sair\n1- Cadastrar aluno\n2- Exibir dados dos alunos\n3- Relatorio de aprovados\n");
        scanf("%d", &opcao);

        switch(opcao){

        case 0:
            break;
        case 1:
            cadastrarAluno("aluno.txt");
            break;
        case 2:
            exibirAlunos("aluno.txt");
            break;
        case 3:
            relatorioAprovados("aluno.txt", "aprovados.txt");
            break;
        }

    }while(opcao != 0);

    return 0;
}