// Define a ordem da árvore
#define ORDEM 7

typedef struct cabecalho1{
    int raiz; // Posição da raiz
    int topo; // Quantidade de elementos na árvore
    int livre; // Cabeça da lista de elementos removidos
} CabecalhoIndices;

typedef struct cabecalho2{
    int posTopo; // Quantidade de espaço já escrito no arquivo
    int posLivre; // Posição removida para sobrescrição
} CabecalhoInfo;

typedef struct produtos{
    int codigo;
    char nome[50];
    char marca[30];
    char categoria[50];
    int estoque;
    double valor;
} Produtos; //Struct que guarda as informações do produto

typedef struct no {
    int numChaves;
    int chave[ORDEM]; // Chaves das informações
    int posInfo[ORDEM]; // Posição das informações
    int filho[ORDEM+1];
} ArvoreB;

typedef struct noAux{
    int codigo; // Chave de identificação do produto
    int posInfo; // Posição da informação no arquivo
} AuxNo;

// Verifica se ocorreu OverFlow no nó em análise
// Entrada: raiz
// Retorno: 1 ou 0
// Pré-condição: raiz tem que estar inicializada
// Pós-condição: nenhuma
int overflow(ArvoreB* raiz);

// Verifica se o nó tem o mínimo de chaves por definição
// Entrada: raiz
// Retorno: 1 ou 0
// Pré-condição: raiz tem que estar inicializada
// Pós-condição: nenhuma
int faltaChave(ArvoreB* raiz);

// Verifica se o nó é folha
// Entrada: raiz
// Retorno: 1 ou 0
// Pré-condição: raiz tem que estar inicializada
// Pós-condição: nenhuma
int ehFolha(ArvoreB* raiz);

// Inserere nova chave na direita de um nó desejado
// Entrada: nó, posição, nó auxiliar e último filho
// Retorno: nenhum
// Pré-condição: elementos não podem ser nulos
// Pós-condição: modifica nó da árvore
void adiciona_Direita(ArvoreB* no, int posicao, AuxNo* auxNo, int ultimo_Filho);

// Procura se existe um determinado elemento e devolve posição da chave
// Entrada: nó, chave e posição
// Retorno: 1 ou 0
// Pré-condição: raiz tem que estar inicializada
// Pós-condição: ponteiro posição alterado
int busca_Posicao(ArvoreB* no, int codigo, int *posicaoChave);

// procura uma determinada chave dentro de um vetor
// Entrada: vetor, posição esquerda, posição direita e cahve
// Retorno: elemento desejado
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int Busca_bin_vetor(int vetor[], int esquerda, int direita, int chave);

// procura uma determinada chave dentro de um vetor
// Entrada: vetor, tamanho e chave
// Retorno: posição desejada
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int Busca_vetor(int vetor[], int tamanho, int chave);

// empurra os elementos de um vetor para direita a partir de uma determinada posição
// Entrada: vetor tamanho e posicao
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetor modificado
void empurra_elementos(int vetor[], int tamanho, int posicao);

// puxa em uma determinada posição a chave e info para a esquerda dentro dos dois vetores 
// Entrada: vetor chave e info, tamanho e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetores modificados
void puxa_chave_info(int chave[], int info[], int tamanho, int posicao);

// puxa em uma determinada posição um vetor para a esquerda dentro
// Entrada: vetor, tamanho e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetor modificado
void puxa(int vetor[], int tamanho, int posicao);

// adiciona elementos dentro dos vetores de chave e info a partir de outro
// Entrada: vetores, tamanho e informações
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetores modificados
int adiciona_chave_info(int chave[], int info[], int tamanho, int ch, int inf);

// Em caso de overflow e impossibilidade de imprestimo, realiza o split 2 3
// Entrada: arquivo, posição do pai, posição esquerda e posição direita
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: árvore modificada
void split2_3(FILE* arquivo, int pos_pai, int pos_esq, int pos_dir);

// Verifica se dá para fazer redistribuição se não faz o split
// Entrada: arquivo, posição do pai e posição do filho
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: árvore modificada
void redistribuicao(FILE* arquivo, int pos_pai, int pos_filho);

// Insere elemento na árvore na posição desejada
// Entrada: arquivo, posição e nó auxiliar com informação base
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: árvore modificada
void insere_Arvore_Aux(FILE* arquivo, int posicao, AuxNo* auxNo);

// Deixa os nós nulos para a criação de um novo nó
// Entrada: vetor e tamanho da ordem
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetor modificado
void inicializa_Filho(int vetor[], int tamanho);

// Realiza split 1-2 caso a raiz tenha OverFlow
// Entrada: arquivo indices, no, noAux;
// Retorno: posição da chave que sobe
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int splitRaiz(FILE* arquivo, int posi_pai);

