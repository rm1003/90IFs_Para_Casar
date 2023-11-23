#define TAM 8
#define ATRIBUTOSP 3
#define ATRIBUTOSC 2

struct pessoa {
    int qtdAtributos;
    int id;
    int *atributos;
};


// Gera os atributos
void geraAtributos(struct pessoa *p);

// Cria uma pessoa pretendente
struct pessoa *criaPretendentes(int id);

// Cria uma pessoa candidata
struct pessoa *criaCandidatas(int id);

// Colocar em um conjunto o o indice dos atributos
struct conjunto *decodificaAtributos(struct pessoa *p);

// Faz a intersecao entre as pessoas
int intersecaoPessoa(struct pessoa *p1, struct pessoa *p2);

// Destroi struct pessoa
void destroiPessoa(struct pessoa *p);

// Imprime os atributos da pessoa
void imprimeAtributos(struct pessoa *p);
