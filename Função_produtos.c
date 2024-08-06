#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Prototipo_auxiliares.h"
#include "Prototipo_comandos.h"
#include "Prototipo_interface.h"
#include "Prototipo_produtos.h"
#include "Prototipo_arquivoBinario.h"

// Verifica se ocorreu OverFlow no nó em análise
// Entrada: raiz
// Retorno: 1 ou 0
// Pré-condição: raiz tem que estar inicializada
// Pós-condição: nenhuma
int overflow(ArvoreB* raiz){
    return (raiz->numChaves == ORDEM);
}

// Verifica se o nó tem o mínimo de chaves por definição
// Entrada: raiz
// Retorno: 1 ou 0
// Pré-condição: raiz tem que estar inicializada
// Pós-condição: nenhuma
int faltaChave(ArvoreB* raiz){
    return (raiz->numChaves < (2*ORDEM)/3);
}

// Verifica se o nó é folha
// Entrada: raiz
// Retorno: 1 ou 0
// Pré-condição: raiz tem que estar inicializada
// Pós-condição: nenhuma
int ehFolha(ArvoreB* raiz){
    return (raiz->filho[0] == -1);
}

// Inserere nova chave na direita de um nó desejado
// Entrada: nó, posição, nó auxiliar e último filho
// Retorno: nenhum
// Pré-condição: elementos não podem ser nulos
// Pós-condição: modifica nó da árvore
void adiciona_Direita(ArvoreB* no, int posicao, AuxNo* auxNo, int ultimo_Filho){
    int i;

    for(i = no->numChaves; i > posicao; i--){
        no->posInfo[i] = no->posInfo[i - 1];
        no->chave[i] = no->chave[i - 1];
        no->filho[i + 1] = no->filho[i];
    }

    no->posInfo[posicao] = auxNo->posInfo;
    no->chave[posicao] = auxNo->codigo;
    no->filho[posicao + 1] = ultimo_Filho;
    no->numChaves++;
}

// Procura se existe um determinado elemento e devolve posição da chave
// Entrada: nó, chave e posição
// Retorno: 1 ou 0
// Pré-condição: raiz tem que estar inicializada
// Pós-condição: ponteiro posição alterado
int busca_Posicao(ArvoreB* no, int codigo, int *posicaoChave){
    
    for((*posicaoChave)=0; (*posicaoChave) < no->numChaves; (*posicaoChave)++){
        if(codigo == no->chave[(*posicaoChave)]) return 1; 
        else if(codigo < no->chave[(*posicaoChave)]) break; 
    }

    return 0; 
}

// procura uma determinada chave dentro de um vetor
// Entrada: vetor, posição esquerda, posição direita e cahve
// Retorno: elemento desejado
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int Busca_bin_vetor(int vetor[], int esquerda, int direita, int chave){
    int meio = (esquerda + direita)/2;
    
    if(direita <= esquerda)
        return meio;

    if(vetor[meio] == chave)
        return meio;

    if(vetor[meio] > chave) 
        return Busca_bin_vetor(vetor, esquerda, meio-1, chave);

    return Busca_bin_vetor(vetor, meio + 1, direita, chave);
}

// procura uma determinada chave dentro de um vetor
// Entrada: vetor, tamanho e chave
// Retorno: posição desejada
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int Busca_vetor(int vetor[], int tamanho, int chave){
    int pos = Busca_bin_vetor(vetor, 0, tamanho-1, chave);

    if(pos < tamanho && chave > vetor[pos]) 
        pos++;
        
    return pos;
}

// empurra os elementos de um vetor para direita a partir de uma determinada posição
// Entrada: vetor tamanho e posicao
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetor modificado
void empurra_elementos(int vetor[], int tamanho, int posicao){
    int i;

    for(i = tamanho - 1 ; i > posicao ; i--){
        vetor[i] = vetor[i-1];
    }
}

// puxa em uma determinada posição a chave e info para a esquerda dentro dos dois vetores 
// Entrada: vetor chave e info, tamanho e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetores modificados
void puxa_chave_info(int chave[], int info[], int tamanho, int posicao){
    int i;

    for(i = posicao; i < tamanho - 1; i++){
        chave[i] = chave[i + 1];
        info[i] = info[i + 1];
    }
}

// puxa em uma determinada posição um vetor para a esquerda dentro
// Entrada: vetor, tamanho e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetor modificado
void puxa(int vetor[], int tamanho, int posicao){
    int i;

    for(i = posicao ; i < tamanho - 1 ; i++){
        vetor[i] = vetor[i + 1];
    }
}

// adiciona elementos dentro dos vetores de chave e info a partir de outro
// Entrada: vetores, tamanho e informações
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetores modificados
int adiciona_chave_info(int chave[], int info[], int tamanho, int ch, int inf){
    int pos = Busca_vetor(chave, tamanho - 1, ch);
    empurra_elementos(chave, tamanho + 1, pos);
    empurra_elementos(info, tamanho + 1, pos);
    chave[pos] = ch;
    info[pos] = inf;
    return pos;
}

