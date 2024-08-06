#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Prototipo_auxiliares.h"
#include "Prototipo_comandos.h"
#include "Prototipo_interface.h"
#include "Prototipo_produtos.h"
#include "Prototipo_arquivoBinario.h"

// Realiza as opções selecionadas pelo úsuario do menu produtos
// Entrada: Uma das 5 opções apresentadas na tela
// Retorno: quebra de página
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void menu_produtos(FILE* ArvoreProdutos, FILE* ArvoreInfo){
    int escolha;

    while(1){
        quebra_Pagina();
        apreseta_Manter();
        scanf("%d%*c", &escolha);
        
        if(escolha == 1){ // Cadastrar produto
            quebra_Pagina();
            cadastra_Produto_Individual(ArvoreProdutos, ArvoreInfo);

            printf("Aperte ENTER para continuar...");
            scanf("%*c"); //Para que o úsuario possa ler a confirmação de cadastro ou mensagem de erro
        }
        else if(escolha == 2){ // Remover Produto
            quebra_Pagina();
            remove_Produto_Individual(ArvoreProdutos, ArvoreInfo);
            printf("Aperte ENTER para continuar...");
            scanf("%*c"); //Para que o úsuario possa ler a confirmação de cadastro ou mensagem de erro
        }
        else if(escolha == 3){ // Atualizar produtos
            atualiza_Produto(ArvoreProdutos, ArvoreInfo);
            printf("Aperte ENTER para continuar...");
            scanf("%*c"); //Para que o úsuario possa ler a confirmação de cadastro ou mensagem de erro
        }
        else if(escolha == 4) //Voltar para o menu
            break;
    }
}

// Realiza as opções selecionadas pelo úsuario do menu de imprimir
// Entrada: Uma das 4 opções apresentadas na tela
// Retorno: quebra de página
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void menu_Imprimir(FILE* ArvoreProdutos, FILE* ArvoreInfo){
    int escolha;

    while(1){
        quebra_Pagina();
        apresenta_Imprimir();
        scanf("%d%*c", &escolha);

        if(escolha == 1){ //Imprimir informações de um produto
            imprimir_Produto(ArvoreProdutos, ArvoreInfo);
            printf("Aperte ENTER para continuar.");
            scanf("%*c");
        }
        else if(escolha == 2){ //Imprimir lista de produtos (in-ordem);
            CabecalhoIndices* cabecalho = le_Cabecalho_Indice(ArvoreProdutos);
            imprimir_inOrdem(ArvoreProdutos, ArvoreInfo, cabecalho->raiz); 
            printf("Aperte ENTER para continuar.");
            scanf("%*c");
        }
	    else if(escolha == 3){ //Imprimir árvore B*
            imprimirArvore_Nivel(ArvoreProdutos);
            printf("Aperte ENTER para continuar.");
            scanf("%*c");
        }
        else if(escolha == 4){ //Imprimir lista de nós livres
            printf("Posições livres do arquivo de Info: \n");
            imprimir_Livres_Info(ArvoreInfo);

            printf("Posições livres do arquivo de Indices: \n");
            imprimir_Livres_Indices(ArvoreProdutos);
            
            printf("Aperte ENTER para continuar.");
            scanf("%*c");
        }
        else if(escolha == 5) //Voltar para o menu
            break;
    }
}

// Realiza a operação de leitura em Lote, do arquivo desejado pelo usuário
// Entrada: Arquivo binário e nome do arquivo
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void menu_Leitura_Lote(FILE* ArvoreProdutos, FILE* ArvoreInfo){
    quebra_Pagina();

    char nomeArq[50];
    FILE* finput;

    printf("Escreva o diretorio do arquivo:\n>");
    scanf("%[^\n]%*c", nomeArq);

    finput = fopen(nomeArq, "r");

    if(finput == NULL) printf("Diretorio de arquivo invalido!\n");
    else{
        char comando[5];
        while(fscanf(finput, "%[^;];", comando) != EOF){
            
            if(!strcmp(comando, "I")){ //Operação de inserção
                Le_Produto_Arquivo(ArvoreProdutos, ArvoreInfo, finput);
            }
            else if(!strcmp(comando, "A")){ //Operação de atualização
                Atualiza_Produto_Arquivo(ArvoreProdutos, ArvoreInfo, finput);
            }
            else if(!strcmp(comando, "R")){ //Operação de remoção
                int codigo;
                fscanf(finput, "%d\n", &codigo);
                remove_Produto(ArvoreProdutos, ArvoreInfo, codigo);
            }
    
            }
        printf("Leitura realizada com sucesso!\n");
    }
    printf("Aperte ENTER para continuar.");
    scanf("%*c");
}