#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

bool pilhaVazia(struct pilha* p){
    if (p->topo == NULL)
        return 1;
    return 0;
}

struct item* criarItem(int valor){
    struct item* i = malloc(sizeof(struct item));
    if (i == NULL)
        return NULL;
    i->valor = valor;
    i->proximo = NULL;
    return i;
}

struct pilha* inicializaPilha(){
    struct pilha* p = malloc(sizeof(struct pilha));
    if (p == NULL)
        return NULL;
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

int push(struct pilha* p,int a){
    struct item* novo = criarItem(a);
    
    if (novo == NULL)
        return 0;

    novo->proximo = p->topo;
    p->topo = novo;
    
    (p->tamanho)++;
    
    return 1;
    
}

int pop(struct pilha* p,int *dado){
    if (pilhaVazia(p))
        return 0;
    
    struct item* aux = p->topo;
    
    if (dado != NULL)
        *dado = p->topo->valor; 
    p->topo = p->topo->proximo;
    
    (p->tamanho)--;
    
    free(aux);
    aux = NULL;
    return 1;
}

void imprimeTopo(struct pilha *p){
    printf("%d\n", p->topo->valor);
    return;
}

void destroiPilha(struct pilha* p){
    while(!pilhaVazia(p))
        pop(p,NULL);
    free(p);
    p = NULL;
}