// Em caso de overflow e impossibilidade de imprestimo, realiza o split 2 3
// Entrada: arquivo, posição do pai, posição esquerda e posição direita
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: árvore modificada
void split2_3(FILE* arquivo, int pos_pai, int pos_esq, int pos_dir){
    ArvoreB* pai = le_Indice_arquivo(arquivo, pos_pai);
    ArvoreB* esq = le_Indice_arquivo(arquivo, pai->filho[pos_esq]);
    ArvoreB* dir = le_Indice_arquivo(arquivo, pai->filho[pos_dir]);
    ArvoreB* meio = (ArvoreB*) malloc(sizeof(ArvoreB));
    meio->numChaves = 0;
    inicializa_Filho(meio->filho, ORDEM+1);
    
    int min = (ORDEM-1)*2/3;
    
    int chave_separadora = pai->chave[pos_esq];
    int chave_separadora_Info = pai->posInfo[pos_esq];

    pai->chave[pos_esq] = esq->chave[min]; //elemento splitado do no filho
    pai->posInfo[pos_esq] = esq->posInfo[min];

    int i;
    
    for(i = min + 1; i < esq->numChaves; i++){
        meio->filho[meio->numChaves] = esq->filho[i];
        esq->filho[i] = -1; //filhos passados vao ficar nulos
        
        meio->numChaves++;
        adiciona_chave_info(meio->chave, meio->posInfo, meio->numChaves, esq->chave[i], esq->posInfo[i]);
    }
    
    meio->filho[meio->numChaves] = esq->filho[esq->numChaves]; //passando o ultimo filho
    esq->filho[esq->numChaves] = -1;
    meio->numChaves++;
    adiciona_chave_info(meio->chave, meio->posInfo, meio->numChaves, chave_separadora, chave_separadora_Info);
    
    esq->numChaves = min; //Número de chaves finais na esquerda
    
    for(i = meio->numChaves; i < min; i++){
        meio->filho[meio->numChaves] = dir->filho[0];
        puxa(dir->filho, dir->numChaves+1, 0);
        meio->numChaves++;

        adiciona_chave_info(meio->chave, meio->posInfo, meio->numChaves, dir->chave[0], dir->posInfo[0]);


        puxa_chave_info(dir->chave, dir->posInfo, dir->numChaves, 0);
        dir->numChaves--;
    }
    meio->filho[meio->numChaves] = dir->filho[0];
    puxa(dir->filho, dir->numChaves+1, 0);
    
    //Escreve na memória novo no
    int pos_meio = insere_Indice_arquivo(arquivo, meio, -1);
    
    pai->numChaves++;
    empurra_elementos(pai->filho, pai->numChaves+1, pos_esq);
    pai->filho[pos_esq+1] = pos_meio;
    pos_dir++;
    
    
    adiciona_chave_info(pai->chave, pai->posInfo, pai->numChaves, dir->chave[0], dir->posInfo[0]);
    puxa_chave_info(dir->chave, dir->posInfo, dir->numChaves, 0);
    dir->numChaves--;
    

    insere_Indice_arquivo(arquivo, pai, pos_pai);
    insere_Indice_arquivo(arquivo, esq, pai->filho[pos_esq]);
    insere_Indice_arquivo(arquivo, dir, pai->filho[pos_dir]);


    free(pai);
    free(esq);
    free(dir);
    free(meio);
}

