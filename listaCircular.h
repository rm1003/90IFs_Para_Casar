
struct item {
	int id;
	struct item *anterior;
	struct item *proximo;
};

/* Lista Duplamente Encadeada */
struct listaC {
	struct item *cabeca;
	int tamanho;
};

// aloca um item, e inicializa componentes
struct item *criaItem(int valor);

// aloca um item, e inicializa componentes
struct listaC *inicializaListaC();

// checa se a lista está vazia 
int listaVazia(struct listaC *l);

// insere um elemento na cauda
void insere(struct listaC *l, int x);

//retira um elemento da lista com um dado id
struct item* extrairItem(struct listaC* l, int id,int *erro);

// transfere um item com um dado id da lista l1 para a l2
void transfereItem(struct listaC* l1,struct listaC* l2, int id);

void removeCabeca(struct listaC* l);

void imprimelistaC(struct listaC *l);

// libera toda memoria alocada na lista;
void destroiListaC(struct listaC *l);
