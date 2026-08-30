/*--------------------------------------------------------*
 * Disciplina: Estrutura de Dados                          *
 *                                                         *
 * Prof. Verissimo                                         *
 *                                                         *
 *---------------------------------------------------------*
 * Objetivo do Programa: Sistema de atendimento do         *
 * Lava-Rapido Brilho Total                                *
 * Data - 30/08/2026                                       *
 * Autor: Renan Cavalcante Nascimento                      *
 *                                                         *
 *---------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcmp */

/* Valor a partir do qual um servico e considerado premium. */
#define VALOR_PREMIUM 100.0

/* Registro simples: sem ponteiro interno, portanto sem lista encadeada. */
typedef struct {
    char placa[8];
    float valor;
} Veiculo;

void exibirCabecalho(void);
void preencherFrota(Veiculo *frota, int quantidade);
void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade);
float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade);
int buscarVeiculoRecursivo(Veiculo *frota, int indice, int quantidade, char placa[8]);
int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade);

int main(void)
{
    Veiculo *frota;
    int quantidade;
    int posicao;
    char placaBusca[8];

    exibirCabecalho();

    printf("Quantos veiculos serao atendidos hoje? ");
    scanf("%d", &quantidade);

    /* Alocacao dinamica: o tamanho do vetor so e conhecido em tempo de
       execucao, depois da leitura de quantidade. */
    frota = (Veiculo *) malloc(quantidade * sizeof(Veiculo));

    /* Verificacao obrigatoria: se a memoria nao foi concedida, malloc
       devolve NULL e qualquer acesso ao vetor causaria falha grave. */
    if (frota == NULL) {
        printf("Erro: nao foi possivel alocar memoria para a frota.\n");
        return 1;
    }

    preencherFrota(frota, quantidade);

    printf("--- Veiculos atendidos hoje ---\n");
    exibirFrotaRecursivo(frota, 0, quantidade);

    printf("--- Busca recursiva por placa ---\n");
    printf("Placa a ser pesquisada: ");