// Verifica se dá para fazer redistribuição se não faz o split
// Entrada: arquivo, posição do pai e posição do filho
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: árvore modificada
void redistribuicao(FILE* arquivo, int pos_pai, int pos_filho){
    ArvoreB* filho; 
    ArvoreB *pai;
    ArvoreB *irmao_esq = NULL; 
    ArvoreB *irmao_dir = NULL;
    
    pai = le_Indice_arquivo(arquivo, pos_pai);
    filho = le_Indice_arquivo(arquivo, pai->filho[pos_filho]);
    
    // Verifica os irmãos
    if(pos_filho!=0){ //elemento mais a esquerda
        irmao_esq = le_Indice_arquivo(arquivo, pai->filho[pos_filho-1]); //Irmão da esquerda
    }
    if(pos_filho!=ORDEM-1 && pai->filho[pos_filho+1]!=-1){
        irmao_dir = le_Indice_arquivo(arquivo, pai->filho[pos_filho+1]); //Irmão da direita
    }
    
    // Depois verifica se é possível fazer empréstimo
    if(irmao_esq!=NULL && irmao_esq->numChaves<ORDEM-1){
        if(irmao_dir!=NULL) free(irmao_dir);
        //emprestimo do no da direita para o da esquerda

        irmao_esq->numChaves++; //Incrementa o irmão da esquerda
        adiciona_chave_info(irmao_esq->chave, irmao_esq->posInfo, irmao_esq->numChaves, pai->chave[pos_filho-1], pai->posInfo[pos_filho-1]); //Desce o elemento do pai


        irmao_esq->filho[irmao_esq->numChaves] = filho->filho[0]; //O filho mais a esquerda passa para o irmão

        pai->chave[pos_filho-1] = filho->chave[0]; //A chave mais a esquerda do filho sobre para o pai
        pai->posInfo[pos_filho-1] = filho->posInfo[0]; //A chave mais a esquerda do filho sobre para o pai

        puxa_chave_info(filho->chave, filho->posInfo, filho->numChaves, 0); //Move para a esquerda todas as chaves do filho
        puxa(filho->filho, filho->numChaves+1, 0); //Move para a esquerda todos os filhos do filho
        filho->filho[filho->numChaves] = -1; //Nulifica o filho mais a direita
        filho->numChaves--; //Decrementa o tamanho
        
        //Modifica na memória binária
        insere_Indice_arquivo(arquivo, pai, pos_pai);
        insere_Indice_arquivo(arquivo, filho, pai->filho[pos_filho]);
        insere_Indice_arquivo(arquivo, irmao_esq, pai->filho[pos_filho-1]);
        

        //Libera tudo
        free(pai);
        free(filho);
	    free(irmao_esq);
    }
    else if(irmao_dir!=NULL && irmao_dir->numChaves<ORDEM-1){
        if(irmao_esq!=NULL) free(irmao_esq);
        
        //emprestimo do no da esquerda para o da direita

        irmao_dir->numChaves++; //Incrementa o irmão da direita

        adiciona_chave_info(irmao_dir->chave, irmao_dir->posInfo, irmao_dir->numChaves, pai->chave[pos_filho], pai->posInfo[pos_filho]); //Desce o elemento do pai

        empurra_elementos(irmao_dir->filho, irmao_dir->numChaves+1, 0); //Prepara o irmão da direita para receber a chave da esquerda
        irmao_dir->filho[0] = filho->filho[filho->numChaves]; // passa a chave da esquerda
        
        pai->chave[pos_filho] = filho->chave[filho->numChaves-1]; //Adiciona o novo filho mais a direita no pai
        pai->posInfo[pos_filho] = filho->posInfo[filho->numChaves-1];

        filho->filho[filho->numChaves] = -1; //Nulifica o filho mais a direita
        filho->numChaves--;
        
        //Modifica na memória binária
        insere_Indice_arquivo(arquivo, pai, pos_pai);
        insere_Indice_arquivo(arquivo, filho, pai->filho[pos_filho]);
        insere_Indice_arquivo(arquivo, irmao_dir, pai->filho[pos_filho+1]);
        
        //Libera tudo
      free(pai);
	    free(filho);
	    free(irmao_dir);
    }
    //Split 2-3
    else{
        if(irmao_esq!=NULL){ //Apresenta irmão na esquerda
            free(pai);
            free(filho);
            if(irmao_esq!=NULL) free(irmao_esq);
            if(irmao_dir!=NULL) free(irmao_dir);
            split2_3(arquivo, pos_pai, pos_filho-1, pos_filho);
        }
        else if(irmao_dir!=NULL){ //Apresenta irmão apenas na direita
            free(pai);
            free(filho);
            if(irmao_esq!=NULL) free(irmao_esq);
            if(irmao_dir!=NULL) free(irmao_dir);
            split2_3(arquivo, pos_pai, pos_filho, pos_filho+1);
        }
    }
}

// Insere elemento na árvore na posição desejada
// Entrada: arquivo, posição e nó auxiliar com informação base
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: árvore modificada
void insere_Arvore_Aux(FILE* arquivo, int posicao, AuxNo* auxNo){
    ArvoreB* no = le_Indice_arquivo(arquivo, posicao);
    int posicaoChave;
    busca_Posicao(no,auxNo->codigo, &posicaoChave);

    if (ehFolha(no)) { //caso base para recursividade
      adiciona_Direita(no, posicaoChave, auxNo, -1);
      escreve_Indice_arquivo(arquivo, no, posicao);

      return; //break point
    }
    else {
      int pos_filho = no->filho[posicaoChave];
      
      insere_Arvore_Aux(arquivo, pos_filho, auxNo);
      ArvoreB* filho = le_Indice_arquivo(arquivo, pos_filho);

      if (overflow(filho)) { //Verifica se houve overflow na inserção
        free(filho);
        redistribuicao(arquivo, posicao, posicaoChave);
        return; //break point
    }
  }
}

// Deixa os nós nulos para a criação de um novo nó
// Entrada: vetor e tamanho da ordem
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: vetor modificado
void inicializa_Filho(int vetor[], int tamanho){
    for(int i = 0 ; i < tamanho ;i++)
        vetor[i] = -1;
}

// Realiza split 1-2 caso a raiz tenha OverFlow
// Entrada: arquivo indices, no, noAux;
// Retorno: posição da chave que sobe
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int splitRaiz(FILE* arquivo, int posi_pai){
    ArvoreB* esq = le_Indice_arquivo(arquivo, posi_pai);

    ArvoreB* dir = (ArvoreB*) malloc(sizeof(ArvoreB));
    dir->numChaves = 0;
    inicializa_Filho(dir->filho, ORDEM+1);

    ArvoreB* pai = (ArvoreB*) malloc(sizeof(ArvoreB));
    pai->numChaves = 0;
    inicializa_Filho(pai->filho, ORDEM+1);

    int minimo = ORDEM/2; //Mínimo de elementos dentro de uma chave

    // Adiciona chave média da esquerda em pai
    pai->numChaves++;
    adiciona_chave_info(pai->chave, pai->posInfo, pai->numChaves, esq->chave[minimo], esq->posInfo[minimo]);
    esq->chave[minimo] = -1;
    esq->posInfo[minimo] = -1;
    // Adiciona metade direita das chaves da esquerda em direita
    for(int i=minimo+1 ; i<esq->numChaves ; i++){
        dir->filho[dir->numChaves] = esq->filho[i];
        esq->filho[i] = -1;

        dir->numChaves++;
        adiciona_chave_info(dir->chave, dir->posInfo, dir->numChaves, esq->chave[i], esq->posInfo[i]);
    }
    dir->filho[dir->numChaves] = esq->filho[esq->numChaves];
    esq->filho[esq->numChaves] = -1;

    esq->numChaves = minimo; //Tamanho pós split

    //Modificação do arquivo binário
    pai->filho[0] = insere_Indice_arquivo(arquivo, esq, posi_pai);
    pai->filho[1] = insere_Indice_arquivo(arquivo, dir, -1);
    int pos_novo_pai = insere_Indice_arquivo(arquivo, pai, -1);


    free(esq);
    free(dir);
    free(pai);

    return pos_novo_pai;
    }

