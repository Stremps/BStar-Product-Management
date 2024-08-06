#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Prototipo_auxiliares.h"
#include "Prototipo_comandos.h"
#include "Prototipo_interface.h"
#include "Prototipo_produtos.h"
#include "Prototipo_arquivoBinario.h"

int main(){
    char AbrirArquivo;
    int escolha;
    FILE *ArvoreProdutos, *ArvoreInfo;

    inicializa_Programa(&AbrirArquivo);
    inicializa_ArquivoBinario(AbrirArquivo, &ArvoreProdutos, &ArvoreInfo);

    while(1){
        quebra_Pagina();
        apreseta_Menu();
        scanf("%d%*c", &escolha);

        if(escolha ==  1){ //Escolha que guia para o menu de manter produtos
            menu_produtos(ArvoreProdutos, ArvoreInfo);
        }
        if(escolha == 2){ //Escolha que guia para o menu de imprimir produtos
            menu_Imprimir(ArvoreProdutos, ArvoreInfo);
        }
        if(escolha == 3){ //Escolha que guia para a leitura em lote
            menu_Leitura_Lote(ArvoreProdutos, ArvoreInfo);
        }
        if(escolha == 4) //Fecha programa
            break;
    }

    fclose(ArvoreProdutos);
    fclose(ArvoreInfo);
    return 0;
}