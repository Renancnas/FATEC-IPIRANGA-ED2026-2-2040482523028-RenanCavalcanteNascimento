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

	if (f->ini == NULL){
		// Fila vazia: esse paciente é o primeiro de todos
		f->ini = novo;
	} else {
		// Fila com gente: quem era o último agora aponta para o novo,
		// formando mais um elo da corrente
		f->fim->prox = novo;
	}

	// Em qualquer um dos dois casos, o novo paciente passa a ser o último da fila
	f->fim = novo;
	return 1;
}

/* Atende (remove) o primeiro paciente da fila.
 * Devolve 1 se atendeu alguém e 0 se a fila estava vazia.
 */
int remover(Fila f){
	// Não dá para remover de uma fila vazia
	if (filaVazia(f)) return 0;

	// "atual" guarda o primeiro paciente, para não perdermos o endereço dele
	NoPtr atual = f->ini;

	// O início da fila passa a ser o paciente seguinte
	f->ini = atual->prox;

	// Mostra na tela quem está sendo atendido
	printf(">> Paciente em atendimento:\n");
	printf(">> ID: %d - Nome: %s\n", atual->id, atual->nome);

	// Como ele saiu da fila, devolvemos sua memória ao sistema
	free(atual);
	return 1;
}

/* Mostra quem é o primeiro da fila, SEM removê-lo. */
void consultar(Fila f){
	if (filaVazia(f)){
		printf(">> Não foi possível consultar o próximo da fila.\n");
		return;
	}

	// Como só queremos "espiar", lemos os dados direto de f->ini e não mexemos na fila
	printf(">> Próximo paciente da fila:\n");
	printf(">> ID: %d - Nome: %s\n", f->ini->id, f->ini->nome);
}

/* Conta quantos pacientes existem na fila. */
int contar(Fila f){
	if (filaVazia(f)){
		return 0;
	} else {
		int i = 0;

		// Começamos no primeiro paciente
		NoPtr atual = f->ini;

		// Andamos de paciente em paciente até chegar no NULL (fim da fila),
		// somando 1 no contador a cada passo
		while(atual != NULL){
			i++;
			atual = atual->prox;
		}
		return i;
	}
}

/* Mostra na tela todos os pacientes da fila, na ordem de chegada. */
void listarFila(Fila f){
	// Se não há ninguém, não há o que listar
	if (filaVazia(f)) return;

	// "atual" é um ponteiro auxiliar que vai caminhar pela fila.
	// Usamos ele para não perder o f->ini original.
	NoPtr atual = f->ini;
	printf("\n=== FILA DE PACIENTES ===\n");

	// Enquanto não chegarmos no fim da fila (NULL), imprimimos o paciente atual
	// e avançamos para o próximo
	while (atual != NULL){
		printf("ID: %d - Nome: %s\n", atual->id, atual->nome);
		atual = atual->prox;
	}