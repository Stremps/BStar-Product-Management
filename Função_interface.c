#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Prototipo_auxiliares.h"
#include "Prototipo_comandos.h"
#include "Prototipo_interface.h"
#include "Prototipo_produtos.h"
#include "Prototipo_arquivoBinario.h"

// Realiza a leitura do sistema operacional do compilador
// Entrada: ponteiro sobre inicialização do programa
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: sistema operacional salvo
void inicializa_Programa(char* ArquivoBinario){
    char confirma;

    while(1){ //Parte muito importante para o usuário não realizar algum erro inversível!
        quebra_Pagina();
        printf("Deseja carregar o arquivo binario? (S\\N):\n"); //Se não quiser carregar, cria novos arquivos
        scanf("%c%*c", ArquivoBinario);
        if(*ArquivoBinario == 'n' || *ArquivoBinario == 'N'){
            printf("Ira perder tudo se ja tem algo salvo. Tem certeza disso?(S\\N):\n");
            scanf("%c%*c", &confirma);
            if(confirma == 'S' || confirma == 's') break;
        }
        else break;
    }
}

// Realiza a quebra de pagina dependendo do sistema operacional do compilador
// Entrada: nenhum
// Retorno: quebra de página
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void quebra_Pagina(){
    #ifdef __linux__ //Para caso seja em um compilador Linux
        system("clear");
    #elif _WIN32 //Para caso seja em um compilador windows 32 bits
        system("cls");
    #elif _WIN64 //Para caso seja em um compilador windows 64 bits
        system("cls");
    #else //Se não nada

    #endif
}

// Apresenta na tela as opções principais do menu do programa
// Entrada: nenhum
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void apreseta_Menu(){
    printf(" == MENU PRINCIPAL ==\n\n");
    printf("1 - Manter produtos\n");
    printf("2 - Imprimir informacoes\n");
    printf("3 - Ler em lote\n");
    printf("4 - Fechar programa\n");
    printf("\n\n\n\n>");
}

// Apresenta as opções de manter produtos
// Entrada: nenhum
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void apreseta_Manter(){
    printf(" == MENU PRODUTOS ==\n\n");
    printf("1 - Cadastrar produto(s)\n");
    printf("2 - Remover produto(s)\n");
    printf("3 - Atualizar produto(s)\n");
    printf("4 - Voltar para o menu\n");
    printf("\n\n\n\n>");
}

// Apresenta as opções de imprimir do programa
// Entrada: nenhum
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void apresenta_Imprimir(){
    printf(" == MENU IMPRIMIR ==\n\n");
    printf("1 - Imprimir informacoes de um produto\n");
    printf("2 - Imprimir lista de produtos (in-ordem)\n");
    printf("3 - Imprimir arvore B*\n");
    printf("4 - Imprimir lista de nos livres\n");
    printf("5 - Voltar para o menu\n");
    printf("\n\n\n>");
}

// Função auxiliar para obter altura da árvore
// Entrada: arquivo e posição
// Retorno: altura
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int altura_Arvore(FILE* ArvoreProduto, int posicao){
    if(posicao == -1)
        return 0;
    
    ArvoreB* no = le_Indice_arquivo(ArvoreProduto, posicao);
    
    if(ehFolha(no))
        return 1;
    else
        return 1 + altura_Arvore(ArvoreProduto, no->filho[0]);
}

// Imprime por nível as informações
// Entrada: arquivo e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprime_Nivel(FILE* ArvoreProduto, int posicao, int nivel, int nivelAtual){
    if(posicao == -1) return;
    
    ArvoreB* no = le_Indice_arquivo(ArvoreProduto, posicao);
    int i;

    if(nivel == nivelAtual && no->numChaves != 0){ //Verifica se está imprimindo corretamente
        printf("[");
        for(i = 0; i < no->numChaves; i++){
            if(no->chave[i] != -1)
                printf("%d", no->chave[i]);
            if(i < no->numChaves - 1)
                printf(",");
        }
        printf("] ");
    }
    
    for(i = 0; i <= no->numChaves; i++)
        imprime_Nivel(ArvoreProduto, no->filho[i], nivel, nivelAtual + 1);
}

