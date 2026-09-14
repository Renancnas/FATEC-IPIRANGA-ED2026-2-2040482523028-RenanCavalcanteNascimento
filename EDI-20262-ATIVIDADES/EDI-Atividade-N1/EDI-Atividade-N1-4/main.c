#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cada "No" é um paciente da fila. Ele guarda:
 *   - o id do paciente
 *   - o nome do paciente
 *   - um ponteiro "prox", que aponta para o próximo paciente da fila
 * É esse ponteiro "prox" que liga um paciente no outro, como vagões de um trem.
 */
typedef struct no {
	int id;
	char nome[50];
	struct no *prox;
} No;

/* "NoPtr" é só um apelido para "ponteiro de No".
 * Em vez de escrever "No *", podemos escrever "NoPtr" — é a mesma coisa, só mais curto.
 */
typedef No* NoPtr;

/* O "Cabecalho" é a ficha de controle da fila. Ele não guarda paciente nenhum,
 * só guarda dois endereços:
 *   - ini: onde está o PRIMEIRO paciente (o próximo a ser atendido)
 *   - fim: onde está o ÚLTIMO paciente (o que chegou por último)
 * Guardar o "fim" evita ter que percorrer a fila inteira toda vez que alguém chega.
 */
typedef struct {
	NoPtr ini;
	NoPtr fim;
} Cabecalho;

/* "Fila" é um apelido para "ponteiro de Cabecalho".
 * Ou seja: quando passamos uma Fila para uma função, estamos passando o endereço
 * da ficha de controle — e por ela conseguimos chegar em todos os pacientes.
 */
typedef Cabecalho* Fila;

/* Cria uma fila nova (vazia) e devolve o endereço dela. */
Fila Criar() {
	// Pede ao sistema um espaço de memória do tamanho de um Cabecalho
	Fila f = (Fila) malloc(sizeof(Cabecalho));

	// Se a memória foi liberada com sucesso, a fila começa vazia:
	// não há primeiro nem último paciente, então os dois apontam para NULL.
	if (f != NULL){
		f->ini = NULL;
		f->fim = NULL;
	}
	return f;
}

/* Verifica se a fila está vazia.
 * Devolve 1 (verdadeiro) se estiver vazia e 0 (falso) se tiver alguém nela.
 */
int filaVazia(Fila f){
	// A fila é considerada vazia em dois casos:
	// 1) ela nem existe (f == NULL)
	// 2) ela existe, mas não tem primeiro paciente (f->ini == NULL)
	if (f == NULL || f->ini == NULL){
		printf("\n[AVISO] A fila esta vazia.\n");
		return 1;
	} else {
		return 0;
	}
}

/* Coloca um novo paciente no FIM da fila.
 * Devolve 1 se deu certo e 0 se faltou memória.
 */
int inserir(Fila f, int id, const char *nome){
	// Reserva memória para o novo paciente
	NoPtr novo = (NoPtr) malloc(sizeof(No));

	// Se não houver memória disponível, avisa que falhou
	if (novo == NULL) return 0;

	// Preenche os dados do novo paciente
	novo->id = id;

	// strncpy copia o nome com limite de tamanho, para não estourar o vetor.
	// Depois colocamos o '\0' na última posição, que é a marca de "fim do texto" em C.
	strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
	novo->nome[sizeof(novo->nome) - 1] = '\0';

	// Ele entra no fim da fila, então não existe ninguém depois dele
	novo->prox = NULL;

