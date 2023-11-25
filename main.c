#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilha.h"
#include "listaCircular.h"
#include "pessoa.h"
#include "conjunto.h"


#define QTD_CANDIDATAS 10
#define QTD_PRETENDENTES 10


int batalha (struct pessoa *p1, struct pessoa *p2) {
	int i, j, k, pontoP1, pontoP2;
	int *vetorP1, *vetorP2;
	// 3 conjuntos, atributos da pessoa 1 e 2, e interseção dos atributos
	struct conjunto *atributoP1, *atributoP2, *intAtri;
	// Recebendo a posição dos atributos
	atributoP1 = decodificaAtributos(p1);
	atributoP2 = decodificaAtributos(p2);
	intAtri = intersecao(atributoP1, atributoP2);

	// Alocando memória para vetor do índice dos atributos
	vetorP1 = malloc(8 * sizeof(int));
	vetorP2 = malloc(8 * sizeof(int));

	// Verificando se os vetores foram alocados corretamente
	if (vetorP1 == NULL || vetorP2 == NULL) 
		return -1;

	// Zerando os elementos do vetor
	zeraVetor(vetorP1);
	zeraVetor(vetorP2);

	// Laços para girar o dado 1d20 para os atributos
	for (i = 0; i < atributoP1->tam; i++) {
		vetorP1[atributoP1->elementos[i]] = (rand() % 21) + 1;
	}
	for (j = 0; j < atributoP2->tam; j++) {
		vetorP2[atributoP2->elementos[j]] = (rand() % 21) + 1;
	}

	// Pontuação de ambas pessoas inicia com 0
	pontoP1 = pontoP2 = 0;
	for (k = 0; k < intAtri->tam; k++) {
		// Se pessoa 1 tiver atributo mais alto que pessoa 2
		if (vetorP1[intAtri->elementos[k]] > vetorP2[intAtri->elementos[k]]) {
			pontoP1++;
		// Se oessia 2 tiver atributo mais alto que pessoa 1
		} else if (vetorP1[intAtri->elementos[k]] > vetorP2[intAtri->elementos[k]]) {
			pontoP2++;
		// Se der empate
		} else {
			pontoP1++;
			pontoP2++;
		}
	}

	// Liberando memória
	destroiConj(atributoP1);
	destroiConj(atributoP2);
	destroiConj(intAtri);
	free(vetorP1);
	free(vetorP2);

	if (pontoP1 == pontoP2)
		return 3;
	else if (pontoP1 > pontoP2)
		return 1;
	return 2; // Se ponto pessoa 1 < pessoa 2
}

int main() {
	srand(time(NULL));

	int i,j,infelicidade, mismatch, match;
	infelicidade = 0;
	mismatch = 0;
	match = 0;

	struct pessoa *pretendentes, *candidatas;

	struct listaC *pretendentesLista;
	struct pilha *candidatasPilha;

	inicializaListaC(pretendentesLista);
	inicializaPilha(candidatasPilha);

	pretendentes = malloc(QTD_PRETENDENTES*sizeof(int));
	candidatas = malloc(QTD_CANDIDATAS*sizeof(int));

	// Bota ponteiros para candidatas no vetor 
	// e seus ids na pilha	
	for(i = 0; i < QTD_CANDIDATAS; i++) {
		candidatas[i] = criaCandidatas(i);
		push(candidatasPilha,i);
	}

	// Bota ponteiros para pretendentes no vetor 
	// e seus ids na lista
	for(i = 0; i < QTD_PRETENDENTES; i++) {
		pretendentes[i] = criaPretendente(i);
		insere(pretendentesLista,i);
	}

	while(!pilhaVazia(candidatasPilha)) {
		struct item *aux, *p1, *p2;
		struct listaC *pretendentesValidos;
		int *pontos, *candidata, resultado, p1pos, p2pos, maisPontosID;

		inicializaListaC(pretendentesValidos);

		pop(candidatasPilha,candidata);

		aux = pretendentesLista->cabeca;

		// acha os pretendentes validos
		do{
			if (intersecaoPessoa(pretendentes[aux->id],candidatas[candidata]) != -1)
				transfereItem(pretendentesValidos,pretendentesLista,aux->id);
			aux = aux->proximo;
		} while(aux != pretendentesLista->cabeca);
		
		aux = NULL;

		if(pretendentesValidos->tamanho < 1){
			infelicidade++;
			continue;
		}

		pontos = malloc(pretendentesValidos->tamanho*sizeof(int));
		
		p1pos = 0;
		p1 = pretendentesValidos->cabeca;
		
		// batalha dos pretendentes validos
		do{
			p2 = p1->proximo;
			p2pos = p1pos + 1;
			while(p2 != pretendentesValidos->cabeca){
				resultado = batalha(p1,p2);

				//empate
				if (resultado = 1) {
					pontos[p1pos] += 3;
				}	
				//p1 ganhou
				else if(resultado = 2) {
					pontos[p2pos] += 3;
				}
				//p2 ganhou
				else {
					pontos[p1pos] += 1;
					pontos[p2pos] += 1;
				}
				p2pos++;
				p2 = p2->proximo;
			}
			p1pos++;
			p1 = p1->proximo;
		} while(p1 != pretendentesValidos->cabeca);
		
		//achar id do ganhador
		for (i = 0; i < pretendentesValidos->tamanho; i++) {
			if ()
		}
		//acha o indice que tem mais pontos
		maisPontosID = 0;
		for(i = 0; i < pretendentesValidos->tamanho; i++){
			if(pontos[maisPontosID] < pontos[i])
				maisPontosID = i;
		}

		//pega o maior da lista
		aux = pretendentesValidos->cabeca;
		while()
	}
	return 0;
}