#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Prototipo_produtos.h"
#include "Prototipo_arquivoBinario.h"
#include "Prototipo_auxiliares.h"
#include "Prototipo_comandos.h"
#include "Prototipo_interface.h"

// Configura a inicialização do arquivo binário
// Entrada: resposta da inicilização e ponteiro do arquivo aberto
// Retorno: nenhum
// Pré-condição: Repostar o questionário do inicializa programa
// Pós-condição: nenhuma
void inicializa_ArquivoBinario(char ArquivoBinario, FILE** ArvoreIndices, FILE** ArvoreInfo){
    char operacao[5];

    if(ArquivoBinario == 'N' || ArquivoBinario == 'n') strcpy(operacao, "w+b"); //Se não deseja ler, ou deseja iniciar novo, arquivo binário
    else strcpy(operacao, "r+b"); //Se sim, utiliza a operação de ler

    *ArvoreInfo = fopen("ProdutosDados.bin", operacao);
    *ArvoreIndices = fopen("ProdutosIndice.bin", operacao); //Realiza a operação
    
    if(ArquivoBinario == 'N' || ArquivoBinario == 'n'){ //Caso novo, inicializa novo cabeçalho
        cria_arquivo_Indice(*ArvoreIndices);
        cria_arquivo_Info(*ArvoreInfo);
    }
}

// Realiza a incialização do cabeçalho do arquivo
// Entrada: Arquivo binário
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário incializado
void cria_arquivo_Indice(FILE* arquivo){
    CabecalhoIndices * cab = (CabecalhoIndices*) malloc(sizeof(CabecalhoIndices)); //Aloca cabeçalho temporario
    cab->raiz = -1; //Inicializa fatores
    cab->livre = -1;
    cab->topo = 0;
    escreve_cabecalho_Indice(arquivo, cab); //Escreve arquivo
    free(cab); //Libera temporário
}

// Realiza a incialização do cabeçalho do arquivo
// Entrada: Arquivo binário
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário incializado
void cria_arquivo_Info(FILE* arquivo){
    CabecalhoInfo* cab = (CabecalhoInfo*) malloc(sizeof(CabecalhoInfo));
    cab->posLivre = -1;
    cab->posTopo = 0;
    escreve_cabecalho_Info(arquivo, cab);
    free(cab);
}

// Realiza a modificação do cabecalho
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário modificado
void escreve_cabecalho_Info(FILE* arquivo, CabecalhoInfo* cabecalho){
    fseek(arquivo, 0, SEEK_SET);
    fwrite(cabecalho, sizeof(CabecalhoInfo), 1, arquivo);
}

// Realiza a modificação do cabecalho
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário modificado
void escreve_cabecalho_Indice(FILE* arquivo, CabecalhoIndices* cabecalho){
    fseek(arquivo, 0, SEEK_SET);
    fwrite(cabecalho, sizeof(CabecalhoIndices), 1, arquivo);
}

// Cria uma cópia de uma chave de indices
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: Posição tem que estar preenchida
// Pós-condição: nenhuma
ArvoreB* le_Indice_arquivo(FILE* arquivo, int posicao){
    ArvoreB* x = (ArvoreB*) malloc(sizeof(ArvoreB));
    fseek(arquivo, 0, SEEK_SET);	// posiciona no início do arquivo
    fseek(arquivo, sizeof(CabecalhoIndices) + posicao* sizeof(ArvoreB), SEEK_SET);
    fread(x, sizeof(ArvoreB), 1, arquivo);
    return x;
}

// Escreve em cima de uma chave de arquivos
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário modificado
void escreve_Indice_arquivo(FILE* arquivo, ArvoreB* no, int posicao){
    fseek(arquivo, 0, SEEK_SET); //posiciona no inicio do arquivo
    fseek(arquivo, sizeof(CabecalhoIndices) + posicao * sizeof(ArvoreB), SEEK_SET);
    fwrite(no, sizeof(ArvoreB), 1, arquivo);
}

// Cria uma cópia do cabeçalho de indices
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: endereço com cópia do arquivo
// Pré-condição: Posição tem que estar preenchida
// Pós-condição: nenhuma
CabecalhoIndices* le_Cabecalho_Indice(FILE* arquivo){
    CabecalhoIndices* cabecalho = (CabecalhoIndices*) malloc(sizeof(CabecalhoIndices));
    fseek(arquivo, 0, SEEK_SET);	// posiciona no in ́ıcio do arquivo
    fread(cabecalho, sizeof(CabecalhoIndices), 1, arquivo);
    return cabecalho;
}

