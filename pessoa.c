// Arquivo pessoa.c
#include <stdio.h>
#include <stdlib.h>
#include "pessoa.h"
#include "conjunto.h"

// Função para zerar os elementos do vetor
void zeraVetor (int *vetor, int tam) {
    for (int i = 0; i < tam; i++) {
        vetor[i] = 0;
    }
    return;
}

// Função para gerar os atributos
void geraAtributos(struct pessoa *p) {
    int indice; // indice da posição do atributo
    int maxAtributos = 0; // controlador da quatidade de atributos

    zeraVetor(p->atributos, TAM);
    // Laço para colocar a quantidade necessário de atributos
    while (maxAtributos < (p->qtdAtributos)) {
        // Gerando indice "aleatoriamente"
        indice = rand() % TAM;
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
struct pessoa *criaCandidatas(int identificador) {
    // Aloca memória para nova candidata
    struct pessoa *novaCandidata = malloc(sizeof(struct pessoa));

    // Testa se a memória foi alocada corretamente
    if (novaCandidata == NULL)
        return NULL;
    
    // Candidata recebe o seu identificador
    novaCandidata->id = identificador;
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

    // Verificando se ambos são nulos ou não
    if (pretendente == NULL || candidata == NULL)
        return -1;

    // Faz a interseção dos conjuntos pretendente e candidata
    struct conjunto *conjIntersecao = intersecao(pretendente, candidata);

    // Verifica se a interseção é válida
    if (conjIntersecao == NULL)
        return -1;

    // Variável quantidade recebe o tamanho do conjunto interseção
    int quantidade = conjIntersecao->tam;
    // Liberando memória dos conjuntos criados
    destroiConj(conjIntersecao);
    destroiConj(pretendente);
    destroiConj(candidata);

    // Condição se a quantidade de atributos igual a 2 devolve o id da pessoa
    if (quantidade >= 2)
        return p1->id;
    return -1;
}

// Função para liberar memória alocada
void destroiPessoa(struct pessoa *p) {
    free(p->atributos);
    free(p);
    return;
}

// Função para imprimir os atributos da pessoa
void imprimeAtributos(struct pessoa *p) {
    // Testa se a p é nulo
    if (p == NULL)
        return;

    // aux = auxiliar para armazenar os atributos
    struct conjunto *aux = decodificaAtributos(p);

    // Imprime o id da pessoa
    printf("%d \n", p->id);

    // Laço para imprimir os atributos
    for (int i = 0; i < aux->tam; i++) {
        switch (aux->elementos[i]) {
            case 0:
                printf("Usa Linux.\n");
                break;
            case 1:
                printf("Computeiro.\n");
                break;
            case 2:
                printf("Shape.\n");
                break;
            case 3:
                printf("Rico.\n");
                break;
            case 4:
                printf("Alto.\n");
                break;
            case 5:
                printf("Não Calvo.\n");
                break;
            case 6:
                printf("Usa o bogosort para ordenar.\n");
                break;
            case 7:
                printf("Gosta de Anime.\n");
                break;
        }
    }
    destroiConj(aux);
    return;
}
