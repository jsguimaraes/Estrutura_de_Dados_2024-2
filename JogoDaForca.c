#include <stdio.h>  // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui a biblioteca padrão para funções utilitárias
#include <string.h> // Inclui a biblioteca padrão para manipulação de strings
#include <time.h>   // Inclui a biblioteca padrão para funções relacionadas ao tempo

#define MAX_PALAVRAS 20    // Define o número máximo de palavras no jogo
#define MAX_TAM_PALAVRA 20 // Define o tamanho máximo de cada palavra

// Declaração das funções utilizadas no jogo
void mostrarForca(int erros);
void mostrarPalavra(const char *palavraSecreta, const char *letrasAcertadas, int tamanho);
int avaliarAcertos(const char *palavraSecreta, char *letrasAcertadas, char letra);
void jogar(const char *palavras[]);

// Conjunto de palavras que serão utilizadas no jogo
const char *palavras[MAX_PALAVRAS] = {
    "programacao", "computador", "linguagem", "algoritmo", "variavel",
    "funcao", "codigo", "declaracao", "compilador", "executar",
    "debugar", "desenvolvimento", "software", "hardware", "interface",
    "sistema", "rede", "seguranca", "arvore", "grafo"};

// Função principal que controla o fluxo do jogo
int main()
{
    char jogarNovamente; // Variável para armazenar a resposta do jogador
    do
    {
        jogar(palavras);                           // Chama a função que inicia o jogo
        printf("Deseja jogar novamente? (s/n): "); // Pergunta se o jogador quer jogar novamente
        scanf(" %c", &jogarNovamente);             // Lê a resposta do jogador
    } while (jogarNovamente == 's' || jogarNovamente == 'S'); // Repete o jogo se a resposta for 's' ou 'S'
    return 0;
}

// Função que gerencia uma rodada do jogo
void jogar(const char *palavras[])
{
    srand(time(NULL));                             // Inicializa o gerador de números aleatórios com base no tempo atual
    int indice = rand() % MAX_PALAVRAS;            // Escolhe um índice aleatório para selecionar a palavra
    const char *palavraSecreta = palavras[indice]; // Armazena a palavra secreta selecionada
    int tamanho = strlen(palavraSecreta);          // Calcula o tamanho da palavra secreta

    char letrasAcertadas[MAX_TAM_PALAVRA] = {0}; // Inicializa o vetor de letras acertadas com zeros
    int erros = 0;                               // Inicializa o contador de erros
    int acertos = 0;                             // Inicializa o contador de acertos

    // Loop principal do jogo, que continua até o jogador cometer 6 erros ou acertar todas as letras
    while (erros < 6 && acertos < tamanho)
    {
        mostrarForca(erros);                                      // Mostra a forca com base no número de erros
        mostrarPalavra(palavraSecreta, letrasAcertadas, tamanho); // Mostra a palavra com as letras acertadas

        char letra;                   // Variável para armazenar a letra jogada pelo jogador
        printf("Digite uma letra: "); // Solicita ao jogador uma letra
        scanf(" %c", &letra);         // Lê a letra jogada pelo jogador

        int acertosNaRodada = avaliarAcertos(palavraSecreta, letrasAcertadas, letra); // Avalia se a letra está na palavra secreta
        if (acertosNaRodada > 0)
        {
            acertos += acertosNaRodada;                             // Atualiza o contador de acertos
            printf("Você acertou %d letra(s)!\n", acertosNaRodada); // Informa ao jogador quantas letras ele acertou
        }
        else
        {
            erros++;                                                      // Incrementa o contador de erros
            printf("Letra errada! Você já cometeu %d erro(s).\n", erros); // Informa ao jogador quantos erros ele já cometeu
        }
    }

    // Aqui, mostramos a forca completa e a mensagem de fim de jogo
    mostrarForca(erros); // Mostra a forca com base no número de erros
    if (erros >= 6)
    {
        printf("GAME OVER! A palavra era: %s\n", palavraSecreta); // Informa que o jogador perdeu e mostra a palavra secreta
    }
    else
    {
        printf("You WIN! A palavra era: %s\n", palavraSecreta); // Informa que o jogador ganhou e mostra a palavra secreta
    }
}

// Função que mostra a forca com base no número de erros
void mostrarForca(int erros)
{
    printf("\n");
    switch (erros)
    {
    case 0:
        printf("  _____  \n");
        printf("  |     | \n");
        printf("        \n");
        printf("        \n");
        printf("        \n");
        printf("        \n");
        break;
    case 1:
        printf("  _____  \n");
        printf("  |     | \n");
        printf("  O     \n");
        printf("        \n");
        printf("        \n");
        printf("        \n");
        break;
    case 2:
        printf("  _____  \n");
        printf("  |     | \n");
        printf("  O     \n");
        printf("  |     \n");
        printf("        \n");
        printf("        \n");
        break;
    case 3:
        printf("  _____  \n");
        printf("  |     | \n");
        printf("  O     \n");
        printf(" /|     \n");
        printf("        \n");
        printf("        \n");
        break;
    case 4:
        printf("  _____  \n");
        printf("  |     | \n");
        printf("  O     \n");
        printf(" /|\\    \n");
        printf("        \n");
        printf("        \n");
        break;
    case 5:
        printf("  _____  \n");
        printf("  |     | \n");
        printf("  O     \n");
        printf(" /|\\    \n");
        printf(" /      \n");
        printf("        \n");
        break;
    case 6:
        printf("  _____  \n");
        printf("  |     | \n");
        printf("  O     \n");
        printf(" /|\\    \n");
        printf(" / \\    \n");
        printf("        \n");
        break;
    default:
        break;
    }
}

// Função que mostra a palavra secreta com as letras acertadas e traços para as letras não acertadas
void mostrarPalavra(const char *palavraSecreta, const char *letrasAcertadas, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (letrasAcertadas[i] != '\0')
        {                                      // Verifica se a letra foi acertada
            printf("%c ", letrasAcertadas[i]); // Mostra a letra acertada
        }
        else
        {
            printf("_ "); // Mostra um traço para a letra não acertada
        }
    }
    printf("\n");
}

// Função que avalia se a letra jogada está na palavra secreta
int avaliarAcertos(const char *palavraSecreta, char *letrasAcertadas, char letra)
{
    int acertos = 0; // Inicializa o contador de acertos
    for (int i = 0; i < strlen(palavraSecreta); i++)
    {
        if (palavraSecreta[i] == letra)
        {                               // Verifica se a letra está na posição atual da palavra secreta
            letrasAcertadas[i] = letra; // Atualiza letras acertadas
            acertos++;                  // Incrementa o contador de acertos
        }
    }
    return acertos; // Retorna o número de acertos
}
