#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pessoa.h"

#define TAM 8
#define ATRIBUTOSP 3
#define ATRIBUTOSC 2


void geraAtributos(struct pessoa *p, int tam) {

    int indice;
    int maxAtributos = 0;
    printf("%d\n", tam);

    for (int i = 0; i < tam; i++) {
        p->atributos[i] = 0;
    }
    
    while (maxAtributos < p->qtdAtributos) {
        indice = rand() % 8;
        printf("%d\n", maxAtributos);
        if (p->atributos[indice] == 0) {
            p->atributos[indice] = 1;
            maxAtributos++;
        }
    }
    return;
}

struct pessoa *criaPretendentes(int id) {
    struct pessoa *novaPretendente = malloc(sizeof(struct pessoa));

    if (novaPretendente == NULL)
        return NULL;

    novaPretendente->id = id;
    novaPretendente->atributos = malloc(TAM * sizeof(int));
    novaPretendente->qtdAtributos = ATRIBUTOSP;
    geraAtributos(novaPretendente, ATRIBUTOSP);
    return novaPretendente;
}

struct pessoa *criaCandidatas(int id) {
    struct pessoa *novaCandidata = malloc(sizeof(struct pessoa));

    if (novaCandidata == NULL)
        return NULL;
    
    novaCandidata->id = id;
    novaCandidata->atributos = malloc(TAM * sizeof(int));
    novaCandidata->qtdAtributos = ATRIBUTOSC;
    geraAtributos(novaCandidata, ATRIBUTOSC);
    return novaCandidata;
}

/*
struct conjunto *decodificaAtributos(struct pessoa *p) {

}

struct pessoa *intersecao(struct pessoa *p1, struct pessoa *p2) {

}

void destroiPessoa(struct pessoa *p) {

}
*/

void imprimeAtributos(struct pessoa *p) {
    for (int i = 0; i < TAM; i++) {
        printf("%d ", p->atributos[i]);
    }
    printf("\n");
    return;
}

int main (){
    struct pessoa *p1;
    struct pessoa *p2;
    srand(time(NULL));

    p1 = criaPretendentes(1);
    p2 = criaCandidatas(1);
    imprimeAtributos(p1);
    printf("\n");
    imprimeAtributos(p2);

    return 0;
}