// Função que insere de forma defenitiva no arquivo binário a informação
// Entrada: arquivo, posição e nó auxiliar
// Retorno: posição inserida
// Pré-condição: nenhuma
// Pós-condição: árvore modificada
int insere_Arvore(FILE* arquivo, int posicao, AuxNo* auxNo);


// Realiza cadastro individual com o usuário digitando dados
// Entrada: arquivos
// Retorno: nenhuma
// Pré-condição: arquivos tem que estarem inicializados
// Pós-condição: provável árvore modificada
void cadastra_Produto_Individual(FILE* ArvoreProdutos, FILE* ArvoreInfo);

// Realiza cadastro individual com o arquivo de dados
// Entrada: arquivos
// Retorno: nenhuma
// Pré-condição: arquivos tem que estarem inicializados
// Pós-condição: provável árvore modificada
int Le_Produto_Arquivo(FILE* ArvoreProdutos, FILE* ArvoreInfo, FILE* finput);

// Retorna a posição de uma determinada informação
// Entrada: arquivos, posição e codigo
// Retorno: nenhuma
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: nenhuma
int posicao_Info(FILE* arquivo, int posicao, int codigo);

// Insere as informações do produto no respectivo arquivo binário
// Entrada: nó desejado e arquivo de info
// Retorno: posição
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
int inserir_Produto(Produtos* no, FILE* ArquivoInfo);

// Função que adiciona um novo produto no arquivo
// Entrada: nó desejado e arquivo de info e chaves
// Retorno: posição
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
void inserir_Produto_Arquivo(Produtos* aux, FILE* ArvoreProdutos, FILE* ArquivoInfo);

// Altera o valor do produto
// Entrada: nó desejado e arquivo de info e chaves codigo e novo valor
// Retorno: nenhum
// Pré-condição: arquivos têm que estarem inicializados
// Pós-condição: arquivo binário modificado
void alterar_Valor(FILE* ArvoreProduto, FILE* ArvoreInfo, int cod, float total);

// Função de chamada para alterar o valor de um produto
// Entrada: arquivos e codigo do produto
// Retorno: nenhum
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
void atualizar_Valor(FILE* ArvoreProduto, FILE* ArvoreInfo, int cod);

// Função chamada para alterar um arquivo por lote
// Entrada: arquivos, codigo do produto e novo estoque
// Retorno: nenhum
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
void altera_Estoque_Arquivo(FILE* ArvoreProduto, FILE* ArquivoInfo, int cod, int estoqueNovo);

// Função chamada para alterar o estoque de um produto
// Entrada: arquivos e codigo do produto
// Retorno: nenhum
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
void altera_Quantidade(FILE* ArvoreProduto, FILE* ArquivoInfo, int cod);

// Função para dar opções de alteração de arquivo
// Entrada: arquivos
// Retorno: nenhum
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: possivel arquivo binário modificado
void atualiza_Produto(FILE* ArvoreProduto, FILE* ArvoreInfo);

// Função de inicialização do processo de remoção
// Entrada: arquivos
// Retorno: nenhum
// Pré-condição: arquivos tem que estar inicializado
// Pós-condição: possivel arquivo binário modificado
void remove_Produto_Individual(FILE* ArvoreB, FILE* ArquivoInfo);

// Adiciona um elemento na posição mais a esquerda de uma chave
// Entrada: arquivos
// Retorno: nenhum
// Pré-condição: arquivos tem que estarem inicializado
// Pós-condição: chave modificada
void adiciona_Esquerda(ArvoreB* no, AuxNo* auxNo);

// Busca o maior código da sub-árvore
// Entrada: arquivos e posição
// Retorno: nenhum
// Pré-condição: um ponteiro para arquivo e a posição da raiz
// Pós-condição: retorna o maior código naquela sub-árvore
AuxNo* maior_Codigo(FILE* arquivo, int posicao);

// Remove um determinado elemento da árvore
// Entrada: arquivos e posição do pai do elemento codigo e quem pode descer
// Retorno: nenhum
// Pré-condição: um ponteiro para arquivo e a posição da raiz
// Pós-condição: modifica a árvore
int remove_Arvore(FILE* arquivoIndice, FILE* arquivoInfo, int posicao, int codigo, int posPai, int desceDireita);

// Remove um determinado elemento da árvore
// Entrada: arquivos e posição e codigo do elemento
// Retorno: nenhum
// Pré-condição: um ponteiro para arquivo e a posição da raiz
// Pós-condição: modifica a árvore
void remove_Produto(FILE* arquivoIndices, FILE* arquivoInfo, int codigo);

// Realiza a leitura do arquivo e altera as informações desejadas
// Entrada: arquivo binário com a árvore e arquivo de leitura
// Retorno: 1 para dizer que não acabou o 0 para End Of File
// Pré-condição: Arquivo binário tem que estar inicializado e posição existentes
// Pós-condição: Arquivo binário modificado
int Atualiza_Produto_Arquivo(FILE* ArvoreProdutos, FILE* ArquivoInfo, FILE* finput);