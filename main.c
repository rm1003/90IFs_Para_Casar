#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pessoa.h"
#include "conjunto.h"

int main (){
    struct pessoa *p1;
    struct pessoa *p2;
    struct conjunto *c1;
    struct conjunto *c2;
    srand(time(NULL));

    p1 = criaPretendentes(1);
    p2 = criaCandidatas(1);
    imprimeAtributos(p1);
    printf("\n");
    imprimeAtributos(p2);
    printf("\n");
    c1 = decodificaAtributos(p1);
    imprimeConj(c1);
    printf("\n");
    c2 = decodificaAtributos(p2);
    imprimeConj(c2);
    printf("\n");
    imprimeAtributos(intersecaoPessoa(p1,p2));
    printf("\n");

    destroiPessoa(p1);
    destroiPessoa(p2);
    destroiConj(c1);
    destroiConj(c2);

    return 0;
}
