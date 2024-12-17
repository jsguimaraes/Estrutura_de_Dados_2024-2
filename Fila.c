#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente
{ // dados do cliente bancário
    char nome[20];
    int operacao; // 1 - saque, 2 - depósito, 0 - atendimento com gerente
    float valor;
    int id;
    struct cliente *proximo;
} Cliente;

typedef struct fila
{                    // atributos de Fila
    Cliente *inicio; // inicio
    Cliente *fim;
    int qtd;
} Fila;

Fila *criaFila()
{
    Fila *fl = (Fila *)malloc(sizeof(Fila));
    fl->inicio = NULL; // inicialização da fila
    fl->fim = NULL;
    fl->qtd = 0;
    return fl;
}

Cliente *cadastraNovoCliente(char nome[], int op, float vl, int id)
{
    Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
    strcpy(novo->nome, nome);
    novo->operacao = op;
    novo->valor = vl;
    novo->proximo = NULL;
    novo->id = id;
    return novo;
}

void enfileirar(Fila *fl, Cliente *cl)
{
    if (fl->inicio == NULL)
    { // Fila Vazia
        fl->inicio = cl;
    }
    else
    { // Fila com elementos
        fl->fim->proximo = cl;
    }
    cl->proximo = NULL;
    fl->fim = cl;
    fl->qtd++;
}

Cliente *desenfileirar(Fila *fl)
{
    Cliente *aux = fl->inicio;
    if (aux == NULL)
    { // Fila vazia
        printf("\nErro - Fila Vazia\n");
    }
    else
    { // Lista com elementos
        fl->inicio = aux->proximo;
        fl->qtd--;
        aux->proximo = NULL;
        if (fl->inicio == NULL)
        {
            fl->fim = NULL;
        }
    }
    return aux;
}

void mostraCliente(Cliente cl)
{
    printf("\n Id:%d \n\t Nome: %s \n\t Operacao %d \n\t Valor=%.2f \n", cl.id, cl.nome, cl.operacao, cl.valor);
}

void mostraFila(Fila *fl)
{
    printf("\nInício da Fila\n");
    Cliente *aux = fl->inicio;
    while (aux != NULL)
    {
        mostraCliente(*aux);
        aux = aux->proximo;
    }
    printf("\nFim da Fila\n");
}

void apagaCliente(Cliente *cl)
{
    printf("\n Apagado!");
    free(cl);
}

void apagaFila(Fila *fl)
{
    Cliente *aux = desenfileirar(fl);
    while (aux != NULL)
    {
        apagaCliente(aux);
        aux = desenfileirar(fl);
    }
    printf("\nFila Vazia - Qtd = %d\n", fl->qtd);
}

int filaVazia(Fila *fl)
{
    return fl->inicio == NULL;
}

void mostrarQuadro(int caixaPrioritario, int caixaGeral, int gerentePrioritario, int gerenteGeral)
{
    printf("Atendimento ao Caixa:\n");
    printf("Prioritário N° = %d\n", caixaPrioritario);
    printf("Geral N° = %d\n", caixaGeral);
    printf("Atendimento Gerente:\n");
    printf("Prioritário N° = %d\n", gerentePrioritario);
    printf("Geral N° = %d\n", gerenteGeral);
}

void menuCaixa(Fila *fG, Fila *fP, Fila *logCaixa, float *saldoCaixa)
{
    int op;
    Cliente *cl;
    char nome[20];
    float vl;

    do
    {
        printf("\n\nInforme uma Opção:");
        printf("\n -- 1 - para Insere:");
        printf("\n -- 2 - para Remove:");
        printf("\n -- 3 - MostraFila:");
        printf("\n -- 4 - Apaga Fila:");
        printf("\n -- 0 - para Sair do Programa:\n");
        printf("\nInforme sua Opçao:");
        scanf("%d", &op);
        fflush(stdin);

        switch (op)
        {
        case 1:
            printf("\n Função Insere na Fila. \n");
            printf("Informe o seu nome:");
            scanf("%s", nome);
            printf("Informe a operacao (1 - saque, 2 - depósito):");
            scanf("%d", &op);
            printf("Informe o Valor:");
            scanf("%f", &vl);
            if (op == 1)
            {
                enfileirar(fP, cadastraNovoCliente(nome, op, vl, fP->qtd + 1));
            }
            else
            {
                enfileirar(fG, cadastraNovoCliente(nome, op, vl, fG->qtd + 1));
            }
            printf("\n Inserção Realizada com Sucesso");
            break;
        case 2:
            printf("\n Função Remove da Fila. \n");
            if (!filaVazia(fP))
            {
                cl = desenfileirar(fP);
            }
            else
            {
                cl = desenfileirar(fG);
            }
            if (cl != NULL)
            {
                mostraCliente(*cl);
                if (cl->operacao == 1)
                {
                    if (*saldoCaixa >= cl->valor)
                    {
                        *saldoCaixa -= cl->valor;
                        printf("Saque realizado. Saldo do caixa: %.2f\n", *saldoCaixa);
                    }
                    else
                    {
                        printf("Saldo insuficiente no caixa.\n");
                    }
                }
                else if (cl->operacao == 2)
                {
                    *saldoCaixa += cl->valor;
                    printf("Depósito realizado. Saldo do caixa: %.2f\n", *saldoCaixa);
                }
                enfileirar(logCaixa, cl); // Adiciona ao log de atendimento do caixa
            }
            printf("\n Remoção Realizada com Sucesso");
            break;
        case 3:
            printf("Mostra Fila:");
            mostraFila(fG);
            mostraFila(fP);
            break;
        case 4:
            printf("\n Apagar a Fila !! \n");
            apagaFila(fG);
            apagaFila(fP);
            break;
        default:
            printf("\nOpção Inválida!!\n");
        }
    } while (op > 0);
}

int main()
{
    Fila *fCaixaGeral, *fCaixaPrio;
    Fila *logCaixa;
    float saldoCaixa = 10000.0;

    fCaixaGeral = criaFila();
    fCaixaPrio = criaFila();
    logCaixa = criaFila();

    // Simulação de menu para o caixa
    menuCaixa(fCaixaGeral, fCaixaPrio, logCaixa, &saldoCaixa);

    return 0;
}
