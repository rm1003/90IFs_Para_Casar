// ARQUIVO conjunto.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "conjunto.h"
#include "auxiliar.h"

// Funcao para criar o conjunto
struct conjunto *criaConj() {
    struct conjunto *novoConj;
    // Aloca memoria para o conjunto
    novoConj = malloc(sizeof(struct conjunto));
    // Aloca memoria para os elementos do conjunto
    novoConj->elementos = malloc(2 * sizeof(int));
    novoConj->tam = 0;
    novoConj->maxTam = 2;
    return novoConj;
}

// Funcao para verificar se o conjunto eh vazio ou nao
bool conjVazio(struct conjunto *c) {
    if (c->tam == 0)
        return 1;
    return 0;
}

// Funcao para destruir o conjunto criado
void destroiConj(struct conjunto *c) {
    free(c->elementos);
    free(c);
    return;
}

// Devolve o tamanho do conjunto
int tamConj(struct conjunto *c) {
    return c->tam;
}

// Verifica se o elemento x pertence ao conjunto C
bool pertenceConj(struct conjunto *c, int x) {
    // Condicao para verificar se o conjunto estah vazia ou nao
    if (conjVazio(c)) {
        return 0;
    } else {
        /* Usando funcao buscaBinaria da biblioteca auxiliar.h para verificar
         * se o elemento pertence ou nao ao conjunto */
        if (buscaBinaria(c->elementos, 0,  c->tam - 1, x))
            return 1;
    }
    return 0;
}

// Funcao para inserir elemento no conjunto
void insereConj(struct conjunto *c, int x) {
    int *aux, i;
    // Condicao para verificar se x pertence ou nao no conjunto
    if (pertenceConj(c, x)) {
        return;
    } else {
        // Condicao para verificar se o tamanho maximo foi atingido ou nao
        if (c->tam >= c->maxTam) {
            // Realoca para aumentar o tamanho maximo do conjunto
            aux = realloc(c->elementos, (c->maxTam * 2)* sizeof(int));
            // Condicao para verificar se o conjunto foi realocado ou nao
            if (aux == NULL) {
                return;
            }
            c->elementos = aux;
            c->maxTam *= 2;
        }

        // Loop para colocar todos elementos maiores que o x uma casa para cima do conjunto
        for (i = c->tam; i > 0 && x < c->elementos[i - 1]; i--) {
            c->elementos[i] = c->elementos[i - 1];
        }
        // Insere o elemento no lugar correto
        c->elementos[i] = x;
        c->tam++;
    }
    return;
}

// Funcao para remover um elemento do conjunto
void removeConj(struct conjunto *c, int x) {
    int i, *aux;
    // Condicao para verificar se o conjunto estah vazia ou nao 
    if (conjVazio(c)) {
        printf("O conjunto esta vazia.\n");
        return;
    }

    // Condicao para verificar se o elemento pertence ou nao no conjunto
    if (pertenceConj(c, x)) {
        /* Loop inicia em i recebe o indice da posicao que o elemento esta, usando
         * a funcao buscaPosBinaria da biblioteca auxiliar.h e termina no tamanho - 1 */
        for (i = buscaPosBinaria(c->elementos, 0, c->tam, x); i < c->tam - 1; i++) {
            c->elementos[i] = c->elementos[i + 1];
        }
        c->tam--;

        /* Condicao para verificar se o tamanho do conjunto e menor que o tamanho
         * maximo do conjunto para realocar para o tamanho maximo correto */
        if (c->tam < (c->maxTam / 2)) {
            // Realocando para diminuir o tamanho maximo do conjunto
            aux = realloc(c->elementos, ((c->maxTam / 2) * sizeof(int)));
            // Condicao para verificar se o conjunto foi realocado ou nao
            if (aux == NULL) {
                return;
            }
            c->elementos = aux;
            c->maxTam /= 2;
        }
    } else {
        printf("O elemento nao pertence ao conjunto.\n");
    }
    return;
}

// Retorna conjunto de tamanho alocado máximo tamConj(c1) + tamConj(c2)
struct conjunto *uniao(struct conjunto *c1, struct conjunto *c2) {
    struct conjunto *cUniao;
    int i, j;

    // Criando um conjunto novo
    cUniao = criaConj();

    // Loops para inserir elementos do conjunto 1 e 2 chamando a funcao insereConj
    for (i = 0; i < c1->tam; i++) {
        insereConj(cUniao, c1->elementos[i]);
    }

    for (j = 0; j < c2->tam; j++) {
        insereConj(cUniao, c2->elementos[j]);
    }

    // Devolve o conjunto uniao
    return cUniao;
}

// Devolve conjunto intersecao entre os dois conjuntos, c1 e c2
struct conjunto *intersecao(struct conjunto *c1, struct conjunto *c2) {
    struct conjunto *cIntersecao;
    int i;

    // Criando um conjunto novo
    cIntersecao = criaConj();

    // Loop para inserir os elementos no conjunto intersecao
    for (i = 0; i < c1->tam; i++) {
        // Condicao para verificar se o elemento do conjunto 2 pertence ou nao no conjunto 1
        if (pertenceConj(c2, c1->elementos[i])) {
            insereConj(cIntersecao, c1->elementos[i]);
        }
    }

    // Devolve o conjunto intesecao
    return cIntersecao;
}

// Funcao para imprimir o conjunto
void imprimeConj(struct conjunto *c) {
    int i;
    // Verificando se o conjunto esta vazia ou nao
    if (conjVazio(c)) {
        printf("O conjunto esta vazia.\n");
        return;
    } else {
        // Loop para imprimir os elementos
        for (i = 0; i < c->tam; i++ ) {
            printf("%d ", c->elementos[i]);
        }
    }
    return;
}
