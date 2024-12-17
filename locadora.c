#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elemento
{
    char placa[10];
    char modelo[20];
    float valor_locacao;
    struct Elemento *prox;
    struct Elemento *ant;
    void *cliente; // ponteiro para cliente que realizou a locação
} Elemento;

typedef struct Lista
{
    Elemento *inicio;
    Elemento *fim;
    int tamanho;
} Lista;

void adicionarFim(Lista *l, Elemento *e)
{
    e->prox = NULL;
    if (l->fim == NULL)
    { // Lista vazia
        e->ant = NULL;
        l->inicio = l->fim = e;
    }
    else
    {
        e->ant = l->fim;
        l->fim->prox = e;
        l->fim = e;
    }
    l->tamanho++;
}

void adicionarInicio(Lista *l, Elemento *e)
{
    e->ant = NULL;
    if (l->inicio == NULL)
    { // Lista vazia
        e->prox = NULL;
        l->inicio = l->fim = e;
    }
    else
    {
        e->prox = l->inicio;
        l->inicio->ant = e;
        l->inicio = e;
    }
    l->tamanho++;
}

int adicionarPosicao(Lista *l, Elemento *e, int pos)
{
    if (pos < 0 || pos > l->tamanho)
    {
        return 0; // Posição inválida
    }
    if (pos == 0)
    {
        adicionarInicio(l, e);
        return 1;
    }
    if (pos == l->tamanho)
    {
        adicionarFim(l, e);
        return 1;
    }
    Elemento *atual = l->inicio;
    for (int i = 0; i < pos; i++)
    {
        atual = atual->prox;
    }
    e->prox = atual;
    e->ant = atual->ant;
    atual->ant->prox = e;
    atual->ant = e;
    l->tamanho++;
    return 1;
}

Elemento *removerInicio(Lista *l)
{
    if (l->inicio == NULL)
    {
        return NULL; // Lista vazia
    }
    Elemento *remover = l->inicio;
    l->inicio = l->inicio->prox;
    if (l->inicio == NULL)
    {
        l->fim = NULL;
    }
    else
    {
        l->inicio->ant = NULL;
    }
    l->tamanho--;
    return remover;
}

Elemento *removerFim(Lista *l)
{
    if (l->fim == NULL)
    {
        return NULL; // Lista vazia
    }
    Elemento *remover = l->fim;
    l->fim = l->fim->ant;
    if (l->fim == NULL)
    {
        l->inicio = NULL;
    }
    else
    {
        l->fim->prox = NULL;
    }
    l->tamanho--;
    return remover;
}

Elemento *removerPosicao(Lista *l, int pos)
{
    if (pos < 0 || pos >= l->tamanho || l->inicio == NULL)
    {
        return NULL; // Posição inválida ou lista vazia
    }
    if (pos == 0)
    {
        return removerInicio(l);
    }
    if (pos == l->tamanho - 1)
    {
        return removerFim(l);
    }
    Elemento *atual = l->inicio;
    for (int i = 0; i < pos; i++)
    {
        atual = atual->prox;
    }
    atual->ant->prox = atual->prox;
    atual->prox->ant = atual->ant;
    l->tamanho--;
    return atual;
}

int buscarElemento(Lista *l, char modelo[])
{
    Elemento *atual = l->inicio;
    int pos = 0;
    while (atual != NULL)
    {
        if (strcmp(atual->modelo, modelo) == 0)
        {
            return pos;
        }
        atual = atual->prox;
        pos++;
    }
    return -1; // Elemento não encontrado
}

int quantidadeElementos(Lista *l)
{
    return l->tamanho;
}

void mostrarLista(Lista *l)
{
    Elemento *atual = l->inicio;
    while (atual != NULL)
    {
        printf("Placa: %s, Modelo: %s, Valor de Locação: %.2f\n", atual->placa, atual->modelo, atual->valor_locacao);
        atual = atual->prox;
    }
}

void apagarElemento(Elemento *e)
{
    free(e);
}

//parte 2

