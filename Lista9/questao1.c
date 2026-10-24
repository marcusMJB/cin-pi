#include <stdio.h>
#include <string.h>

int main(){

    FILE *arquivoLeitura;
    FILE *arquivoEscrita;

    arquivoLeitura = fopen("requisicoes.txt", "r");
    arquivoEscrita = fopen("relatorio.txt", "w");

    if(arquivoLeitura == NULL || arquivoEscrita == NULL){

        printf("Erro ao abrir o arquivo\n");
        if(arquivoLeitura){
            fclose(arquivoLeitura);
        }
        if(arquivoEscrita){
            fclose(arquivoEscrita);
        }
        return 1;
    }

    int numeroRequisicao;
    fscanf(arquivoLeitura, "%d\n", &numeroRequisicao);

    fprintf(arquivoEscrita, "=== RELATORIO DE REQUISICOES ===\n");
    fprintf(arquivoEscrita, "Total de requisicoes: %d\n", numeroRequisicao);

    char endpoint[51];
    int codigo, tempo;
    int sucesso = 0, redirecionamento = 0, erroCliente = 0, erroServidor = 0, somaTempo = 0, maiorTempo = 0;
    double mediaTempo = 0.0, taxaErro = 0.0;
    char maiorendpoint[51];

    for(int i = 0; i < numeroRequisicao; i++){
        
        fscanf(arquivoLeitura, "%50s %d %d", endpoint, &codigo, &tempo);

        if(codigo >= 200 && codigo <= 299){
            sucesso++;
        }else if(codigo >= 300 && codigo <= 399){
            redirecionamento++;
        }else if(codigo >= 400 && codigo <= 499){
            erroCliente++;
        }else if(codigo >= 500 && codigo <= 599){
            erroServidor++;
        }
        somaTempo += tempo;

        if(i == 0 || tempo > maiorTempo){
            maiorTempo = tempo;
            strcpy(maiorendpoint, endpoint);
        }
    }
    if(numeroRequisicao != 0){
        mediaTempo = (double)somaTempo / numeroRequisicao;
    }
    if(numeroRequisicao != 0){
        taxaErro = 100.0 * (erroCliente + erroServidor)/numeroRequisicao;
    }

    fprintf(arquivoEscrita, "Sucesso (2xx): %d\n", sucesso);
    fprintf(arquivoEscrita, "Redirecionamento (3xx): %d\n", redirecionamento);
    fprintf(arquivoEscrita, "Erro de cliente (4xx): %d\n", erroCliente);
    fprintf(arquivoEscrita, "Erro de servidor (5xx): %d\n", erroServidor);
    fprintf(arquivoEscrita, "Tempo medio de resposta: %.2f ms\n", mediaTempo);
    fprintf(arquivoEscrita, "Mais lenta: %s (%d ms)\n", maiorendpoint, maiorTempo);
    fprintf(arquivoEscrita, "Taxa de erro: %.2f%%\n", taxaErro);

    if(taxaErro < 10){
        fprintf(arquivoEscrita, "STATUS: SAUDAVEL");
    }else if(taxaErro >= 10 && taxaErro < 30){
        fprintf(arquivoEscrita, "STATUS: ATENCAO");
    }else if(taxaErro >= 30){
        fprintf(arquivoEscrita, "STATUS: CRITICO");
    }

    fclose(arquivoLeitura);
    fclose(arquivoEscrita);

    return 0;
}