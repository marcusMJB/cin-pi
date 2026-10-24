#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { 
 char titular[51]; /* nome do titular */ 
 float saldo; /* saldo da conta */ 
 int ativa; /* 1 = conta ativa, 0 = conta encerrada */ 
} Conta;


int main(){

    int numeroContas;
    scanf("%d", &numeroContas);
    int contagemConta;

    Conta conta;
    FILE *arquivo = fopen("contas.bin", "wb+");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    for(int i = 0; i < numeroContas; i++){

        contagemConta = i + 1;
        scanf("%f", &conta.saldo);
        getchar();
        fgets(conta.titular, 50, stdin);
        conta.titular[strcspn(conta.titular, "\n")] = '\0';
        conta.ativa = 1; 

        fwrite(&contagemConta, sizeof(int), 1, arquivo);
        fwrite(&conta, sizeof(Conta), 1, arquivo);
    }
    fseek(arquivo, 0, SEEK_SET); //volta o cursor para o incio do arquivo para executar a leitura
    
    int idConta, operacoes;
    char opcao[10];
    float valor;
    scanf("%d", &operacoes);

    for(int i = 0; i < operacoes; i++){

        scanf("%s", opcao);
        if(strcmp(opcao, "CONSULTAR") == 0){
            scanf("%d", &idConta);

            if(idConta < 1 || idConta > numeroContas){
                printf("Conta inexistente\n");
            }
            else{
                int id;
                Conta c;    

                //leva o cursor a posição escolhida e faz a leitura
                fseek(arquivo, (idConta - 1) * (sizeof(int) + sizeof(Conta)), SEEK_SET);
                fread(&id, sizeof(int), 1, arquivo);
                fread(&c, sizeof(Conta), 1, arquivo);

                if(c.ativa == 1){
                    printf("%s - saldo: %.2f\n", c.titular, c.saldo);
                }
                else{
                    printf("Conta encerrada\n");
                }
            }

        }else if(strcmp(opcao, "DEPOSITAR") == 0){
            scanf("%d %f", &idConta, &valor);

            if(idConta < 1 || idConta > numeroContas){
                printf("Conta inexistente\n");
            }
            else{
                int id;
                Conta c;

                //leva o cursor a posição escolhida, ler, deposita, salva no arquivo, ler e exibi
                fseek(arquivo, (idConta - 1) * (sizeof(int) + sizeof(Conta)), SEEK_SET);
                fread(&id, sizeof(int), 1, arquivo);
                fread(&c, sizeof(Conta), 1, arquivo);

                if(c.ativa == 1){
                    c.saldo += valor;
                    fseek(arquivo, (idConta - 1) * (sizeof(int) + sizeof(Conta)), SEEK_SET);
                    fwrite(&idConta, sizeof(int), 1, arquivo);
                    fwrite(&c, sizeof(Conta), 1, arquivo);

                    fseek(arquivo, (idConta - 1) * (sizeof(Conta) + sizeof(int)), SEEK_SET);
                    fread(&id, sizeof(int), 1, arquivo);
                    fread(&c, sizeof(Conta), 1, arquivo);
                    printf("Saldo atual: %.2f\n", c.saldo);
                }
                else{
                    printf("Conta encerrada\n");
                }    
            }

        }else if(strcmp(opcao, "SACAR") == 0){
            scanf("%d %f", &idConta, &valor);

            if(idConta < 1 || idConta > numeroContas){
                printf("Conta inexistente\n");
            }
            else{
                int id;
                Conta c;

                //leva o cursor a posição escolhida, ler, saca, salva no arquivo, ler e exibi
                fseek(arquivo, (idConta - 1) * (sizeof(int) + sizeof(Conta)), SEEK_SET);
                fread(&id, sizeof(int), 1, arquivo);
                fread(&c, sizeof(Conta), 1, arquivo);

                if(c.ativa == 1){
                    if(c.saldo >= valor){
                        c.saldo -= valor;

                        fseek(arquivo, (idConta - 1) * (sizeof(int) + sizeof(Conta)), SEEK_SET);
                        fwrite(&id, sizeof(int), 1, arquivo);
                        fwrite(&c, sizeof(Conta), 1, arquivo);

                        fseek(arquivo, (idConta - 1) * (sizeof(int) + sizeof(Conta)), SEEK_SET);
                        fread(&id, sizeof(int), 1, arquivo);
                        fread(&c, sizeof(Conta), 1, arquivo);
                        printf("Saldo atual: %.2f\n", c.saldo);
                    }
                    else{
                        printf("Saldo insuficiente\n");
                    }
                }
                else{
                    printf("Conta encerrada\n");
                }    
            }

        }else if(strcmp(opcao, "ENCERRAR") == 0){
            scanf("%d", &idConta);

            if(idConta < 1 || idConta > numeroContas){
                printf("Conta inexistente\n");
            }
            else{
                int id;
                Conta c;

                //leva o cursor a posição escolhida, ler, encerra e salva no arquivo
                fseek(arquivo, (idConta - 1) * (sizeof(int) + sizeof(Conta)), SEEK_SET);
                fread(&id, sizeof(int), 1, arquivo);
                fread(&c, sizeof(Conta), 1, arquivo);

                c.ativa = 0;
                fseek(arquivo, (idConta - 1) * (sizeof(int) + sizeof(Conta)), SEEK_SET);
                fwrite(&id, sizeof(int), 1, arquivo);
                fwrite(&c, sizeof(Conta), 1, arquivo);

                printf("Conta encerrada com sucesso\n");
            }
        }

    }

    printf("Contas ativas:\n");
    fseek(arquivo, 0, SEEK_SET);
    int posicao;
    Conta cc;
    while(fread(&posicao, sizeof(int), 1, arquivo) == 1 && fread(&cc, sizeof(Conta), 1, arquivo) == 1){

        if(cc.ativa == 1){
            printf("%d %s %.2f\n", posicao, cc.titular, cc.saldo);
        }
    }

    fclose(arquivo);
    return 0;
}