// Função que insere de forma defenitiva no arquivo binário a informação
// Entrada: arquivo, posição e nó auxiliar
// Retorno: posição inserida
// Pré-condição: nenhuma
// Pós-condição: árvore modificada
int insere_Arvore(FILE* arquivo, int posicao, AuxNo* auxNo){
    if(posicao == -1){ //Caso a raiz não exista
        // if(nos livres) tem que adicionar o caso de nós livres

        ArvoreB* no = (ArvoreB*) malloc(sizeof(ArvoreB));
        inicializa_Filho(no->filho, ORDEM+1);
        no->numChaves = 1;
        adiciona_chave_info(no->chave, no->filho, no->numChaves, auxNo->codigo, posicao);

        int pos = insere_Indice_arquivo(arquivo, no, -1);

        return pos;
    }
    else{
        insere_Arvore_Aux(arquivo, posicao, auxNo); 
        ArvoreB* no = le_Indice_arquivo(arquivo, posicao);
        
        if(overflow(no)){
            free(no);
            int x = splitRaiz(arquivo, posicao);

            return x;
        }
        free(no);
        return posicao;
    }
}

// Realiza cadastro individual com o usuário digitando dados
// Entrada: arquivos
// Retorno: nenhuma
// Pré-condição: arquivos tem que estarem inicializados
// Pós-condição: provável árvore modificada
void cadastra_Produto_Individual(FILE* ArvoreProdutos, FILE* ArvoreInfo){
    Produtos* aux = (Produtos*) malloc(sizeof(Produtos));

    printf("Insira o codigo do produto:\n>");
    scanf("%d%*c", &aux->codigo);

    printf("Insira o nome do produto (max. 50 caracteres):\n>");
    scanf("%[^\n]%*c", aux->nome);

    printf("Insira a marca do produto (max. 30 caracteres):\n>");
    scanf("%[^\n]%*c", aux->marca);

    printf("Insira a categoria do produto (max. 50 caracteres):\n>");
    scanf("%[^\n]%*c", aux->categoria);

    printf("Insira o estoque do produto:\n>");
    scanf("%d%*c", &aux->estoque);

    printf("Insira o preço do produto (R$ XX,XX):\n> R$ ");
    aux->valor = ler_Preco();

    inserir_Produto_Arquivo(aux, ArvoreProdutos, ArvoreInfo);

    free(aux);
}

// Realiza cadastro individual com o arquivo de dados
// Entrada: arquivos
// Retorno: nenhuma
// Pré-condição: arquivos tem que estarem inicializados
// Pós-condição: provável árvore modificada
int Le_Produto_Arquivo(FILE* ArvoreProdutos, FILE* ArvoreInfo, FILE* finput){
    Produtos* aux = (Produtos*) malloc(sizeof(Produtos));

    if(fscanf(finput, "%d;", &aux->codigo) == EOF) //Realiza a leitura do código e acaba se for Fim Do Arquivo
        return 0;

    fscanf(finput, "%[^;]%*c", aux->nome);

    fscanf(finput, "%[^;]%*c", aux->marca);

    fscanf(finput, "%[^;]%*c", aux->categoria);

    fscanf(finput, "%d;", &aux->estoque);

    aux->valor = le_Preco_Arquivo(finput); //Leitura para mascara a virgula

    inserir_Produto_Arquivo(aux, ArvoreProdutos, ArvoreInfo);

    free(aux);
}

// Retorna a posição de uma determinada informação
// Entrada: arquivos, posição e codigo
// Retorno: nenhuma
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: nenhuma
int posicao_Info(FILE* arquivo, int posicao, int codigo){
    if (posicao == -1) return -1;

    int i;

    ArvoreB* no = le_Indice_arquivo(arquivo, posicao);
    for (i = 0; i < no->numChaves; i++){
        if (codigo < no->chave[i]) return posicao_Info(arquivo, no->filho[i], codigo);
        if (codigo == no->chave[i]) return no->posInfo[i];
    }

    return posicao_Info(arquivo, no->filho[no->numChaves], codigo); //Último filho
}

// Insere as informações do produto no respectivo arquivo binário
// Entrada: nó desejado e arquivo de info
// Retorno: posição
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
int inserir_Produto(Produtos* no, FILE* ArquivoInfo){
    CabecalhoInfo *cab = le_Cabecalho_Produto(ArquivoInfo);
    int pos;

    if(cab->posLivre == -1){
        escreve_Produto_Arquivo(ArquivoInfo, no, cab->posTopo);
        pos = cab->posTopo;
        cab->posTopo++;
    }
    else{
        Produtos *produto = le_Produto_arquivo(ArquivoInfo, cab->posLivre);
        escreve_Produto_Arquivo(ArquivoInfo, no, cab->posLivre);
        pos = cab->posLivre;
        cab->posLivre = produto->codigo;
        free(produto);
    }

    escreve_cabecalho_Produto(ArquivoInfo, cab);
    free(cab);
    return pos;
}