int menu()
{
    int opcao;
    printf("1 - Inserir um Elemento no Inicio:\n");
    printf("2 - Inserir um Elemento no Fim:\n");
    printf("3 - Inserir um Elemento na Posição:\n");
    printf("4 - Remover um Elemento no Inicio:\n");
    printf("5 - Remover um Elemento no Fim:\n");
    printf("6 - Remover um Elemento na Posição:\n");
    printf("7 - Mostrar Lista:\n");
    printf("8 - Apagar um Elemento da Lista:\n");
    printf("9 - Apagar a Lista:\n");
    printf("0 - Fim do Programa - Lista de Chamada:\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}


//parte 3

typedef struct Cliente
{
    char nome[50];
    char cpf[15];
} Cliente;

Lista listaLivres;
Lista listaLocados;

void inicializarListas()
{
    listaLivres.inicio = listaLivres.fim = NULL;
    listaLivres.tamanho = 0;
    listaLocados.inicio = listaLocados.fim = NULL;
    listaLocados.tamanho = 0;
}

// Funções específicas para a locadora (alugar e devolver carros)
void alugarCarro()
{
    // Mostrar todos os carros livres para locação
    mostrarLista(&listaLivres);

    // Selecionar carro e cliente para locação
    char placa[10];
    printf("Digite a placa do carro que deseja alugar: ");
    scanf("%s", placa);

    Elemento *carro = removerPosicao(&listaLivres, buscarElemento(&listaLivres, placa));
    if (carro == NULL)
    {
        printf("Carro não encontrado!\n");
        return;
    }

    Cliente *cliente = (Cliente *)malloc(sizeof(Cliente));
    printf("Digite o nome do cliente: ");
    scanf("%s", cliente->nome);
    printf("Digite o CPF do cliente: ");
    scanf("%s", cliente->cpf);

    carro->cliente = cliente;

    adicionarFim(&listaLocados, carro);
    printf("Carro alugado com sucesso!\n");
}

void devolverCarro()
{
    // Mostrar lista de carros locados
    mostrarLista(&listaLocados);

    // Selecionar carro pela placa e devolver
    char placa[10];
    printf("Digite a placa do carro que deseja devolver: ");
    scanf("%s", placa);

    Elemento *carro = removerPosicao(&listaLocados, buscarElemento(&listaLocados, placa));
    if (carro == NULL)
    {
        printf("Carro não encontrado!\n");
        return;
    }

    Cliente *cliente = (Cliente *)carro->cliente;
    printf("Valor a pagar pela locação: %.2f\n", carro->valor_locacao);
    free(cliente);
    carro->cliente = NULL;

    adicionarFim(&listaLivres, carro);
    printf("Carro devolvido com sucesso!\n");
}

int main()
{
    inicializarListas();

    // Adicionar 5 carros livres e 2 clientes para locação
    for (int i = 0; i < 5; i++)
    {
        Elemento *e = (Elemento *)malloc(sizeof(Elemento));
        sprintf(e->placa, "ABC%d", i);
        sprintf(e->modelo, "Modelo%d", i);
        e->valor_locacao = 100.0 + i * 10;
        e->cliente = NULL;
        adicionarFim(&listaLivres, e);
    }

    int opcao;
    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
        {
            Elemento *e = (Elemento *)malloc(sizeof(Elemento));
            printf("Digite a placa: ");
            scanf("%s", e->placa);
            printf("Digite o modelo: ");
            scanf("%s", e->modelo);
            printf("Digite o valor de locação: ");
            scanf("%f", &e->valor_locacao);
            e->cliente = NULL;
            adicionarInicio(&listaLivres, e);
            break;
        }
        case 2:
        {
            Elemento *e = (Elemento *)malloc(sizeof(Elemento));
            printf("Digite a placa: ");
            scanf("%s", e->placa);
            printf("Digite o modelo: ");
            scanf("%s", e->modelo);
            printf("Digite o valor de locação: ");
            scanf("%f", &e->valor_locacao);
            e->cliente = NULL;
            adicionarFim(&listaLivres, e);
            break;
        }
        case 3:
        {
            Elemento *e = (Elemento *)malloc(sizeof(Elemento));
            printf("Digite a placa: ");
            scanf("%s", e->placa);
            printf("Digite o modelo: ");
            scanf("%s", e->modelo);
            printf("Digite o valor de locação: ");
            scanf("%f", &e->valor_locacao);
            e->cliente = NULL;
            int pos;
            printf("Digite a posição: ");
            scanf("%d", &pos);
            if (!adicionarPosicao(&listaLivres, e, pos))
            {
                printf("Posição inválida!\n");
                free(e);
            }
            break;
        }
        case 4:
        {
            Elemento *e = removerInicio(&listaLivres);
            if (e != NULL)
            {
                printf("Elemento removido: %s\n", e->modelo);
                apagarElemento(e);
            }
            else
            {
                printf("Lista vazia!\n");
            }
            break;
        }
        case 5:
        {
            Elemento *e = removerFim(&listaLivres);
            if (e != NULL)
            {
                printf("Elemento removido: %s\n", e->modelo);
                apagarElemento(e);
            }
            else
            {
                printf("Lista vazia!\n");
            }
            break;
        }
        case 6:
        {
            int pos;
            printf("Digite a posição: ");
            scanf("%d", &pos);
            Elemento *e = removerPosicao(&listaLivres, pos);
            if (e != NULL)
            {
                printf("Elemento removido: %s\n", e->modelo);
                apagarElemento(e);
            }
            else
            {
                printf("Posição inválida ou lista vazia!\n");
            }
            break;
        }
        case 7:
        {
            mostrarLista(&listaLivres);
            break;
        }
        case 8:
        {
            char modelo[20];
            printf("Digite o modelo do elemento a apagar: ");
            scanf("%s", modelo);
            int pos = buscarElemento(&listaLivres, modelo);
            if (pos != -1)
            {
                Elemento *e = removerPosicao(&listaLivres, pos);
                if (e != NULL)
                {
                    apagarElemento(e);
                    printf("Elemento apagado!\n");
                }
            }
            else
            {
                printf("Elemento não encontrado!\n");
            }
            break;
        }
        case 9:
        {
            while (listaLivres.inicio != NULL)
            {
                Elemento *e = removerInicio(&listaLivres);
                apagarElemento(e);
            }
            printf("Lista apagada!\n");
            break;
        }
        case 0:
        {
            printf("Fim do programa!\n");
            break;
        }
        default:
        {
            printf("Opção inválida!\n");
            break;
        }
        }
    } while (opcao != 0);

    return 0;
}
