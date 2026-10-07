#include <stdio.h>

union Identificacao {
    unsigned int matricula;
    unsigned long long cpf;
    unsigned int temporario;
};

struct Permissoes {
    unsigned laboratorio : 1;
    unsigned biblioteca : 1;
    unsigned estacionamento : 1;
    unsigned servidores : 1;
    unsigned noturno : 1;
    unsigned bloqueado : 1;
};

typedef struct Cartao {
    char tipo;
    union Identificacao id;
    struct Permissoes perm;
} Cartao;

int main() {
    int n;
    scanf("%d", &n);

    Cartao cartoes[100];

    //cadastro dos Cartões
    for (int i = 0; i < n; i++) {
        scanf(" %c", &cartoes[i].tipo);

        if (cartoes[i].tipo == 'M') {
            scanf("%u", &cartoes[i].id.matricula);
        } else if (cartoes[i].tipo == 'C') {
            scanf("%llu", &cartoes[i].id.cpf);
        } else if (cartoes[i].tipo == 'T') {
            scanf("%u", &cartoes[i].id.temporario);
        }

        int lab, bib, est, serv, notu, bloq;
        scanf("%d %d %d %d %d %d", &lab, &bib, &est, &serv, &notu, &bloq);

        cartoes[i].perm.laboratorio = lab;
        cartoes[i].perm.biblioteca = bib;
        cartoes[i].perm.estacionamento = est;
        cartoes[i].perm.servidores = serv;
        cartoes[i].perm.noturno = notu;
        cartoes[i].perm.bloqueado = bloq;
    }

    int q;
    scanf("%d", &q);

    //Processamento das Solicitações de Acesso
    for (int i = 0; i < q; i++) {
        char tipo_req, area, periodo;
        union Identificacao id_req;

        scanf(" %c", &tipo_req);

        if (tipo_req == 'M') {
            scanf("%u", &id_req.matricula);
        } else if (tipo_req == 'C') {
            scanf("%llu", &id_req.cpf);
        } else if (tipo_req == 'T') {
            scanf("%u", &id_req.temporario);
        }

        scanf(" %c %c", &area, &periodo);

        //Busca do cartão cadastrado
        int indice_encontrado = -1;
        for (int j = 0; j < n; j++) {
            if (cartoes[j].tipo == tipo_req) {
                if (tipo_req == 'M' && cartoes[j].id.matricula == id_req.matricula) {
                    indice_encontrado = j;
                    break;
                } else if (tipo_req == 'C' && cartoes[j].id.cpf == id_req.cpf) {
                    indice_encontrado = j;
                    break;
                } else if (tipo_req == 'T' && cartoes[j].id.temporario == id_req.temporario) {
                    indice_encontrado = j;
                    break;
                }
            }
        }

        //Validação do Acesso
        if (indice_encontrado == -1) {
            printf("CARTAO NAO ENCONTRADO\n");
        } else {
            Cartao c = cartoes[indice_encontrado];
            int acesso_permitido = 1;


            if (c.perm.bloqueado) {
                acesso_permitido = 0;
            }

            if (area == 'L' && !c.perm.laboratorio) acesso_permitido = 0;
            if (area == 'B' && !c.perm.biblioteca) acesso_permitido = 0;
            if (area == 'E' && !c.perm.estacionamento) acesso_permitido = 0;
            if (area == 'S' && !c.perm.servidores) acesso_permitido = 0;

            if (periodo == 'N' && !c.perm.noturno) {
                acesso_permitido = 0;
            }

            if (acesso_permitido) {
                printf("ACESSO LIBERADO\n");
            } else {
                printf("ACESSO NEGADO\n");
            }
        }
    }

    return 0;
}