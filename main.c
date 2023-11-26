// Arquivo main.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilha.h"
#include "listaCircular.h"
#include "pessoa.h"
#include "conjunto.h"


#define QTD_CANDIDATAS 100
#define QTD_PRETENDENTES 100


int batalha (struct pessoa *p1, struct pessoa *p2) {
	int i, j, pontoP1, pontoP2, tamIntersecao;
	int *vetorP1, *vetorP2;

	// 3 conjuntos, atributos da pessoa 1 e 2, e interseção dos atributos
	struct conjunto *atributoP1, *atributoP2, *intAtri;

	// Recebendo a posição dos atributos
	atributoP1 = decodificaAtributos(p1);
	atributoP2 = decodificaAtributos(p2);
	intAtri = intersecao(atributoP1, atributoP2);
	tamIntersecao = intAtri->tam;

	// Alocando memória para vetor do índice dos atributos
	vetorP1 = malloc(tamIntersecao * sizeof(int));
	vetorP2 = malloc(tamIntersecao * sizeof(int));

	// Verificando se os vetores foram alocados corretamente
	if (vetorP1 == NULL || vetorP2 == NULL)  {
		free(vetorP1);
		free(vetorP2);
		return -1;
	}

	// Zerando os elementos do vetor
	zeraVetor(vetorP1, tamIntersecao);
	zeraVetor(vetorP2, tamIntersecao);

	// Laços para girar o dado 1d20 para os atributos
	for (i = 0; i < intAtri->tam; i++) {
		vetorP1[i] = (rand() % 20) + 1;
		vetorP2[i] = (rand() % 20) + 1;
	}

	// Pontuação de ambas pessoas inicia com 0
	pontoP1 = 0;
	pontoP2 = 0;
	for (j = 0; j < tamIntersecao; j++) {
		// Se pessoa 1 tiver atributo mais alto que pessoa 2
		if (vetorP1[j] > vetorP2[j]) {
			pontoP1++;
		// Se oessia 2 tiver atributo mais alto que pessoa 1
		} else if (vetorP1[j] < vetorP2[j]) {
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

	// Caso interseção deu 0 elementos.
	if (tamIntersecao == 0)
		return -1;

	if (pontoP1 > pontoP2)
		return 1;
	if (pontoP1 < pontoP2)
		return 2;
	return 3;
}

int main() {
	srand(time(NULL));
	
	int i, infelicidade, mismatch, match, erro;
	// Ponteiro para ponteiro para struct pessoa
	struct pessoa **vetorCandidatas, **vetorPretendentes;
	struct listaC *pretendentesValidos = inicializaListaC();
	struct listaC *pretendentesLista = inicializaListaC();
	struct pilha *candidatasPilha = inicializaPilha();

	infelicidade = 0;
	mismatch = 0;
	match = 0;

	vetorPretendentes = malloc(QTD_PRETENDENTES * sizeof(struct pessoa*));
	vetorCandidatas = malloc(QTD_CANDIDATAS * sizeof(struct pessoa*));
	
	// Bota ponteiros para candidatas no vetor 
	// e seus ids na pilha	
	for(i = 0; i < QTD_CANDIDATAS; i++) {
		vetorCandidatas[i] = criaCandidatas(i);
		push(candidatasPilha,i);
	}

	// Bota ponteiros para pretendentes no vetor 
	// e seus ids na lista
	for(i = 0; i < QTD_PRETENDENTES; i++) {
		vetorPretendentes[i] = criaPretendentes(i);
		insere(pretendentesLista,i);
	}

	while(!pilhaVazia(candidatasPilha)) {
		int *pontos;
		struct item *aux, *p1, *p2, *pretendente;
		int candidata, p1pos, p2pos, maisPontosID;

		// Retiro a candidata da pilha
		pop(candidatasPilha, &candidata);

		// Iterador da lista
		aux = pretendentesLista->cabeca;
		int taman = pretendentesLista->tamanho;
		for (i = 0; i < taman; i++) {
			if (intersecaoPessoa(vetorPretendentes[aux->id],vetorCandidatas[candidata]) != -1) {
				// Coloca pretendente na lista de pretendentes válidos
				transfereItem(pretendentesLista, pretendentesValidos, aux->id);
				if (aux != pretendentesLista->cabeca)
					aux = aux->proximo;
			}
		}

		// Acha os pretendentes validos
		/*
		do {
			// Condição para interseção dos atributos
			if (intersecaoPessoa(vetorPretendentes[aux->id],vetorCandidatas[candidata]) != -1) {
				printf("ALOALO\n");
				// Coloca pretendente na lista de pretendentes válidos
				transfereItem(pretendentesLista, pretendentesValidos, aux->anterior->id);

			}
			aux = aux->proximo;
		} while(aux != pretendentesLista->cabeca);
		*/
		
		aux = NULL;

		// Se não tiver nenhum pretendentes
		if(pretendentesValidos->tamanho < 1){
			infelicidade++;
			continue; // Pula o laço
		}
		
		// p1pos = posição da pessoa 1
		// p2pos = posição da pessoa 2
		pontos = calloc(pretendentesValidos->tamanho, sizeof(int));
		p1pos = 0;
		p1 = pretendentesValidos->cabeca;
		
		// Batalha dos pretendentes validos
		do {
			p2 = p1->proximo;
			p2pos = p1pos + 1;

			while(p2 != pretendentesValidos->cabeca) {
				switch (batalha(vetorPretendentes[p1->id],vetorPretendentes[p2->id])) {
					case 1:
						// Pessoa 1 ganha
						pontos[p1pos] += 3;
						break;
					case 2:
						// Pessoa 2 ganha
						pontos[p2pos] += 3;
						break;
					case 3:
						// Empate
						pontos[p1pos] += 1;
						pontos[p2pos] += 1;
						break;
				}
				p2pos++;
				p2 = p2->proximo;
			}
			p1pos++;
			p1 = p1->proximo;
		} while(p1->proximo != pretendentesValidos->cabeca);
		
		// Acha o indice que tem mais pontos
		maisPontosID = 0;
		for(i = 0; i < pretendentesValidos->tamanho; i++){
			if(pontos[maisPontosID] < pontos[i])
				maisPontosID = i;
		}

		// Devolve os perdedores para a lista principal

		if (pretendentesValidos->tamanho > 1) {
			aux = pretendentesValidos->cabeca;
			for (i = 0; i < pretendentesValidos->tamanho; i++) {
				// Todos pretendentes menos o que possui maior pontuação
				if (i != maisPontosID)
					transfereItem(pretendentesValidos, pretendentesLista, aux->id);
				aux = aux->proximo;
			}
		}

		// pontos[0] = pontos pretendentes, pontos[1] = pontos candidata
		pontos = realloc(pontos, (2 * sizeof(int)));
		zeraVetor(pontos, 2);
		// Identificador do pretendente
		pretendente = extrairItem(pretendentesValidos, pretendentesValidos->cabeca->id, &erro);

		// Laço principal 90Ifs
		for (i = 0; i < 90; i++) {
			switch (batalha(vetorPretendentes[pretendente->id], vetorCandidatas[candidata])) {
			case 1:
				// Pretendente ganha
				pontos[0] += 3;
				break;
			case 2:
				// Candidata ganha
				pontos[1] += 3;
				break;
			case 3:
				// Empate
				pontos[0] += 1;
				pontos[1] += 1;
				break;
			}
		}

		// Pretendente ganha mismatch + 1
		if (pontos[0] >= pontos[1]) {
			mismatch++;
			// Insere pretendente na lista novamente
			insere(pretendentesLista, pretendente->id);
			printf("Candidata %d deu errado com Pretendente %d\n", candidata, pretendente->id);
		} else {
			// Candidata ganha match + 1
			printf("Candidata %d deu certo com Pretendente %d\n", candidata, pretendente->id);
			match++;
		}
		free(pontos);
		destroiItem(pretendente);
		free(aux);
		pontos = NULL;
	}

	printf(">> Infelizes: %d <<\n", infelicidade);
	printf(">> Match: %d <<\n", match);
	printf(">> Mismatch: %d <<\n", mismatch);

	// Libera todas memórias alocadas
	for (i = 0; i < QTD_CANDIDATAS; i++) {
		destroiPessoa(vetorCandidatas[i]);
		destroiPessoa(vetorPretendentes[i]);
	}
	destroiListaC(pretendentesValidos);
	destroiListaC(pretendentesLista);
	destroiPilha(candidatasPilha);
	free(vetorCandidatas);
	free(vetorPretendentes);
	vetorCandidatas = NULL;
	vetorPretendentes = NULL;

	return 0;
}