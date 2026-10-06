#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam 205
#define BUFFER_SIZE 256

typedef struct {
    char nomeCidade[tam];
    int tamPopulacao;
    char periculosidade[tam];
    char funcaoPais[tam];
} Dados;

void formatar(char *str) {
    if (str[0] == '\0') return;

    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] = str[0] - ('a' - 'A');
    }

    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
    }
}

int comparaCidadelas(const void *a, const void *b) {
    const Dados *c1 = (const Dados *)a;
    const Dados *c2 = (const Dados *)b;

    if (c1->tamPopulacao != c2->tamPopulacao) {
        return c2->tamPopulacao - c1->tamPopulacao;
    }

    int p1 = (int)strlen(c1->periculosidade);
    int p2 = (int)strlen(c2->periculosidade);
    if (p1 != p2) {
        return p2 - p1;
    }

    return strcmp(c1->nomeCidade, c2->nomeCidade);
}

void decodificarMensagem(const char *frase, Dados *d) {
    int idxNome = 0;
    int idxFuncao = 0;
    int pop = 0;
    int numAsteriscos = 0;
    int tamFrase = (int)strlen(frase);

    d->nomeCidade[0] = '\0';
    d->funcaoPais[0] = '\0';
    d->periculosidade[0] = '\0';
    d->tamPopulacao = 0;

    for (int i = 0; i < tamFrase; i++) {
        
        if (frase[i] == ' ' && i + 1 < tamFrase && frase[i + 1] == ' ') {
            while (i < tamFrase && frase[i] == ' ') {
                i++;
            }
            if (i < tamFrase) {
                char prox = frase[i];
                if ((prox >= 'A' && prox <= 'Z') || (prox >= 'a' && prox <= 'z')) {
                    if (idxFuncao < tam - 1) {
                        d->funcaoPais[idxFuncao++] = prox;
                    }
                }
            }
        }

      
        if (i < tamFrase) {
            char c = frase[i];

            if (c >= 'A' && c <= 'Z') {
                if (idxNome < tam - 1) {
                    d->nomeCidade[idxNome++] = c;
                }
            } else if (c >= '0' && c <= '9') {
                pop = pop * 10 + (c - '0');
            } else if (c == '*') {
                numAsteriscos++;
            }
        }
    }

    d->nomeCidade[idxNome] = '\0';
    d->funcaoPais[idxFuncao] = '\0';

    formatar(d->nomeCidade);
    formatar(d->funcaoPais);

    if (numAsteriscos >= tam) numAsteriscos = tam - 1;
    for (int k = 0; k < numAsteriscos; k++) {
        d->periculosidade[k] = '*';
    }
    d->periculosidade[numAsteriscos] = '\0';

    d->tamPopulacao = pop;
}

int mensagemEspecial(const char *frase) {
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == '!') {
            return 1;
        }
    }
    return 0;
}

int chaveEspecial(const char *frase) {
    int chave = 0;
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] >= '0' && frase[i] <= '9') {
            chave = chave * 10 + (frase[i] - '0');
        }
    }
    return chave;
}

int main() {
    int capacidade = 16;
    int quantidade = 0;
    int encontrouEspecial = 0;
    int chaveN = 0;

    Dados *vetDados = (Dados *) malloc(capacidade * sizeof(Dados));
    if (vetDados == NULL) {
        return 1;
    }

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (buffer[0] == '\0') continue;

        if (mensagemEspecial(buffer)) {
            chaveN = chaveEspecial(buffer);
            encontrouEspecial = 1;
            continue; 
        }

        if (quantidade == capacidade) {
            capacidade *= 2;
            Dados *temp = (Dados *) realloc(vetDados, capacidade * sizeof(Dados));
            if (temp == NULL) {
                free(vetDados);
                return 1;
            }
            vetDados = temp;
        }

        decodificarMensagem(buffer, &vetDados[quantidade]);
        quantidade++;
    }

    if (!encontrouEspecial || chaveN < 1 || chaveN > quantidade) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } else {
        qsort(vetDados, quantidade, sizeof(Dados), comparaCidadelas);

        Dados cidadelaAchada = vetDados[chaveN - 1];
        int numAsteriscos = (int)strlen(cidadelaAchada.periculosidade);

        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade %s.",
               cidadelaAchada.nomeCidade,
               cidadelaAchada.tamPopulacao,
               cidadelaAchada.funcaoPais,
               cidadelaAchada.periculosidade);

        if (cidadelaAchada.tamPopulacao >= 1000 && numAsteriscos > 3) {
            printf(" Talvez seja melhor desistir...\n");
        } else if (cidadelaAchada.tamPopulacao >= 1000) {
            printf(" Um lugar denso, vai ser difícil achar ela.\n");
        } else if (numAsteriscos > 3) {
            printf(" Vai ser complicado entrar lá.\n");
        }
    }

    free(vetDados);
    return 0;
}