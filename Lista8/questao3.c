#include <stdio.h>

typedef union {
    int dados;
    struct { unsigned int num : 30; unsigned int op : 2; } fase1;
    struct { unsigned int num : 28; unsigned int op : 2; unsigned int lixo : 2; } fase2;
    struct { unsigned int num : 26; unsigned int op : 2; unsigned int lixo : 4; } fase3;
} Segredo;

static int processar_fase(Segredo estado, int num_fase, int diff_desafio, int hab_pericia)
{
    unsigned int tipo_op;
    long long calc_val;

    switch (num_fase) {
    case 1:  tipo_op = estado.fase1.op; calc_val = estado.fase1.num; break;
    case 2:  tipo_op = estado.fase2.op; calc_val = estado.fase2.num; break;
    default: tipo_op = estado.fase3.op; calc_val = estado.fase3.num; break;
    }

    switch (tipo_op) {
    case 0:  calc_val = calc_val + diff_desafio / 10;         break;
    case 1:  calc_val = calc_val - (hab_pericia * 5) / 100;   break; 
    case 2:  calc_val = calc_val * 2 * hab_pericia;           break; 
    default: {                                                   
        int fator_div = diff_desafio / 5;
        calc_val = (fator_div != 0) ? calc_val / fator_div : calc_val;
        break;
    }
    }
 
    Segredo res;
    res.dados = 0;
    switch (num_fase) {
    case 1:  res.fase1.num = (unsigned int)calc_val; break;
    case 2:  res.fase2.num = (unsigned int)calc_val; break;
    default: res.fase3.num = (unsigned int)calc_val; break;
    }
    return res.dados;
}

static int validar_horario(int min_totais)
{

    return min_totais >= 18 * 60 || min_totais <= 4 * 60;
}

int main(void)
{
    int hab_pericia, hr_iniciar, min_iniciar, diff_desafio, gabarito, palpite_inicial;

    if (scanf("%d | %d | %d %d | %d %d", &hab_pericia, &hr_iniciar, &min_iniciar,
              &diff_desafio, &gabarito, &palpite_inicial) != 6)
        return 1;

    int diff_calculada = (diff_desafio - hab_pericia) - 5;
    int grau_dificuldade = (diff_calculada <= 5) ? 1 : (diff_calculada <= 10) ? 2 : 3;
    int total_etapas = grau_dificuldade;
    int tempo_por_etapa = 120 / hab_pericia; /* minutos por etapa */

    int tempo_inicio = hr_iniciar * 60 + min_iniciar;
    int tempo_fim = (tempo_inicio + total_etapas * tempo_por_etapa) % (24 * 60);

    Segredo chave_processada;
    chave_processada.dados = palpite_inicial;
    for (int idx_etapa = 1; idx_etapa <= total_etapas; idx_etapa++) {
        chave_processada.dados = processar_fase(chave_processada, idx_etapa, diff_desafio, hab_pericia);
    }

    Segredo chave_esperada;
    chave_esperada.dados = gabarito;

    printf("(%d) horario inicial: (%02d:%02d) | resultado encontrado: (%d)   horario final:(%02d:%02d)\n",
           palpite_inicial, hr_iniciar, min_iniciar, chave_processada.dados, tempo_fim / 60, tempo_fim % 60);

    int tempo_valido = validar_horario(tempo_inicio) && validar_horario(tempo_fim);

    if (tempo_valido && chave_processada.dados == chave_esperada.dados)
        printf("Beep sabia, Beep sempre sabe, BEEEEEEPPPPP\n");
    else
        printf("beepp, NA PROXIMA BEEP ABRIRAAAAAA\n");

    return 0;
}