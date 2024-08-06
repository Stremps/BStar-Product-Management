// Configura a inicialização do arquivo binário
// Entrada: resposta da inicilização e ponteiro do arquivo aberto
// Retorno: nenhum
// Pré-condição: Repostar o questionário do inicializa programa
// Pós-condição: nenhuma
void inicializa_ArquivoBinario(char ArquivoBinario, FILE** ArvoreIndices, FILE** ArvoreInfo);

// Realiza a incialização do cabeçalho do arquivo
// Entrada: Arquivo binário
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário incializado
void cria_arquivo_Indice(FILE* arquivo);

// Realiza a incialização do cabeçalho do arquivo
// Entrada: Arquivo binário
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário incializado
void cria_arquivo_Info(FILE* arquivo);

// Realiza a modificação do cabecalho
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário modificado
void escreve_cabecalho_Info(FILE* arquivo, CabecalhoInfo* cabecalho);

// Realiza a modificação do cabecalho
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário modificado
void escreve_cabecalho_Indice(FILE* arquivo, CabecalhoIndices* cabecalho);

// Cria uma cópia de uma chave de indices
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: Posição tem que estar preenchida
// Pós-condição: nenhuma
ArvoreB* le_Indice_arquivo(FILE* arquivo, int posicao);

// Escreve em cima de uma chave de arquivos
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário modificado
void escreve_Indice_arquivo(FILE* arquivo, ArvoreB* no, int posicao);

// Cria uma cópia do cabeçalho de indices
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: endereço com cópia do arquivo
// Pré-condição: Posição tem que estar preenchida
// Pós-condição: nenhuma
CabecalhoIndices* le_Cabecalho_Indice(FILE* arquivo);

// Verifica para inserção no arquivo de indices
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: Posição tem que estar preenchida
// Pós-condição: arquivo binário modificados
int insere_Indice_arquivo(FILE* arquivo, ArvoreB* no, int posicao);

// Escreve os dados de um produto em determinada posição do arquivo
// Entrada: Arquivo, nó desejado e posiçãi
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto, uma posição e um produto 
// Pós-condição: os dados do produto serão escritos no arquivo
void escreve_Produto_Arquivo(FILE* arquivo, Produtos* no, int posicao);

// Lê os dados de um produto em determinada posição do arquivo
// Entrada: Arquivo e posição
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto, uma posição
// Pós-condição: retornará um produto com os dados lidos do arquivo
Produtos* le_Produto_arquivo(FILE* arquivo, int posicao);

// Lê o cabeçalho do arquivo de dados
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: Cabeçalho produto
// Pré-condição: ter um arquivo aberto
// Pós-condição: retornará o cabecalho do arquivo de dados
CabecalhoInfo* le_Cabecalho_Produto(FILE* arquivo);

// Escreve o cabeçalho do arquivo de dados
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto e os dados do cabeçalho
// Pós-condição: os dados do cabeçalho serão escritos no arquivo
void escreve_cabecalho_Produto(FILE* arquivo, CabecalhoInfo* cabecalho);

// Remove produto do arquivo binário
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto e os dados do cabeçalho
// Pós-condição: os dados são escritos no arquivo
void remover_Produto(FILE* arquivo, int posicao);

// Modifica a remoção no cabeçalho
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto e os dados do cabeçalho
// Pós-condição: modifica o cabeçalho
void remover_Indice_Arquivo(FILE* arquivo, ArvoreB* no, int posicao);