// Função que adiciona um novo produto no arquivo
// Entrada: nó desejado e arquivo de info e chaves
// Retorno: posição
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
void inserir_Produto_Arquivo(Produtos* aux, FILE* ArvoreProdutos, FILE* ArquivoInfo){
    CabecalhoIndices *cab = le_Cabecalho_Indice(ArvoreProdutos);
    int flag = posicao_Info(ArvoreProdutos,cab->raiz,aux->codigo);

    if(flag != -1){ //Para caso o produto já tenha sido inserido
        printf("Codigo repetido.\n");
        return; //Break point
    }

    AuxNo* auxNo = (AuxNo*)malloc(sizeof(AuxNo));
    auxNo->posInfo = inserir_Produto(aux, ArquivoInfo);
    auxNo->codigo = aux->codigo;
    int posRaiz = insere_Arvore(ArvoreProdutos, cab->raiz, auxNo);
    cab = le_Cabecalho_Indice(ArvoreProdutos);
    cab->raiz = posRaiz;
    escreve_cabecalho_Indice(ArvoreProdutos, cab);
    
    free(cab);
    free(auxNo);
}

// Altera o valor do produto
// Entrada: nó desejado e arquivo de info e chaves codigo e novo valor
// Retorno: nenhum
// Pré-condição: arquivos têm que estarem inicializados
// Pós-condição: arquivo binário modificado
void alterar_Valor(FILE* ArvoreProduto, FILE* ArvoreInfo, int cod, float total){
    CabecalhoIndices* cab = le_Cabecalho_Indice(ArvoreProduto);
    int posProduto = posicao_Info(ArvoreProduto, cab->raiz, cod);
    
    if(posProduto == -1){
        printf("Codigo nao encontrado\n");
        return;
    }
    else{
        Produtos* produto = le_Produto_arquivo(ArvoreInfo, posProduto);
        produto->valor = total;
        escreve_Produto_Arquivo(ArvoreInfo, produto, posProduto);
	    free(produto);
    }
}

// Função de chamada para alterar o valor de um produto
// Entrada: arquivos e codigo do produto
// Retorno: nenhum
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
void atualizar_Valor(FILE* ArvoreProduto, FILE* ArvoreInfo, int cod){

    CabecalhoIndices *cab = le_Cabecalho_Indice(ArvoreProduto);
    float valor1, valor2, total;
    
    if(cab->raiz == -1){
        printf ("Arvore Vazia\n");
    }
    else{
        printf("Digite o novo valor: ");
        total = ler_Preco();
        
        alterar_Valor(ArvoreProduto, ArvoreInfo, cod, total);
    }
}

// Função chamada para alterar um arquivo por lote
// Entrada: arquivos, codigo do produto e novo estoque
// Retorno: nenhum
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
void altera_Estoque_Arquivo(FILE* ArvoreProduto, FILE* ArquivoInfo, int cod, int estoqueNovo){
    CabecalhoIndices* cab = le_Cabecalho_Indice(ArvoreProduto);
    int posProduto = posicao_Info(ArvoreProduto, cab->raiz, cod);
    
    if(posProduto == -1){
        printf("Codigo nao encontrado\n");
        return;
    }
    else{

        Produtos* produto = le_Produto_arquivo(ArquivoInfo, posProduto);
        produto->estoque = estoqueNovo;
        escreve_Produto_Arquivo(ArquivoInfo, produto, posProduto);
	    free(produto);
    }
}

// Função chamada para alterar o estoque de um produto
// Entrada: arquivos e codigo do produto
// Retorno: nenhum
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: arquivo binário modificado
void altera_Quantidade(FILE* ArvoreProduto, FILE* ArquivoInfo, int cod){
    CabecalhoIndices* cab = le_Cabecalho_Indice(ArvoreProduto);
    int posProduto = posicao_Info(ArvoreProduto, cab->raiz, cod);
    
    if(posProduto == -1){
        printf("Codigo nao encontrado\n");
        return;
    }
    else{
        int estoqueNovo;

        printf("Digite o novo valor: ");
        scanf("%d%*c", &estoqueNovo);
        Produtos* produto = le_Produto_arquivo(ArquivoInfo, posProduto);
        produto->estoque = estoqueNovo;
        escreve_Produto_Arquivo(ArquivoInfo, produto, posProduto);
	    free(produto);
    }
}

// Função para dar opções de alteração de arquivo
// Entrada: arquivos
// Retorno: nenhum
// Pré-condição: arquivo tem que estar inicializado
// Pós-condição: possivel arquivo binário modificado
void atualiza_Produto(FILE* ArvoreProduto, FILE* ArvoreInfo){
    
    quebra_Pagina();
    
    printf("1 - Atualizar valor\n");
    printf("2 - Atualizar estoque\n");
    
    int escolha;
    
    scanf("%d%*c", &escolha);
    
    switch (escolha){
        case 1 :
            printf("Insira o código do produto\n>");
            scanf("%d%*c", &escolha);
            atualizar_Valor(ArvoreProduto, ArvoreInfo, escolha);
            break;
        case 2 :
            printf("Insira o código do produto\n>");
            scanf("%d%*c", &escolha);
            altera_Quantidade(ArvoreProduto, ArvoreInfo, escolha);
            break;
        default:
            printf("Comando invalido!\n");
            break;
    }
}

