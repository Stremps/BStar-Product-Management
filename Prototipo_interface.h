// Realiza a leitura do sistema operacional do compilador
// Entrada: ponteiro sobre inicialização do programa
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: sistema operacional salvo
void inicializa_Programa(char* ArquivoBinario);

// Configura a inicialização do arquivo binário
// Entrada: resposta da inicilização e ponteiro do arquivo aberto
// Retorno: nenhum
// Pré-condição: Repostar o questionário do inicializa programa
// Pós-condição: nenhuma
void inicializa_ArquivoBinario(char ArquivoBinario, FILE** ArvoreIndices, FILE** ArvoreInfo);

// Realiza a quebra de pagina dependendo do sistema operacional do compilador
// Entrada: nenhum
// Retorno: quebra de página
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void quebra_Pagina();

// Apresenta na tela as opções principais do menu do programa
// Entrada: nenhum
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void apreseta_Menu();

// Apresenta as opções de manter produtos
// Entrada: nenhum
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void apreseta_Manter();

// Apresenta as opções de imprimir do programa
// Entrada: nenhum
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void apresenta_Imprimir();

// Função auxiliar para obter altura da árvore
// Entrada: arquivo e posição
// Retorno: altura
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int altura_Arvore(FILE* ArvoreProduto, int posicao);

// Imprime por nível as informações
// Entrada: arquivo e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprime_Nivel(FILE* ArvoreProduto, int pos, int nivel, int nivelAtual);

// Faz a passagem pelas chaves e níveis
// Entrada: arquivo, nivel e nivel atual e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimirArvore_Nivel(FILE* ArvoreProdutos);

// Imprime os produtos pela ordem da chave
// Entrada: arquivos e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_inOrdem(FILE* ArvoreProduto, FILE* ArquivoInfo, int posicao);

// Imprime a informação de um produto a partir da sua posição
// Entrada: arquivos e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_Info(FILE* arquivo, int posicao);

// Imprime a todas as informação de um produto a partir da sua posição
// Entrada: arquivos
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_Produto(FILE* ArvoreProdutos, FILE* ArvoreInfo);

// Imprime a lista de posções livres no arquivo de indice
// Entrada: arquivo
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_Livres_Indices(FILE* arquivo);

// Imprime a lista de posções livres no arquivo de indice
// Entrada: arquivo
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_Livres_Info(FILE* Arquivo);