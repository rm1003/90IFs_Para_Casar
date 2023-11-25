#include <stdbool.h>

#ifndef ITEM
#define ITEM
struct item {
	int valor;
	struct item *proximo;
};
#endif

struct pilha {
	struct item *topo;
	int tamanho;
};

// Recebe inteiro, aloca memoria para um item, atribui o valor e retorna o item
#ifndef CRIA_ITEM
#define CRIA_ITEM
struct item *criaItem(int valor);
#endif

// Aloca memoria para uma pilha, zera o tamanho e atribui o ponteiros topo para NULO
struct pilha *inicializaPilha();

// Retorna true para pilha vazia e false para pilha com ao menos um item
bool pilhaVazia(struct pilha *p);

// Dada uma pilha P, insere item com valor x chamando criaItem no topo da pilha; 
// retorna 1 se x foi inserido com sucesso, 0 se x não foi inserido.
int push(struct pilha *p, int x);

// Dada uma pilha P, remove elemento do inicio, caso a pilha não esteja vazia; 
// retorna 1 se o elemento foi removido ou 0 se o elemento não foi removido.
// O ponteiro para inteiro 'dado' retorna o valor do topo...
int pop(struct pilha *p, int *dado);

// Imprime o topo da pilha
void imprimeTopo(struct pilha *p);

// Retorna o tamanho da pilha
int tamanhoPilha(struct pilha *p);

// Destroi cada item da pilha (se não vazia) e destroi a pilha
void destroiPilha(struct pilha *p);