// Função de inicialização do processo de remoção
// Entrada: arquivos
// Retorno: nenhum
// Pré-condição: arquivos tem que estar inicializado
// Pós-condição: possivel arquivo binário modificado
void remove_Produto_Individual(FILE* ArvoreB, FILE* ArquivoInfo){
    int codigo;

    printf("Insira o codigo desejado:\n>");
    scanf("%d%*c", &codigo);
    remove_Produto(ArvoreB, ArquivoInfo, codigo);
}

// Adiciona um elemento na posição mais a esquerda de uma chave
// Entrada: arquivos
// Retorno: nenhum
// Pré-condição: arquivos tem que estarem inicializado
// Pós-condição: chave modificada
void adiciona_Esquerda(ArvoreB* no, AuxNo* auxNo) {
    int i;

    for (i = no->numChaves; i > 0; i--) {
        no->posInfo[i] = no->posInfo[i-1];
        no->chave[i] = no->chave[i-1];
        no->filho[i] = no->filho[i-1];
    }

    no->posInfo[0] = auxNo->posInfo;
    no->chave[0] = auxNo->codigo;
    no->filho[no->numChaves + 1] = no->filho[no->numChaves];
    no->numChaves++;
}

// Busca o maior código da sub-árvore
// Entrada: arquivos e posição
// Retorno: nenhum
// Pré-condição: um ponteiro para arquivo e a posição da raiz
// Pós-condição: retorna o maior código naquela sub-árvore
AuxNo* maior_Codigo(FILE* arquivo, int posicao){
  ArvoreB* no = le_Indice_arquivo(arquivo, posicao);
  if (ehFolha(no)) {
    AuxNo* auxNo = (AuxNo*) malloc(sizeof(AuxNo));
    auxNo->codigo = no->chave[no->numChaves - 1];
    auxNo->posInfo = no->posInfo[no->numChaves - 1];
    return auxNo;
  } 
	else {
    return maior_Codigo(arquivo, no->filho[no->numChaves]);
  }
}

