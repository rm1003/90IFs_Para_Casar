// ARQUIVO auxiliar.c
#include <stdio.h>
#include <stdlib.h>
#include "auxiliar.h"

// Funcao para achar o indice que o elemento deve ficar
int buscaPosBinaria(int *elementos, int inicio, int fim, int valor) {
    int m;

    // Caso base da recursao
    if (inicio > fim)
        return inicio - 1;

    // m = meio do vetor
    m = (inicio + fim) / 2;

    // Condicao caso o elemento esta exatamente no meio
    if (elementos[m] == valor)
        return m;

    // Condicao para caso o valor eh maior que o elemento do meio
    if (elementos[m] < valor)
        return buscaPosBinaria(elementos, m + 1, fim, valor);
    return buscaPosBinaria(elementos, inicio, m - 1, valor);
}

// Funcao para procurar se o elemento estah no vetor ou nao
int buscaBinaria(int *elementos, int inicio, int fim, int valor) {
    int meio;

    // Caso base da recursao
    if (inicio > fim) {
        return 0;
    }

    // meio do vetor
    meio = (inicio + fim) / 2;

    // Condicao para caso o valor esta exatamente no meio
    if (elementos[meio] == valor) {
        return 1;
    }

    // Condicao para caso o valor eh maior que o elemento do meio
    if (elementos[meio] > valor)
        return buscaBinaria(elementos, inicio, meio - 1, valor);
    return buscaBinaria(elementos, meio + 1, fim, valor);
}
