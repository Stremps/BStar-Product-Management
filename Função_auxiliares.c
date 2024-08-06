#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Prototipo_auxiliares.h"
#include "Prototipo_comandos.h"
#include "Prototipo_interface.h"
#include "Prototipo_produtos.h"
#include "Prototipo_arquivoBinario.h"

// Realiza a leitura mascarada do preço com virgula
// Entrada: Apenas teclado
// Retorno: double mascarado
// Pré-condição: nenhuma
// Pós-condição: nenhuma
double ler_Preco(){
    int pre, pos;
    double numeroDecimal;
    scanf("%d,%d%*c", &pre, &pos);//Entrada do teclado mascarado

    numeroDecimal = pre;
    numeroDecimal += pos/100.0;

    return numeroDecimal;
}

// Realiza a leitura mascarada do preço do produto na notação com virgula
// Entrada: arquivo binário e inputs do teclado
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
double le_Preco_Arquivo(FILE* finput){
    int pre, pos;
    double numeroDecimal;
    fscanf(finput, "%d,%d%*c", &pre, &pos); //Entrada do teclado mascarado

    numeroDecimal = pre;
    numeroDecimal += pos/100.0;

    return numeroDecimal;
}

// Converte uma string em um valor inteiro
// Entrada: string com o número sem casas decimais
// Retorno: valor inteiro
// Pré-condição: A string deve conter apenas números
// Pós-condição: nenhuma
int converte_String_Int(char* source){
    int aux, valor;

    for(valor = 0; *source; source++){
        valor*=10; //Libera as casas das unidades para inserir novo numero de 1 a 9
        aux = *source - 48; //Converte o número da tabela ASCII
        valor+=aux;
    }

    return valor;
}

// Converte uma string em um valor de dupla ponto flutuante
// Entrada: string com o número
// Retorno: valor inteiro
// Pré-condição: A string deve conter apenas números e uma virgula no máximo, se tiver casas decimais
// Pós-condição: nenhuma
double converte_String_Double(char *source){
    double aux, aux2, valor;
    int i, flagVirgula;

    for(valor = flagVirgula = 0, i = -1; *source; source++){
        if(*source == ',') flagVirgula = 1; //Verifica se já alcançou a virgula
        else if(flagVirgula){ //Realiza a conversão dos valores pós-virgula
            aux2 = pow(10, i);
            aux = (*source - 48)*aux2; //Insere o número decimanl na grandeza adequada
            valor+=aux;
            i--; //Contador
        }
        else{ // Realiza a conversão dos valores pré-virugla
            valor*=10; //Libera as casas das unidades para inserir novo numero de 1 a 9
            aux = *source - 48; //Converte o número da tabela ASCII
            valor+=aux;
        }
    }
    return valor;
}

