#include <stdio.h>
#include <string.h>

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
        fprintf(arquivo, "%d\n", aluno.matricula);
        getchar();

        printf("Nome do aluno: ");
        fgets(aluno.nome, 50, stdin);
        aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
        fprintf(arquivo, "%s\n", aluno.nome);

        printf("Nota 1: ");
        scanf("%f", &aluno.nota1);
        fprintf(arquivo, "%f\n", aluno.nota1);


        printf("Nota 2: ");
        scanf("%f", &aluno.nota2);
        fprintf(arquivo, "%f\n", aluno.nota2);

        aluno.media = (aluno.nota1 + aluno.nota2)/2;
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

        while(fscanf(arquivo, "%d\n", &aluno.matricula) == 1){

            printf("Matricula: %d\n", aluno.matricula);

            fgets(aluno.nome, 50, arquivo);
            printf("Nome: %s", aluno.nome);

            fscanf(arquivo, "%f\n", &aluno.nota1);
            printf("Nota 1: %.2f\t", aluno.nota1);

            fscanf(arquivo, "%f\n", &aluno.nota2);
            printf("Nota 2: %.2f\t", aluno.nota2);

            fscanf(arquivo, "%f\n", &aluno.media);
            printf("Media: %.2f\n\n", aluno.media);
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
    Aluno aluno; 

    if(arquivo != NULL){

        if(arquivoApr != NULL){

            while(fscanf(arquivo, "%d\n", &aluno.matricula) == 1){

                fgets(aluno.nome, 50, arquivo);
                aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
                fscanf(arquivo, "%f\n", &aluno.nota1);
                fscanf(arquivo, "%f\n", &aluno.nota2);
                fscanf(arquivo, "%f\n", &aluno.media);

                if(aluno.media >= 7){

                    fprintf(arquivoApr, "%d\n", aluno.matricula);
                    fprintf(arquivoApr, "%s\n", aluno.nome);
                    fprintf(arquivoApr, "%f\n", aluno.nota1);
                    fprintf(arquivoApr, "%f\n", aluno.nota2);
                    fprintf(arquivoApr, "%f\n", aluno.media);

                }
            }

            
            fclose(arquivoApr);
        }

        else{
            printf("\nErro ao abrir o arquivo!\n");
        }
        fclose(arquivo);
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