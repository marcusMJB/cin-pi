#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int dia, mes, ano;
} Contato;

void imprimir(Contato **c, int quant) {
    printf("\n\tLista de contatos:\n");
    printf("\t-------------------------------------------\n");

    for (int i = 0; i < quant; i++) {
        printf("\t%d = %02d/%02d/%04d\t%s\n", i + 1, c[i]->dia, c[i]->mes, c[i]->ano, c[i]->nome);
    }
    printf("\t-------------------------------------------\n");
}

void liberarMemoria(Contato **c, int *quant) {
    for (int i = 0; i < *quant; i++) {
        if (c[i] != NULL) {
            free(c[i]);   // Liberta a estrutura do contacto na memória Heap
            c[i] = NULL;  // Anula o ponteiro por segurança
        }
    }
    *quant = 0;           // Reinicia a contagem de contactos
    printf("\n\tMemoria libertada com sucesso!\n");
}

int cadastarContato(Contato **c, int quant, int tam) {
    if (quant < tam) {
        Contato *novo = malloc(sizeof(Contato));
        if (novo == NULL) return 0;

        printf("\nDigite o nome do contato: ");
        scanf("%49[^\n]", novo->nome);
        printf("Digite a data de aniversario dd mm aaaa: ");
        scanf("%d%d%d", &novo->dia, &novo->mes, &novo->ano);
        getchar();

        c[quant] = novo;
        return 1;
    } else {
        printf("\n\tImpossivel novo cadastro. Vetor cheio!\n");
        return 0;
    }
}

void alterarContato(Contato **c, int quant) {
    int id;

    imprimir(c, quant);

    printf("\n\tDigite o codigo de contato que deseja alterar: ");
    scanf("%d", &id);
    getchar();
    id--;

    if (id >= 0 && id < quant) {
        printf("\nDigite o novo nome do contato: ");
        scanf("%49[^\n]", c[id]->nome);
        printf("Digite a nova data de aniversario dd mm aaaa: ");
        scanf("%d%d%d", &c[id]->dia, &c[id]->mes, &c[id]->ano);
        getchar();
    } else {
        printf("\n\tCodigo invalido!\n");
    }
}

void salvar(Contato **c, int quant, char arq[]) {
    FILE *file = fopen(arq, "w");

    if (file) {
        fprintf(file, "%d\n", quant);
        for (int i = 0; i < quant; i++) {
            fputs(c[i]->nome, file);
            fputc('\n', file);
            fprintf(file, "%d %d %d\n", c[i]->dia, c[i]->mes, c[i]->ano);
        }
        fclose(file);
    } else {
        printf("\n\tNao foi possivel abrir o arquivo\n");
    }
}

int lerArquivo(Contato **c, char arq[]) {
    FILE *file = fopen(arq, "r");
    int quant = 0;

    if (file) {
        fscanf(file, "%d\n", &quant);
        for (int i = 0; i < quant; i++) {
            Contato *novo = malloc(sizeof(Contato));
            fscanf(file, "%49[^\n]\n", novo->nome);
            fscanf(file, "%d %d %d\n", &novo->dia, &novo->mes, &novo->ano);
            c[i] = novo;
        }
        fclose(file);
    } else {
        printf("\n\tNao foi possivel abrir o arquivo\n");
    }
    return quant;
}

void salvarB(char arq[], Contato **c, int quant) {
    FILE *file = fopen(arq, "wb");

    if (file) {
        for (int i = 0; i < quant; i++) {
            fwrite(c[i], sizeof(Contato), 1, file);
        }
        fclose(file);
    } else {
        printf("\nErro ao abrir o arquivo\n");
    }
}

int lerB(char arq[], Contato **c) {
    int quant = 0;
    FILE *file = fopen(arq, "rb");

    if (file) {
        Contato *novo = malloc(sizeof(Contato));
        while (fread(novo, sizeof(Contato), 1, file) == 1) {
            c[quant] = novo;
            quant++;
            novo = malloc(sizeof(Contato));
        }
        free(novo); // Libera o bloco alocado excedente ao atingir o EOF
        fclose(file);
    } else {
        printf("\nErro ao abrir o arquivo\n");
    }
    return quant;
}

void alterarB(char arq[]){

    FILE *file = fopen(arq, "rb+");
    Contato c;
    int id, i =1;

    if(file){
        printf("\n\tLista de contatos:\n");
        printf("\t-------------------------------\n");
        while (fread(&c, sizeof(Contato), 1, file))
        {
            printf("\t%d = %2d/%2d/%4d\t%s\n", i, c.dia, c.mes, c.ano, c.nome);
            i++;
        }
        printf("\t-------------------------------\n");
        
        printf("\n\tDigite o indice do contato que deseja alterar:\n\n");
        scanf("%d", &id);
        getchar();
        id--;

        if(id >= 0 && id < i-1){

            printf("\tDigite nome e data de nascimento dd mm aaaa: ");
            scanf("%49[^\n]%d%d%d", c.nome, &c.dia, &c.mes, &c.ano);
            fseek(file, id * sizeof(Contato), SEEK_SET);
            fwrite(&c, sizeof(Contato), 1, file);
        }
        fclose(file);
    }

    else{
        printf("\nErro ao abrir o arquivo!\n");
    }
}

int main() {
    Contato *agenda[50];
    char arquivo[] = "agenda.txt";
    char arquivo2[] = "agenda.dat";
    int opcao, tam = 50, quant = 0;

    do {
        printf("\n\t0- Sair\n\t1- Cadastrar\n\t2- Alterar\n\t3- Imprimir\n\t4- Salvar texto\n\t5- Ler arquivo texto\n");
        printf("\t6- Salvar Binario\n\t7- Ler Binario\n\t8- AlterarB\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

        case 0:
            liberarMemoria(agenda, &quant);
            printf("\n\tA encerrar o programa...\n");
            break;

        case 1:
            quant += cadastarContato(agenda, quant, tam);
            break;

        case 2:
            alterarContato(agenda, quant);
            break;

        case 3:
            imprimir(agenda, quant);
            break;

        case 4:
            salvar(agenda, quant, arquivo);
            break;

        case 5:
            quant = lerArquivo(agenda, arquivo);
            break;

        case 6:
            salvarB(arquivo2, agenda, quant);
            break;

        case 7:
            quant = lerB(arquivo2, agenda);
            break;

        case 8:
            alterarB(arquivo2);
            break;    

        default:
            if (opcao != 0) {
                printf("\n\tOpcao invalida\n");
            }
            break;
        }

    } while (opcao != 0);

    return 0;
}