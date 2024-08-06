// Realiza a leitura mascarada do preço com virgula
// Entrada: Apenas teclado
// Retorno: double mascarado
// Pré-condição: nenhuma
// Pós-condição: nenhuma
double ler_Preco();

// Realiza a leitura mascarada do preço do produto na notação com virgula
// Entrada: arquivo binário e inputs do teclado
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
double le_Preco_Arquivo(FILE* finput);

// Converte uma string em um valor inteiro
// Entrada: string com o número sem casas decimais
// Retorno: valor inteiro
// Pré-condição: A string deve conter apenas números
// Pós-condição: nenhuma
int converte_String_Int(char* source);

// Converte uma string em um valor de dupla ponto flutuante
// Entrada: string com o número
// Retorno: valor inteiro
// Pré-condição: A string deve conter apenas números e uma virgula no máximo, se tiver casas decimais
// Pós-condição: nenhuma
double converte_String_Double(char *source);