// Verifica para inserção no arquivo de indices
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: Posição tem que estar preenchida
// Pós-condição: arquivo binário modificados
int insere_Indice_arquivo(FILE* arquivo, ArvoreB* no, int posicao){
    int pos_escrita;
    if(posicao==-1){ // Vai na posição livre
        CabecalhoIndices* cab = le_Cabecalho_Indice(arquivo);
        if(cab->livre==-1){ // Escrever no topo do arquivo
            escreve_Indice_arquivo(arquivo, no, cab->topo);
            pos_escrita = cab->topo;
            cab->topo++;
        }

        else{ // Se não, escreve na posição livre
            int pos_aux;

            ArvoreB* aux = le_Indice_arquivo(arquivo, cab->livre); // Ler cabeça dos livres
            pos_aux = cab->livre;
            cab->livre = aux->filho[0];
            
            escreve_Indice_arquivo(arquivo, no, pos_aux);
            pos_escrita = pos_aux;

            free(aux);
        }
        escreve_cabecalho_Indice(arquivo, cab);
        free(cab);
    }
    else{ // Se não, escreve na posição escolhida
        escreve_Indice_arquivo(arquivo, no, posicao);
        pos_escrita = posicao;
    }
    return pos_escrita;
}

// Escreve os dados de um produto em determinada posição do arquivo
// Entrada: Arquivo, nó desejado e posiçãi
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto, uma posição e um produto 
// Pós-condição: os dados do produto serão escritos no arquivo
void escreve_Produto_Arquivo(FILE* arquivo, Produtos* no, int posicao){
    fseek(arquivo, 0, SEEK_SET);
    fseek(arquivo, sizeof(CabecalhoInfo) + posicao * sizeof(Produtos), SEEK_SET);
    fwrite(no, sizeof(Produtos), 1, arquivo);
}

// Lê os dados de um produto em determinada posição do arquivo
// Entrada: Arquivo e posição
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto, uma posição
// Pós-condição: retornará um produto com os dados lidos do arquivo
Produtos* le_Produto_arquivo(FILE* arquivo, int posicao){
    Produtos* x = (Produtos*) malloc(sizeof(Produtos));
    fseek(arquivo, 0, SEEK_SET);	
    fseek(arquivo, sizeof(CabecalhoInfo) + posicao * sizeof(Produtos), SEEK_SET);
    fread(x, sizeof(Produtos), 1, arquivo);
    return x;
}

// Lê o cabeçalho do arquivo de dados
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: Cabeçalho produto
// Pré-condição: ter um arquivo aberto
// Pós-condição: retornará o cabecalho do arquivo de dados
CabecalhoInfo* le_Cabecalho_Produto(FILE* arquivo){
    CabecalhoInfo* cabecalho = (CabecalhoInfo*) malloc(sizeof(CabecalhoInfo));
    fseek(arquivo, 0, SEEK_SET);
    fread(cabecalho, sizeof(CabecalhoInfo), 1, arquivo);
    return cabecalho;
}

// Escreve o cabeçalho do arquivo de dados
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto e os dados do cabeçalho
// Pós-condição: os dados do cabeçalho serão escritos no arquivo
void escreve_cabecalho_Produto(FILE* arquivo, CabecalhoInfo* cabecalho){
    fseek(arquivo, 0, SEEK_SET);
    fwrite(cabecalho, sizeof(CabecalhoInfo), 1, arquivo); 
}

// Remove produto do arquivo binário
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto e os dados do cabeçalho
// Pós-condição: os dados são escritos no arquivo
void remover_Produto(FILE* arquivo, int posicao){
    Produtos *produto = le_Produto_arquivo(arquivo, posicao);
    CabecalhoInfo *cabecalho = le_Cabecalho_Produto(arquivo);

    produto->codigo = cabecalho->posLivre;
    cabecalho->posLivre = posicao;

    escreve_cabecalho_Produto(arquivo, cabecalho);
    escreve_Produto_Arquivo(arquivo, produto, posicao);
    free(produto);
    free(cabecalho);

}

// Modifica a remoção no cabeçalho
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: ter um arquivo aberto e os dados do cabeçalho
// Pós-condição: modifica o cabeçalho
void remover_Indice_Arquivo(FILE* arquivo, ArvoreB* no, int posicao){
    CabecalhoIndices* cabecalho = le_Cabecalho_Indice(arquivo);

    no->numChaves = cabecalho->livre;
    cabecalho->livre = posicao;

    escreve_Indice_arquivo(arquivo, no, posicao);
    escreve_cabecalho_Indice(arquivo, cabecalho);
}