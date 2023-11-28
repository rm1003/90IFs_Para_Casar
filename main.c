// Arquivo main.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilha.h"
#include "listaCircular.h"
#include "pessoa.h"
#include "conjunto.h"

#define QTD_CANDIDATAS 10
#define QTD_PRETENDENTES 10

void imprimeVetor(int *vetor, int tam){
	for(int i = 0; i < tam; i++)
		printf("%d ",vetor[i]);
	printf("\n");
}

void imprimeCasais(int **casais, int tam, int lsize){
	int min;
	for(int i = 0; i < tam; i+=lsize){
		min = (lsize < tam-i)? lsize : tam-i; 
		for (int j = 0; j < min; j++)
			printf("[%3d,%3d]",casais[0][i+j],casais[1][i+j]);
		printf("\n");
	}
}

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
		destroiConj(atributoP1);
		destroiConj(atributoP2);
		destroiConj(intAtri);
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
	
	int i, infelicidade, mismatch, match, erro, tam, minQtdeCasais;
	int *infelizes,*noivas,*noivos,**matches;
	// Ponteiro para ponteiro para struct pessoa
	struct pessoa **vetorCandidatas, **vetorPretendentes;
	struct listaC *pretendentesValidos = inicializaListaC();
	struct listaC *pretendentesLista = inicializaListaC();
	struct pilha *candidatasPilha = inicializaPilha();

	minQtdeCasais = (QTD_PRETENDENTES<QTD_CANDIDATAS)?QTD_PRETENDENTES:QTD_CANDIDATAS;


	infelicidade = 0;
	mismatch = 0;
	match = 0;

	vetorPretendentes = malloc(QTD_PRETENDENTES * sizeof(struct pessoa*));
	vetorCandidatas = malloc(QTD_CANDIDATAS * sizeof(struct pessoa*));
	infelizes = malloc(QTD_CANDIDATAS * sizeof(int));
	noivas = malloc(minQtdeCasais*sizeof(int));
	noivos = malloc(minQtdeCasais*sizeof(int));
	matches = malloc(2*sizeof(int*));

	if (vetorCandidatas == NULL || vetorPretendentes == NULL)
		return 0;
	if (noivas == NULL || noivos == NULL || matches == NULL)
		return 0;

	matches[0] = noivos;
	matches[1] = noivas; 
	
	// Bota ponteiros para candidatas no vetor 
	// e seus ids na pilha	
	for(i = 0; i < QTD_CANDIDATAS; i++) {
		vetorCandidatas[i] = criaCandidatas(i);
		push(candidatasPilha, i);
	}

	// Bota ponteiros para pretendentes no vetor 
	// e seus ids na lista
	for(i = 0; i < QTD_PRETENDENTES; i++) {
		vetorPretendentes[i] = criaPretendentes(i);
		insere(pretendentesLista, i);
	}

	while(!pilhaVazia(candidatasPilha) && !listaVazia(pretendentesLista)) {
		int *pontos;
		struct item *p1, *p2, *pretendente, *aux, *tmp;
		int candidata, p1pos, p2pos, maisPontosID;

		printf("--------------------------------------------------------------------------------\n");
		// Retiro a candidata da pilha
		pop(candidatasPilha, &candidata);
		printf("A Candidata %3d entrou no show!!\n",candidata);

		aux = pretendentesLista->cabeca;
		tmp = aux->proximo;
		// Acha os pretendentes validos
		tam = pretendentesLista->tamanho;
		for (i = 0; i < tam; i++) {
			// Condição para interseção dos atributos
			if (intersecaoPessoa(vetorPretendentes[aux->id], vetorCandidatas[candidata]) != -1) {
				// Coloca pretendente na lista de pretendentes válidos
				printf("A Candidata %3d gostou do Pretendente %3d\n", candidata, aux->id);
				transfereItem(pretendentesLista, pretendentesValidos, aux->id);
				// Testar se a lista pretendentesLista está vazia (caso unitário)
				if (!listaVazia(pretendentesLista)) {
					aux = tmp;
					tmp = tmp->proximo;
				}
			} else {
				aux = aux->proximo;
				tmp = aux->proximo;
			}
		}

		aux = NULL;
		tmp = NULL;

		// Se não tiver nenhum pretendentes
		if(pretendentesValidos->tamanho < 1){
			printf("A Candidata %3d não gostou de ninguem :(\n",candidata);
			infelizes[infelicidade] = candidata;
			infelicidade++;
			continue; // Pula o laço
		}
		
		// p1pos = posição da pessoa 1
		// p2pos = posição da pessoa 2
		pontos = calloc(pretendentesValidos->tamanho, sizeof(int));
		p1pos = 0;
		p1 = pretendentesValidos->cabeca;
		
		printf("----COMEÇA A BATALHA DOS PRETENDENTES!!!----\n");
		// Batalha dos pretendentes validos
		do {
			p2 = p1->proximo;
			p2pos = p1pos + 1;
			while(p2 != pretendentesValidos->cabeca) {
				printf("\n    Pretendente %3d VS Pretendente %3d\n",p1->id,p2->id);
				switch (batalha(vetorPretendentes[p1->id],vetorPretendentes[p2->id])) {
					case 1:
						// Pessoa 1 ganha
						printf("       PRETENDENTE %3d GANHOU\n",p1->id);
						pontos[p1pos] += 3;
						break;
					case 2:
						printf("       PRETENDENTE %3d GANHOU\n",p2->id);
						// Pessoa 2 ganha
						pontos[p2pos] += 3;
						break;
					case 3:
						// Empate
						printf("          HOUVE UM EMPATE!!!\n");
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
		printf("----TERMINA A BATALHA DOS PRETENDENTES!!!----\n");

		
		// Acha o indice que tem mais pontos
		maisPontosID = 0;
		for(i = 0; i < pretendentesValidos->tamanho; i++){
			if(pontos[maisPontosID] < pontos[i])
				maisPontosID = i;
		}

		// Devolve os perdedores para a lista principal

		if (pretendentesValidos->tamanho > 1) {
			aux = pretendentesValidos->cabeca;
			tmp = aux->proximo;
			tam = pretendentesValidos->tamanho;
			for (i = 0; i < tam; i++) {
				// Todos pretendentes, menos o que possui maior pontuação
				if (i != maisPontosID) {
					transfereItem(pretendentesValidos, pretendentesLista, aux->id);
					aux = tmp;
					tmp = tmp->proximo;
				} else {
					aux = aux->proximo;
					tmp = tmp->proximo;
				}
			}
		}

		// pontos[0] = pontos pretendentes, pontos[1] = pontos candidata
		pontos = realloc(pontos, (2 * sizeof(int)));
		zeraVetor(pontos, 2);
		// Identificador do pretendente
		pretendente = extrairItem(pretendentesValidos, pretendentesValidos->cabeca->id, &erro);
		printf("      O GANHADOR FOI O PRETENDENTE %d\n\n", pretendente->id);

		printf("Entram no 90 IFs: CANDIDATA %3d e PRETENDENTE %3d\n", candidata,pretendente->id);
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
			// Insere pretendente na lista novamente
			insere(pretendentesLista, pretendente->id);
			printf("Candidata %3d e Pretendente %3d deram mismatch!!!! :(\n\n", candidata, pretendente->id);
			mismatch++;
		} else {
			// Candidata ganha match + 1
			printf("Candidata %3d e Pretendente %3d deram match!!!! :)\n\n", candidata, pretendente->id);
			matches[0][match] = pretendente->id;
			matches[1][match] = candidata;
			match++;
		}
		free(pretendente);
		free(pontos);
		pontos = NULL;
	}
	
	printf("Houveram %3d Candidatas Infelizes:\n", infelicidade);
	for(i = 0; i < infelicidade; i+=10)
		imprimeVetor(infelizes+i,(10 < infelicidade-i)? 10 : infelicidade-i);

	printf("Houveram %3d Match:\n", match);
	imprimeCasais(matches,match,3);
	printf("Houveram %3d Mismatch!!\n", mismatch);

	// Libera todas memórias alocadas
	for (i = 0; i < QTD_CANDIDATAS; i++) {
		destroiPessoa(vetorCandidatas[i]);;
	}
	for (i = 0; i < QTD_PRETENDENTES; i++) {
		destroiPessoa(vetorPretendentes[i]);
	}

	destroiListaC(pretendentesValidos);
	destroiListaC(pretendentesLista);
	destroiPilha(candidatasPilha);
	free(vetorCandidatas);
	free(vetorPretendentes);
	free(infelizes);
	free(noivas);
	free(noivos);
	free(matches);
	vetorCandidatas = NULL;
	vetorPretendentes = NULL;

	return 0;
}
