#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pessoa.h"
#include "conjunto.h"

// Função para gerar os atributos
void geraAtributos(struct pessoa *p) {
    int indice; // indice da posição do atributo
    int maxAtributos = 0; // controlador da quatidade de atributos

    // Laço para zerar todas posições do vetor
    for (int i = 0; i < TAM; i++) {
        p->atributos[i] = 0;
    }
    
    // Laço para colocar a quantidade necessário de atributos
    while (maxAtributos < (p->qtdAtributos)) {
        // Gerando indice "aleatoriamente"
        indice = (rand() % 8);
        // Condição para verificar se no indice já possui ou não o atributo
        if (p->atributos[indice] == 0) {
            p->atributos[indice] = 1;
            maxAtributos++; // Quantidade de atributos + 1
        }
    }
    return;
}

// Função para criar pessoa pretendente e devolve o pretendente
struct pessoa *criaPretendentes(int identificador) {
    // Aloca memória para nova pretendente
    struct pessoa *novaPretendente = malloc(sizeof(struct pessoa));
    // Testa se a memória foi alocada corretamente
    if (novaPretendente == NULL)
        return NULL;

    // Pretendente recebe o seu identificador
    novaPretendente->id = identificador;

    // Aloca memória para os atributos
    novaPretendente->atributos = malloc(TAM * sizeof(int));
    // Testa se a memória foi alocada corretamente
    if (novaPretendente->atributos == NULL)
        return NULL;

    // Quantidade de atributos = 3
    novaPretendente->qtdAtributos = ATRIBUTOSP;
    geraAtributos(novaPretendente);
    return novaPretendente;
}

// Função para criar pessoa candidata e devolve a candidata
struct pessoa *criaCandidatas(int id) {
    // Aloca memória para nova candidata
    struct pessoa *novaCandidata = malloc(sizeof(struct pessoa));

    // Testa se a memória foi alocada corretamente
    if (novaCandidata == NULL)
        return NULL;
    
    // Candidata recebe o seu identificador
    novaCandidata->id = id;
    // Aloca memória para os atributos
    novaCandidata->atributos = malloc(TAM * sizeof(int));

    // Testa se a memória foi alocada corretamente
    if (novaCandidata->atributos == NULL)
        return NULL;

    // Quantidade de atributos = 2
    novaCandidata->qtdAtributos = ATRIBUTOSC;
    geraAtributos(novaCandidata);
    return novaCandidata;
}

// Função para leitura dos atributos de cada pessoa
struct conjunto *decodificaAtributos(struct pessoa *p) {
    // Chama a função criaConj() para gerar o novo conjunto
    struct conjunto *novoConjPessoa = criaConj();

    // Laço para colocar a posição dos atributos no conjunto
    for (int i = 0; i < TAM; i++) {
        if (p->atributos[i] == 1) {
            // Função insereConj() para inserir o indice
            insereConj(novoConjPessoa, i);
        }
    }

    // Devolve o conjunto dos atributos da pessoa
    return novoConjPessoa;
}

// Função que devolve o pretendente com os atributos desejadas
int intersecaoPessoa(struct pessoa *p1, struct pessoa *p2) {
    // Armazenando os atributos no conjunto pretendentes
    struct conjunto *pretendente = decodificaAtributos(p1);

    // Armazenando os atributos no conjunto candidata
    struct conjunto *candidata = decodificaAtributos(p2);

    // Faz a interseção dos conjuntos pretendente e candidata
    struct conjunto *conjIntersecao = intersecao(pretendente, candidata);

    int quantidade = conjIntersecao->tam;
    destroiConj(conjIntersecao);
    destroiConj(pretendente);
    destroiConj(candidata);

    if (quantidade == 2)
        return p1->id;
    return 0;
}

// Função para liberar memória alocada
void destroiPessoa(struct pessoa *p) {
    free(p->atributos);
    free(p);
}

// Função para imprimir os atributos da pessoa
void imprimeAtributos(struct pessoa *p) {
    // Testa se a p é nulo
    if (p == NULL) {
        return;
    }
    // Laço para imprimir os atributos
    for (int i = 0; i < TAM; i++) {
        printf("%d ", p->atributos[i]);
    }
    printf("\n");
    return;
}
