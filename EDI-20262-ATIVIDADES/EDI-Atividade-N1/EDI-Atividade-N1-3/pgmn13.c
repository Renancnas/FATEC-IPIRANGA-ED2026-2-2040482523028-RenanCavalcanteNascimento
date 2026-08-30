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
    scanf("%7s", placaBusca);

    posicao = buscarVeiculoRecursivo(frota, 0, quantidade, placaBusca);

    if (posicao == -1) {
        printf("Veiculo nao encontrado na frota.\n");
    } else {
        /* posicao + 1 porque o vetor comeca em 0 e a exibicao para o
           usuario comeca em 1. */
        printf("Veiculo encontrado na posicao %d! Placa: %s | Valor: R$ %.2f\n",
               posicao + 1, (frota + posicao)->placa, (frota + posicao)->valor);
    }

    printf("--- Resumo do dia ---\n");
    printf("Total de veiculos atendidos: %d\n", quantidade);
    printf("Servicos premium (>= R$ %.2f): %d\n",
           VALOR_PREMIUM, contarPremiumRecursivo(frota, 0, quantidade));
    printf("Valor total arrecadado: R$ %.2f\n",
           calcularValorTotalRecursivo(frota, 0, quantidade));

    /* Liberacao unica da memoria e anulacao do ponteiro, para evitar que
       ele continue apontando para uma area que nao pertence mais ao
       programa (ponteiro solto). */
    free(frota);
    frota = NULL;

    printf("Memoria da frota liberada com sucesso. Sistema encerrado.\n");

    return 0;
}

/* Cabecalho fixo do sistema: nao recebe nem devolve dados. */
void exibirCabecalho(void)
{
    printf("=================================\n");
    printf("LAVA-RAPIDO BRILHO TOTAL - FILA DE ATENDIMENTO\n");
    printf("=================================\n");
}

/* Unica funcao do programa autorizada a usar laco de repeticao, e apenas
   para a leitura dos dados. A navegacao usa aritmetica de ponteiros:
   (frota + i) e o endereco do i-esimo veiculo e -> acessa seus campos. */
void preencherFrota(Veiculo *frota, int quantidade)
{
    int i;

    for (i = 0; i < quantidade; i++) {
        printf("Placa do veiculo %d: ", i + 1);
        scanf("%7s", (frota + i)->placa);

        printf("Valor do servico (R$): ");
        scanf("%f", &(frota + i)->valor);
    }
}

/* Exibicao recursiva.
   Caso base: indice == quantidade (o vetor acabou), retorna sem imprimir.
   Passo recursivo: imprime o veiculo atual e chama a si mesma para o
   proximo indice. */
void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade)
{
    if (indice == quantidade) {
        return;
    }

    printf("%d) Placa: %s | Valor: R$ %.2f\n",
           indice + 1, frota[indice].placa, frota[indice].valor);

    exibirFrotaRecursivo(frota, indice + 1, quantidade);
}

/* Soma recursiva dos valores.
   Caso base: indice == quantidade, devolve 0.0f e encerra a cadeia de
   chamadas (sem ele a recursao seria infinita).
   Passo recursivo: devolve o valor do veiculo atual somado ao resultado
   da chamada para o restante do vetor. */
float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade)
{
    if (indice == quantidade) {
        return 0.0f;
    }

    return frota[indice].valor +
           calcularValorTotalRecursivo(frota, indice + 1, quantidade);
}

/* Busca recursiva por placa.
   Caso base 1: o vetor terminou sem encontrar a placa, devolve -1.
   Caso base 2: a placa atual e igual a procurada, devolve o indice.
   Passo recursivo: repassa a busca para a posicao seguinte.
   strcmp devolve 0 quando as duas cadeias de caracteres sao iguais. */
int buscarVeiculoRecursivo(Veiculo *frota, int indice, int quantidade, char placa[8])
{
    if (indice == quantidade) {
        return -1;
    }

    if (strcmp(frota[indice].placa, placa) == 0) {
        return indice;
    }

    return buscarVeiculoRecursivo(frota, indice + 1, quantidade, placa);
}

/* Contagem recursiva de servicos premium.
   Caso base: indice == quantidade, devolve 0.
   Passo recursivo: soma 1 ao resultado do restante do vetor quando o
   valor atual alcanca VALOR_PREMIUM; caso contrario apenas repassa. */
int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade)
{
    if (indice == quantidade) {
        return 0;
    }

    if (frota[indice].valor >= VALOR_PREMIUM) {
        return 1 + contarPremiumRecursivo(frota, indice + 1, quantidade);
    }

    return contarPremiumRecursivo(frota, indice + 1, quantidade);
}