// Remove um determinado elemento da árvore
// Entrada: arquivos e posição do pai do elemento codigo e quem pode descer
// Retorno: nenhum
// Pré-condição: um ponteiro para arquivo e a posição da raiz
// Pós-condição: modifica a árvore
int remove_Arvore(FILE* arquivoIndice, FILE* arquivoInfo, int posicao, int codigo, int posPai, int desceDireita){
    ArvoreB* no = le_Indice_arquivo(arquivoIndice, posicao);
    int i, j, k;
    if (ehFolha(no)) {
        if (desceDireita) {
            //tera que remover o utlimo
            no->posInfo[no->numChaves - 1] = -1;
            no->chave[no->numChaves - 1] = -1;
            no->numChaves--;

            escreve_Indice_arquivo(arquivoIndice, no, posicao);
            return faltaChave(no);
        }

        for (i = 0; i < no->numChaves; i++) {
            if (codigo == no->chave[i]) remover_Produto(arquivoInfo, no->posInfo[i]);
            if (codigo <= no->chave[i]){
                no->posInfo[i] = no->posInfo[i + 1];
                no->chave[i] = no->chave[i + 1];
            }
        }

        no->posInfo[no->numChaves] = -1;
        no->chave[no->numChaves] = -1;
        no->numChaves = no->numChaves - 1;
        escreve_Indice_arquivo(arquivoIndice, no, posicao);

        if (posPai == -1) {
            //raiz
            if (no->numChaves == 0) {
                //acabou a arvore
                return -1;
            }
            return posicao;
        }
        return faltaChave(no);
    }

    int filhoEstaFaltando = -1;

    if (desceDireita) {
        filhoEstaFaltando = remove_Arvore(arquivoIndice, arquivoInfo, no->filho[no->numChaves], codigo, posicao, 1);
    } 
    else {
        int i;
        for(i = 0; i < no->numChaves; i++) {
            if (codigo < no->chave[i] || codigo == no->chave[i]) break;
        }

        if(codigo == no->chave[i]) {
            //deletar no meio da arvore;
            remover_Produto(arquivoInfo, no->posInfo[i]);

            AuxNo* auxNo = maior_Codigo(arquivoIndice, no->filho[i]);
            no->chave[i] = auxNo->codigo;
            no->posInfo[i] = auxNo->posInfo;

            filhoEstaFaltando = remove_Arvore(arquivoIndice, arquivoInfo, no->filho[i], codigo, posicao, 1);
        } 
        else {
            filhoEstaFaltando = remove_Arvore(arquivoIndice, arquivoInfo, no->filho[i], codigo, posicao, 0);
        }
    }

    if (filhoEstaFaltando == 0) {
        //não precisa arrumar filho
        escreve_Indice_arquivo(arquivoIndice, no, posicao);

        if (posPai == -1) return posicao;
        
        return 0;
    }

        //tem que arrumar o filho
        int indexFilhoArrumar = -1;
        int indexChave = -1;

    for( j = 0; j < no->numChaves; j++) {
        ArvoreB* filhoArrumarTest = le_Indice_arquivo(arquivoIndice, no->filho[j]);

        if (faltaChave(filhoArrumarTest)) {
            indexChave = j;
            indexFilhoArrumar = j;
        }
    }

    if (indexFilhoArrumar == -1) {
        indexFilhoArrumar = no->numChaves;
    }

    if (indexChave == -1) {
        indexChave = no->numChaves - 1;
    }

    //tenta emprestar da direita
    if (indexFilhoArrumar < no->numChaves) {
        ArvoreB* noFilhoDirTest = le_Indice_arquivo(arquivoIndice, no->filho[indexFilhoArrumar + 1]);

        if (noFilhoDirTest->numChaves > (ORDEM / 2)) {
            ArvoreB* noFilhoArrumar = le_Indice_arquivo(arquivoIndice, no->filho[indexFilhoArrumar]);

            noFilhoArrumar->chave[noFilhoArrumar->numChaves] = no->chave[indexFilhoArrumar];
            noFilhoArrumar->posInfo[noFilhoArrumar->numChaves + 1] = no->posInfo[indexFilhoArrumar];

            no->chave[indexFilhoArrumar] = noFilhoDirTest->chave[0];
            no->posInfo[indexFilhoArrumar] = noFilhoDirTest->posInfo[0];

            for(i = 0; i < noFilhoDirTest->numChaves; i++) {
                noFilhoDirTest->chave[i] = noFilhoDirTest->chave[i + 1];
                noFilhoDirTest->posInfo[i] = noFilhoDirTest->posInfo[i + 1];
            }

            noFilhoDirTest->chave[noFilhoDirTest -> numChaves] = -1;
            noFilhoDirTest->posInfo[noFilhoDirTest -> numChaves] = -1;

            noFilhoArrumar->numChaves++;
            noFilhoDirTest->numChaves--;

            escreve_Indice_arquivo(arquivoIndice, no, posicao);
            escreve_Indice_arquivo(arquivoIndice, noFilhoArrumar, no->filho[indexFilhoArrumar]);
            escreve_Indice_arquivo(arquivoIndice, noFilhoDirTest, no->filho[indexFilhoArrumar + 1]);

            if (posPai == -1) {
                return posicao;
            }
            return 0;
        }
    }
    //tenta emprestar da esquerda
    if (indexFilhoArrumar != 0) {
        ArvoreB* noFilhoEsqTest = le_Indice_arquivo(arquivoIndice, no -> filho[indexFilhoArrumar - 1]);

        if (noFilhoEsqTest->numChaves > (ORDEM / 2)) {
            ArvoreB* noFilhoArrumar = le_Indice_arquivo(arquivoIndice, no->filho[indexFilhoArrumar]);

            for(i=0; i < noFilhoArrumar->numChaves; i++) {
                noFilhoArrumar->chave[i + 1] = noFilhoArrumar->chave[i];
                noFilhoArrumar->posInfo[i + 1] = noFilhoArrumar->posInfo[i];
            }

            noFilhoArrumar->chave[0] = no->chave[indexChave];
            noFilhoArrumar->posInfo[0] = no->posInfo[indexChave];

            no->chave[indexChave] = noFilhoEsqTest->chave[noFilhoEsqTest->numChaves - 1];
            no->posInfo[indexChave] = noFilhoEsqTest->posInfo[noFilhoEsqTest->numChaves - 1];

            noFilhoEsqTest->chave[noFilhoEsqTest -> numChaves - 1] = -1;
            noFilhoEsqTest->posInfo[noFilhoEsqTest -> numChaves - 1] = -1;

            noFilhoEsqTest->numChaves--;
            noFilhoArrumar->numChaves++;

            escreve_Indice_arquivo(arquivoIndice, no, posicao);
            escreve_Indice_arquivo(arquivoIndice, noFilhoArrumar, no->filho[indexFilhoArrumar]);
            escreve_Indice_arquivo(arquivoIndice, noFilhoEsqTest, no->filho[indexFilhoArrumar - 1]);

            if (posPai == -1) {
                return posicao;
            }
            return 0;
        }
    }

    //terá que juntar dois nós
    int indexJunta = -1;
    if (indexFilhoArrumar == no->numChaves) {
        indexJunta = indexFilhoArrumar - 1;
    } else {
        indexJunta = indexFilhoArrumar + 1;
    }

    int posFilhoJunta = no->filho[indexJunta];
    ArvoreB* filhoJunta = le_Indice_arquivo(arquivoIndice, posFilhoJunta);

    int posFilhoArrumar = no->filho[indexFilhoArrumar];
    ArvoreB* noFilhoArrumar = le_Indice_arquivo(arquivoIndice, posFilhoArrumar);

    if (indexJunta < indexFilhoArrumar) {
        AuxNo* auxNo = (AuxNo* ) malloc(sizeof(AuxNo));

        auxNo->codigo = no->chave[indexChave];
        auxNo->posInfo = no->posInfo[indexChave];

        adiciona_Esquerda(noFilhoArrumar, auxNo);
        for (k = filhoJunta->numChaves - 1; k >= 0; k--) {
            auxNo->codigo = filhoJunta->chave[k];
            auxNo->posInfo = filhoJunta->posInfo[k];

            adiciona_Esquerda(noFilhoArrumar, auxNo);
        }

        for(k = 0; k < no->numChaves; k++) {
            if (k >= indexChave) {
                no->posInfo[k] = no->posInfo[k + 1];
                no->chave[k] = no->posInfo[k + 1];
            }

            if (k > indexFilhoArrumar) {
                no->filho[k] = no->filho[k + 1];
            }
        }

        no->posInfo[no->numChaves - 1] = -1;
        no->chave[no->numChaves - 1] = -1;
        no->filho[no->numChaves] = -1;
        no->numChaves--;

        escreve_Indice_arquivo(arquivoIndice, noFilhoArrumar, posFilhoArrumar);

        //exlui filho que foi juntado
        int quebrouAraiz = 0;

        if (posPai == -1 && no->numChaves == 0) {
            quebrouAraiz = 1;
            remover_Indice_Arquivo(arquivoIndice, no, posicao);
        }
        remover_Indice_Arquivo(arquivoIndice, filhoJunta, posFilhoJunta);

        if (quebrouAraiz) {
            return posFilhoArrumar;
        } 
        else {
            return faltaChave(no);
        }
    } 
    else {
        //junta com o da direta
        //desce do pai pro filho
        noFilhoArrumar->posInfo[noFilhoArrumar->numChaves] = no->posInfo[indexChave];
        noFilhoArrumar->chave[noFilhoArrumar->numChaves] = no->chave[indexChave];
        noFilhoArrumar->numChaves++;

        //passa tudo do filho da direta pro da esq;
        for (k = 0; k < filhoJunta->numChaves; k++) {
            noFilhoArrumar->posInfo[noFilhoArrumar->numChaves] = filhoJunta->posInfo[k];
            noFilhoArrumar->chave[noFilhoArrumar->numChaves] = filhoJunta->chave[k];
            noFilhoArrumar->numChaves++;
        }

        for(k = 0; k < no -> numChaves; k++) {
            if (k >= indexChave) {
                no->posInfo[k] = no->posInfo[k + 1];
                no->chave[k] = no->posInfo[k + 1];
            }
            if (k > indexFilhoArrumar) {
                no->filho[k] = no->filho[k + 1];
            }
        }

        no->posInfo[no->numChaves-1] = -1;
        no->chave[no->numChaves-1] = -1;
        no->filho[no->numChaves] = -1;
        no->numChaves--;

        escreve_Indice_arquivo(arquivoIndice, noFilhoArrumar, posFilhoArrumar);
        int quebrouAraiz = 0;

        if (posPai == -1 && no->numChaves == 0) {
            quebrouAraiz = 1;
            remover_Indice_Arquivo(arquivoIndice, no, posicao);
        }
        remover_Indice_Arquivo(arquivoIndice, filhoJunta, posFilhoJunta);
        if (quebrouAraiz) {
            return posFilhoArrumar;
        } 
        else {
            return faltaChave(no);
        }
    }
}