// Faz a passagem pelas chaves e níveis
// Entrada: arquivo, nivel e nivel atual e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimirArvore_Nivel(FILE* ArvoreProdutos){
    CabecalhoIndices* cabecalho = le_Cabecalho_Indice(ArvoreProdutos);
    int i, altura = altura_Arvore(ArvoreProdutos, cabecalho->raiz);
    
    for(i = 1; i <= altura + 1; i++){
        imprime_Nivel(ArvoreProdutos, cabecalho->raiz, i, 1);
        printf("\n");
    }
}

// Faz a passagem pelas chaves e níveis
// Entrada: arquivo, nivel e nivel atual e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_Info(FILE* arquivo, int posicao){
    Produtos* info = le_Produto_arquivo(arquivo, posicao);
    
    printf("Código: %04d == Nome: %s\n", info->codigo, info->nome);
    
    free(info);
}

// Imprime os produtos pela ordem da chave
// Entrada: arquivos e posição
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_inOrdem(FILE* ArvoreProduto, FILE* ArquivoInfo, int posicao){
    CabecalhoIndices* cab = le_Cabecalho_Indice(ArvoreProduto);
    
    if (posicao == -1) return; //Break point
    else{
        int i;
        ArvoreB* no = le_Indice_arquivo(ArvoreProduto, posicao);
        for(i = 0 ; i < no->numChaves; i++){
            imprimir_inOrdem(ArvoreProduto, ArquivoInfo, no->filho[i]);
            imprimir_Info(ArquivoInfo, no->posInfo[i]); 
        }
        imprimir_inOrdem(ArvoreProduto, ArquivoInfo, no->filho[no->numChaves]); 
    }
}

// Imprime a todas as informação de um produto a partir da sua posição
// Entrada: arquivos
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_Produto(FILE* ArvoreProdutos, FILE* ArvoreInfo){
    int codigo, posicao = -1;
    CabecalhoIndices *cabecalho = le_Cabecalho_Indice(ArvoreProdutos);
    printf("Insira o código do produto desejado:\n>");

    scanf("%d%*c", &codigo);
    posicao = posicao_Info(ArvoreProdutos, cabecalho->raiz, codigo);

    if(posicao != -1){
        Produtos* aux = le_Produto_arquivo(ArvoreInfo, posicao);

        printf ("\n------ PRODUTO ------\n");
        printf ("Codigo: %d |  Nome: %s\n", aux->codigo, aux->nome);
        printf ("Marca: %s  | Categoria: %s\n", aux->marca, aux->categoria);
        printf ("Estoque: %d\n", aux->estoque);
        printf ("Preco: R$ %.2lf\n", aux->valor);
        printf ("---------------------\n");
    }
    else{
        printf("Produto não existe!\n");
    }
}

// Imprime a lista de posções livres no arquivo de indice
// Entrada: arquivo
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_Livres_Info(FILE* Arquivo){
    CabecalhoInfo * cab = le_Cabecalho_Produto(Arquivo);
    int posicao = cab->posLivre;
    if(posicao == -1) printf("Não há livres\n\n");
    
    while(posicao != -1){
        Produtos* aux = le_Produto_arquivo(Arquivo, posicao);
        printf("%d\n", posicao);
        posicao = aux->codigo;
        free(aux);
    }
    printf("\n\n");
    free(cab);
}

// Imprime a lista de posções livres no arquivo de indice
// Entrada: arquivo
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_Livres_Indices(FILE* arquivo){
    CabecalhoIndices* cab = le_Cabecalho_Indice(arquivo);
    int posicao = cab->livre;
    
    if(posicao == -1) printf("Não há livres\n\n");
    
    while(posicao != -1){
        ArvoreB* aux = le_Indice_arquivo(arquivo, posicao);
        printf("%d\n", posicao);
        posicao = aux->numChaves;
    }
}