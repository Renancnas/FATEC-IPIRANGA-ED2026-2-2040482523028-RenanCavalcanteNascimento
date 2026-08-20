
#include <stdio.h>

/* Constante simbolica: o tamanho da turma aparece em um unico lugar do codigo.
 * Se a turma mudar de tamanho, basta alterar esta linha - o vetor e todos os
 * lacos se ajustam automaticamente, sem numeros "soltos" espalhados no fonte. */
#define TAMANHO_TURMA 5

/* Prototipos das funcoes (permitem chamar as funcoes antes de defini-las). */
void  exibirCabecalho(void);
float calcularMedia(float vetor[], int tamanho);
void  simularAjuste(float notaOriginal, float bonus);
void  aplicarBonus(float *nota, float bonus);

int main(void)
{
    float notas[TAMANHO_TURMA];   /* vetor dimensionado pela constante simbolica */
    float bonus;
    int   i;

    /* Chamada unica da funcao sem parametros, no inicio da execucao. */
    exibirCabecalho();

    /* Preenchimento iterativo do vetor: um for controlado por TAMANHO_TURMA.
     * Usa-se for (e nao while) porque o numero de repeticoes e conhecido
     * antecipadamente - e exatamente o tamanho da turma. */
    for (i = 0; i < TAMANHO_TURMA; i++) {
        printf("Nota do aluno %d: ", i + 1);
        scanf("%f", &notas[i]);
    }

    printf("Informe o valor do bonus a aplicar: ");
    scanf("%f", &bonus);

    printf("\n--- Media da turma antes do ajuste ---\n");
    printf("Media inicial: %.2f\n", calcularMedia(notas, TAMANHO_TURMA));

    /* Passagem por valor: simularAjuste recebe apenas COPIAS dos valores.
     * Logo depois reimprimimos notas[0] para comprovar que nada mudou. */
    printf("\n--- Simulacao do ajuste (passagem por valor) ---\n");
    simularAjuste(notas[0], bonus);
    printf("Nota do aluno 1 apos a simulacao (inalterada): %.2f\n", notas[0]);

    /* Passagem por referencia: enviamos o ENDERECO de cada posicao (&notas[i]),
     * de modo que a funcao altera de fato o conteudo do vetor. */
    printf("\n--- Aplicacao real do bonus (passagem por referencia) ---\n");
    for (i = 0; i < TAMANHO_TURMA; i++) {
        aplicarBonus(&notas[i], bonus);
    }
    printf("Bonus de %.2f aplicado a todas as notas da turma.\n", bonus);

    /* Percurso final do vetor ja ajustado. */
    printf("\n--- Notas finais da turma ---\n");
    for (i = 0; i < TAMANHO_TURMA; i++) {
        printf("Aluno %d: %.2f\n", i + 1, notas[i]);
    }

    printf("\n--- Media da turma apos o ajuste ---\n");
    printf("Media final: %.2f\n", calcularMedia(notas, TAMANHO_TURMA));

    return 0;
}


void exibirCabecalho(void)
{
    printf("=================================\n");
    printf("SISTEMA DE NOTAS - TURMA ADS\n");
    printf("=================================\n");
}

float calcularMedia(float vetor[], int tamanho)
{
    float soma = 0.0f;
    int   i;

    for (i = 0; i < tamanho; i++) {
        soma += vetor[i];
    }

    return soma / tamanho;
}

void simularAjuste(float notaOriginal, float bonus)
{
    float resultado = notaOriginal + bonus;   /* altera apenas a copia local */

    printf("Simulacao para o aluno 1: %.2f + %.2f = %.2f (nao aplicado ainda)\n",
           notaOriginal, bonus, resultado);
}

void aplicarBonus(float *nota, float bonus)
{
    *nota = *nota + bonus;
}