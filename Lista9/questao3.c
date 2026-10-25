#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char sigla[20];
    int nota_acumulada;
} CentroAcademico;

typedef struct {
    int id_trabalho;
    char sigla_centro[20];
    int nota;
} Trabalho;

void converter_txt_para_bin(char *arq_txt, char *arq_bin) {
    FILE *arquivoLeitura = fopen(arq_txt, "r");
    FILE *arquivoEscrita = fopen(arq_bin, "wb");

    Trabalho trab;
    int idSessao, totalTrabalho;

    if (arquivoEscrita == NULL || arquivoLeitura == NULL) {
        printf("Erro ao abrir o arquivo\n");
        if (arquivoEscrita != NULL) fclose(arquivoEscrita);
        if (arquivoLeitura != NULL) fclose(arquivoLeitura);
        return;
    }

    if (fscanf(arquivoLeitura, "%d\n", &idSessao) != 1 || 
        fscanf(arquivoLeitura, "%d\n", &totalTrabalho) != 1) {
        printf("Erro na leitura inicial\n");
        fclose(arquivoEscrita);
        fclose(arquivoLeitura);
        return;
    }

    fwrite(&idSessao, sizeof(int), 1, arquivoEscrita);
    fwrite(&totalTrabalho, sizeof(int), 1, arquivoEscrita);

    for (int i = 0; i < totalTrabalho; i++) {
        memset(&trab, 0, sizeof(Trabalho));

        if (fscanf(arquivoLeitura, "%d %s %d\n", &trab.id_trabalho, trab.sigla_centro, &trab.nota) != 3) {
            printf("Erro na leitura dos dados dos trabalhos\n");
            fclose(arquivoEscrita);
            fclose(arquivoLeitura);
            return;
        }

        fwrite(&trab, sizeof(Trabalho), 1, arquivoEscrita);
    }

    printf("Processamento concluido: %s -> %s\n", arq_txt, arq_bin);

    fclose(arquivoEscrita);
    fclose(arquivoLeitura);
}

void processar_planilha_bin(char *arq_bin, CentroAcademico *centros, int qtd_centros, Trabalho **trabalhos, int *qtd_trabalhos) {
    FILE *arquivo = fopen(arq_bin, "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        *trabalhos = NULL;
        *qtd_trabalhos = 0;
        return;
    }

    int idSessao, totaTrabalhosVer;

    if (fread(&idSessao, sizeof(int), 1, arquivo) != 1 || 
        fread(&totaTrabalhosVer, sizeof(int), 1, arquivo) != 1) {
        printf("Erro na leitura inicial\n");
        fclose(arquivo);
        *trabalhos = NULL;
        *qtd_trabalhos = 0;
        return;
    }

    *trabalhos = (Trabalho *) malloc(totaTrabalhosVer * sizeof(Trabalho));
    if (*trabalhos == NULL) {
        printf("Erro ao alocar memoria\n");
        fclose(arquivo);
        *qtd_trabalhos = 0;
        return;
    }

    int verificados = 0;
    for (int i = 0; i < totaTrabalhosVer; i++) {
        if (fread(&((*trabalhos)[i]), sizeof(Trabalho), 1, arquivo) == 1) {
            verificados++;

            for (int j = 0; j < qtd_centros; j++) {
                if (strcmp((*trabalhos)[i].sigla_centro, centros[j].sigla) == 0) {
                    centros[j].nota_acumulada += (*trabalhos)[i].nota;
                    break;
                }
            }
        } else {
            printf("Erro na leitura dos dados do trabalho\n");
            break;
        }
    }

    *qtd_trabalhos = verificados;
    fclose(arquivo);
}

void ordenarCentros(CentroAcademico *centros, int n) {
    for (int i = 1; i < n; i++) {
        CentroAcademico chave = centros[i];
        int j = i - 1;

        while (j >= 0 && centros[j].nota_acumulada < chave.nota_acumulada) {
            centros[j + 1] = centros[j];
            j--;
        }

        centros[j + 1] = chave;
    }
}

void ordenarTrabalhos(Trabalho *trabalhos, int n) {
    for (int i = 1; i < n; i++) {
        Trabalho chave = trabalhos[i];
        int j = i - 1;

        while (j >= 0 && trabalhos[j].nota < chave.nota) {
            trabalhos[j + 1] = trabalhos[j];
            j--;
        }

        trabalhos[j + 1] = chave;
    }
}

void exibirRanking(CentroAcademico *centros, int qtd_centros, Trabalho *trabalhos, int qtd_trabalhos) {
    printf("=== RANKING INSTITUCIONAL (CENTROS) ===\n");
    for (int i = 0; i < qtd_centros; i++) {
        printf("%do Lugar: %s - %d pontos\n", i + 1, centros[i].sigla, centros[i].nota_acumulada);
    }

    printf("=== RANKING INDIVIDUAL (TOP 3 TRABALHOS) ===\n");
    int limite = (qtd_trabalhos < 3) ? qtd_trabalhos : 3;

    for (int i = 0; i < limite; i++) {
        printf("%do Lugar: Trabalho %d (%s) - Nota %d\n", i + 1, trabalhos[i].id_trabalho, trabalhos[i].sigla_centro, trabalhos[i].nota);
    }
}

int main() {
    int qtd_centros;
    if (scanf("%d", &qtd_centros) != 1) return 1;

    CentroAcademico *centros = (CentroAcademico *) malloc(qtd_centros * sizeof(CentroAcademico));
    if (centros == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    for (int i = 0; i < qtd_centros; i++) {
        scanf("%s", centros[i].sigla);
        centros[i].nota_acumulada = 0;
    }

    int planilhas;
    if (scanf("%d", &planilhas) != 1) {
        free(centros);
        return 1;
    }

    char arqTxt[100], arqBin[100];
    
    Trabalho *todos_trabalhos = NULL;
    int total_trabalhos = 0;

    for (int i = 0; i < planilhas; i++) {
        scanf("%s %s", arqTxt, arqBin);

        converter_txt_para_bin(arqTxt, arqBin);

        Trabalho *trabalhos_temp = NULL;
        int qtdTrabalhosTemp = 0;

        processar_planilha_bin(arqBin, centros, qtd_centros, &trabalhos_temp, &qtdTrabalhosTemp);

        if (qtdTrabalhosTemp > 0 && trabalhos_temp != NULL) {
            Trabalho *temp = (Trabalho *) realloc(todos_trabalhos, (total_trabalhos + qtdTrabalhosTemp) * sizeof(Trabalho));
            if (temp != NULL) {
                todos_trabalhos = temp;
                for (int k = 0; k < qtdTrabalhosTemp; k++) {
                    todos_trabalhos[total_trabalhos + k] = trabalhos_temp[k];
                }
                total_trabalhos += qtdTrabalhosTemp;
            }
            free(trabalhos_temp);
        }
    }

    //Ordenacao
    ordenarCentros(centros, qtd_centros);
    ordenarTrabalhos(todos_trabalhos, total_trabalhos);

    //Exibicao
    exibirRanking(centros, qtd_centros, todos_trabalhos, total_trabalhos);

    free(centros);
    if (todos_trabalhos != NULL) {
        free(todos_trabalhos);
    }

    return 0;
}