#include <stdio.h>
//Renan Cavalcante Nascimento, Fatec Ipiranga

#define TAMANHO_ESTOQUE 5
#define ESTOQUE_MINIMO 10

int estoque[TAMANHO_ESTOQUE];


void exibirCabecalho(void);
void preencherEstoque(void);
void exibirEstoque(int momento);
float calcularMediaEstoque(void);
void simularReposicao(int quantidadeAtual, int reposicao);
void aplicarResicaoGeral(int reposicao);
void identificarEstoqueCritico(int minimo);

void exibirCabecalho(void) {
    printf("=================================\n");
    printf("SISTEMA DE ESTOQUE - LOJA CONSTRUMAIS\n");
    printf("=================================\n");
}

// Implementação da função sem parâmetros com preenchimento via ponteiro e utiliza laço for para ler as quantidades.
void preencherEstoque(void) {
    int *p = estoque;
    int qtd_lida;
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Quantidade do produto %d: ", i + 1);
        scanf("%d", &qtd_lida);
        *(p + i) = qtd_lida; 
    }
}

void exibirEstoque(int momento) {
    int *p = estoque;
    
    if (momento == 0) {
        printf("-- Estoque atual (antes da reposicao) --\n");
    } else {
        printf("-- Estoque final (apos reposicao) --\n");
    }
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Produto %d: %d unidades\n", i + 1, *(p + i));
    }
}

float calcularMediaEstoque(void) {
    int *p = estoque;
    int soma_total = 0;
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        soma_total = soma_total + *(p + i); // p + i é a localização física do endereço, já *(p + i) é o valor armazenado neste endereço.
    }
    
    return (float)soma_total / TAMANHO_ESTOQUE;
}

void simularReposicao(int quantidadeAtual, int reposicao) {
    int resultado_simulado = quantidadeAtual + reposicao;
    printf("Simulacao para o produto 1: %d + %d = %d (nao aplicado ainda)\n", quantidadeAtual, reposicao, resultado_simulado);
}

void aplicarReposicaoGeral(int reposicao) {
    int *p = estoque;
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        *(p + i) = *(p + i) + reposicao;
    }
}

void identificarEstoqueCritico(int minimo) {
    int *p = estoque;
    
    printf("-- Analise de estoque critico (minimo = %d unidades) --\n", minimo);
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        if (*(p + i) < minimo) {
            printf("Produto %d esta em nivel critico: %d unidades (abaixo do minimo)\n", i + 1, *(p + i));
        }
    }
}

int main(void) {
    int reposicao;
    int *ptr_base = estoque; 
    
    
    exibirCabecalho();
    
    
    preencherEstoque();
    
    printf("Quantidade de reposicao a aplicar: ");
    scanf("%d", &reposicao);
    
    exibirEstoque(0);
    
    printf("-- Simulacao de reposicao (passagem por valor) --\n");
    simularReposicao(*ptr_base, reposicao);
    printf("Quantidade do produto 1 apos a simulacao (inalterada): %d\n", *ptr_base);
    
    printf("-- Aplicacao real da reposicao (ponteiro interno ao vetor global) --\n");
    aplicarReposicaoGeral(reposicao);
    printf("Reposicao de %d unidades aplicada a todos os produtos do estoque.\n", reposicao);
    
    exibirEstoque(1);
    
    
    printf("-- Media geral do estoque --\n");
    printf("Media final: %.2f unidades\n", calcularMediaEstoque());
    
    identificarEstoqueCritico(ESTOQUE_MINIMO);
    
    return 0;
}