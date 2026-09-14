/*----------------------------------------------------------------------------------*/
/*                                FATEC-Ipiranga                                    */        
/*                            ADS - Estrutura de Dados                              */
/*                             Id da Atividade: N1-4                                */
/*    Objetivo: Estrutura de dados do tipo Fila Dinâmica Encadeada em C             */
/*                                                                                  */
/*    Autor: Renan Cavalcante Nascimento, ADS Noturno                               */
/*                                                                   Data:14/09/2026*/
/*----------------------------------------------------------------------------------*/


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
	printf("=========================\n");

}

/* Remove TODOS os pacientes da fila, liberando a memória de cada um.
 * A fila continua existindo, mas fica vazia.
 */
void esvaziarFila(Fila f){
	NoPtr atual = f->ini;
	NoPtr proximo;

	while (atual != NULL){
		// Guardamos o endereço do próximo ANTES de liberar o atual.
		// Se liberássemos primeiro, perderíamos o caminho para o resto da fila.
		proximo = atual->prox;
		free(atual);
		atual = proximo;
	}

	// Sem pacientes, início e fim voltam a apontar para NULL
	f->ini = NULL;
	f->fim = NULL;

	printf(">> Realizado a liberação de memória da fila.\n");
}

/* Libera a memória do Cabecalho, ou seja, da própria fila.
 * Deve ser chamada depois de esvaziarFila, quando a fila não será mais usada.
 */
void destruirFila(Fila f){
	free (f);
}

int main(){
	// Cria a fila de atendimento do hospital
	Fila filaAtendimento = Criar();
	int opcao, id;
	char nome[50];

	// O menu se repete até o usuário digitar 0 para sair
	do {
		printf("\n--- SISTEMA HOSPITALAR (FATEC IPIRANGA) ---\n");
		printf("1. Chegada de Paciente (Inserir na Fila)\n");
		printf("2. Listar Fila de Pacientes\n");
		printf("3. Atender Paciente (Retirar da Fila)\n");
		printf("4. Consultar Próximo da Fila\n");
		printf("5. Verificar a Quantidade de Pacientes na Fila\n");
		printf("0. Sair\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);

		switch(opcao){
			case 1:
				printf("Informe o ID do paciente: ");
				scanf("%d", &id);

				// O scanf deixa o Enter guardado na memória do teclado.
				// O getchar descarta esse Enter para ele não atrapalhar o fgets abaixo.
				getchar();

				printf("Informe o Nome do paciente: ");
				fgets(nome, sizeof(nome), stdin);

				// O fgets guarda também o Enter digitado.
				// strcspn encontra a posição do "\n" e nós colocamos ali o fim do texto,
				// apagando a quebra de linha do nome.
				nome[strcspn(nome, "\n")] = 0;

				if (inserir(filaAtendimento, id, nome)){
					printf(">> Paciente inserido com sucesso!\n");
				} else {
					printf(">> Erro ao inserir paciente.\n");
				}
				break;
			case 2:
				listarFila(filaAtendimento);
				break;
			case 3:
				// O "!" significa "não": se remover NÃO deu certo, mostramos o erro
				if (!remover(filaAtendimento)) {
					printf(">> Erro ao atender paciente.\n");
				} else {
					printf(">> Primeiro paciente da fila atendido com sucesso.\n");
				}
				break;
			case 4:
				consultar(filaAtendimento);
				break;
			case 5:
				int qtd = contar(filaAtendimento);
				printf(">> Quantidade de pacientes na fila: %d.\n", qtd);
				break;
			case 0:
				// Antes de encerrar, devolvemos toda a memória usada:
				// primeiro os pacientes, depois a própria fila
				esvaziarFila(filaAtendimento);
				destruirFila(filaAtendimento);
				printf(">> Encerrando o sistema...\n");
				break;
			default:
				printf("Opcao invalida!\n");
		}
	} while (opcao != 0);

	return 0;
}