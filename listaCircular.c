#include "listaCircular.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// aloca um item, e inicializa componentes
struct item *criaItem(int id){
    struct item* novoItem = malloc(sizeof(struct item));

    //se malloc funciona, inicia o novoItem
    if (novoItem != NULL){
        novoItem->id = id;
        novoItem->proximo = novoItem;
        novoItem->anterior = novoItem;
    }
    return novoItem;
}

struct listaC* inicializaListaC(){
    struct listaC* l = malloc(sizeof(struct listaC));

    // caso ponteiro valido, inicializa ele
    if (l != NULL){
        l->cabeca = NULL;
        l->tamanho = 0;
    }
    return l;
}

int listaVazia(struct listaC *l){
    return (l->tamanho == 0);
}

// insere um elemento na cabeca
void insere(struct listaC* l, int id){
    struct item* novo = criaItem(id);
    
    if(!listaVazia(l)){
        novo->proximo = l->cabeca ;
        novo->anterior = l->cabeca->anterior;
        l->cabeca->anterior->proximo = novo;
        l->cabeca->anterior = novo;
    }

    l->tamanho++;
    l->cabeca = novo;

}

struct item* extrairItem(struct listaC* l, int id, int *erro){
    struct item* aux = l->cabeca;
    int cont = 0;
    
    // acha elemento com id
    while (cont < l->tamanho && aux->id != id){
        aux = aux->proximo;
        cont++;
    }

    // não existe elemento com esse id 
    if (cont >= l->tamanho){
        *erro = 1;
        return NULL;
    }
    
    // caso unitario
    if (l->tamanho == 1)
        l->cabeca = NULL;

    // caso da cabeca
    if (aux == l->cabeca)
        l->cabeca = aux->proximo;

    // ajeita ponteiros dos adjacentes
    aux->anterior->proximo = aux->proximo;
    aux->proximo->anterior = aux->anterior;

    aux->proximo = aux;
    aux->anterior = aux;

    *erro = 0;
    l->tamanho = l->tamanho - 1;
    return aux;
}

void transfereItem(struct listaC* l1, struct listaC* l2, int id){
    int erro = 0;
    struct item* aux = extrairItem(l1, id, &erro);
    if (!(erro))
        insere(l2,id);

    return;
}


void destroiItem(struct item* dItem){

    free(dItem);
    dItem = NULL;
    
    return;
}

void removeCabeca(struct listaC* l){
    if(listaVazia(l))
        return;
    
    int erro = 0;
    struct item* rm = extrairItem(l,l->cabeca->id,&erro);
    destroiItem(rm);
    rm = NULL;
    return;
}

void imprimelistaC(struct listaC* l){
    struct item* aux = l->cabeca;

    for (int i = 0; i < l->tamanho; i++){
        printf("%d ",aux->id);
        aux = aux->proximo;
    }
    printf("\n");
    return;
}

void destroiListaC(struct listaC* l){
    while(!listaVazia(l)){
        removeCabeca(l);
    }
    free(l);
    l = NULL;

    return;
}

