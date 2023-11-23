#include <stdbool.h>

struct conjunto {
    int tam;
    int maxTam;
    int *elementos;
};

// Cria o conjunto
struct conjunto *criaConj();

// Destroi o conjunto criado
void destroiConj(struct conjunto *c);

// Retorna o tamanho do conjunto
int tamConj(struct conjunto *c);

// Verifica se o elemento x pertence ao conjunto C
bool pertenceConj(struct conjunto *c, int x);

// Insere o elemento x ao conjunto C, caso x não exista em C
void insereConj(struct conjunto *c, int x);

// Remove o elemento x do conjunto C
void removeConj(struct conjunto *c, int x);

// Retorna conjunto de tamanho alocado máximo tamConj(c1) + tamConj(c2)
struct conjunto *uniao(struct conjunto *c1, struct conjunto *c2);

// Devolve o conjunto intersecao entre os dois conjunto c1 e c2
struct conjunto *intersecao(struct conjunto *c1, struct conjunto *c2);

// Funcao para imprimir o conjunto
void imprimeConj(struct conjunto *c);

// Verifica se o conjunto está vazia
bool conjVazio(struct conjunto *c);