// Remove um determinado elemento da árvore
// Entrada: arquivos e posição e codigo do elemento
// Retorno: nenhum
// Pré-condição: um ponteiro para arquivo e a posição da raiz
// Pós-condição: modifica a árvore
void remove_Produto(FILE* arquivoIndices, FILE* arquivoInfo, int codigo){
    CabecalhoIndices* cab = le_Cabecalho_Indice(arquivoIndices);
    
    int posicao = posicao_Info(arquivoIndices, cab->raiz, codigo);
    
    if(posicao == -1){
        printf ("Codigo inexistente\n");
    }
    else{
        int posRaiz = remove_Arvore(arquivoIndices, arquivoInfo, cab->raiz, codigo, -1, 0);
        free(cab);
        cab = le_Cabecalho_Indice(arquivoIndices);
        cab->raiz = posRaiz;
	
        escreve_cabecalho_Indice(arquivoIndices, cab);
    }
}

// Realiza a leitura do arquivo e altera as informações desejadas
// Entrada: arquivo binário com a árvore e arquivo de leitura
// Retorno: 1 para dizer que não acabou o 0 para End Of File
// Pré-condição: Arquivo binário tem que estar inicializado e posição existentes
// Pós-condição: Arquivo binário modificado
int Atualiza_Produto_Arquivo(FILE* ArvoreProdutos, FILE* ArquivoInfo, FILE* finput){
    char leitura[50], *aux, *aux1, *aux2, *aux3;
    int codigo, flagVirgula;

    if(fscanf(finput,"%[^\n]\n", leitura) == EOF) return 0;

    flagVirgula = 0; //Flag de verificação se é um valor em dinheiro (com virgula)
    aux = (char*) malloc(sizeof(strlen(leitura) + 1)); //Aloca dinamicamente para strtok
    strcpy(aux, leitura); //Copia para o auxiliar
    strtok(aux, ";"); //Lê até encontrar o ';'
    codigo = converte_String_Int(aux); //Sempre lê o código primeiro

    aux2 = strtok(NULL, ";");
    if(strchr(aux2,',') != NULL) flagVirgula = 1; //Verifica se vai manter o estoque
    if(aux2 != 0 && !flagVirgula){
        int estoque;
        estoque = converte_String_Int(aux2);
        altera_Estoque_Arquivo(ArvoreProdutos, ArquivoInfo, codigo, estoque);
    }

    if(flagVirgula) aux3 = aux2;
    else aux3 = strtok(NULL, "\0");
    if(aux3 != 0){
        double valor;
        valor = converte_String_Double(aux3);
        alterar_Valor(ArvoreProdutos, ArquivoInfo, codigo, valor);
    }
    
    free(aux);
    return 1;
}