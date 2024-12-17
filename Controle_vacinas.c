#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    int dia, mes, ano;
} Data;

typedef struct vacina
{
    char nome[20];
    char fabricante[20];
    Data validade;
} Vacina;

typedef struct cao
{
    char nome[15];
    int idade;
    Data dNascimento;
    Vacina carterinha[10];
    int qtVacinas;
    char nomePai[15];
    char nomeMae[15];
} Cao;

void mostraData(Data dt)
{
    printf("%02d/%02d/%04d\n", dt.dia, dt.mes, dt.ano);
}

void mostraVacina(Vacina vc)
{
    printf("Nome: %s\n", vc.nome);
    printf("Fabricante: %s\n", vc.fabricante);
    printf("Validade: ");
    mostraData(vc.validade);
}

void mostraDadosCao(Cao dog)
{
    printf("Nome: %s\n", dog.nome);
    printf("Idade: %d\n", dog.idade);
    printf("Data de Nascimento: ");
    mostraData(dog.dNascimento);
    printf("Vacinas:\n");
    for (int i = 0; i < dog.qtVacinas; i++)
    {
        mostraVacina(dog.carterinha[i]);
    }
    if (strlen(dog.nomePai) > 0 && strlen(dog.nomeMae) > 0)
    {
        printf("Nome do Pai: %s\n", dog.nomePai);
        printf("Nome da Mãe: %s\n", dog.nomeMae);
    }
}

Data cadastraData(int d, int m, int a)
{
    Data dt;
    dt.dia = d;
    dt.mes = m;
    dt.ano = a;
    return dt;
}

void cadastraVacina(Vacina *vc)
{
    printf("Nome da Vacina: ");
    scanf("%s", vc->nome);
    printf("Fabricante da Vacina: ");
    scanf("%s", vc->fabricante);
    int d, m, a;
    printf("Data de Validade (dd mm aaaa): ");
    scanf("%d %d %d", &d, &m, &a);
    vc->validade = cadastraData(d, m, a);
}

void cadastraCao(Cao *dog)
{
    printf("Nome do Cão: ");
    scanf("%s", dog->nome);
    printf("Idade do Cão: ");
    scanf("%d", &dog->idade);
    int d, m, a;
    printf("Data de Nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &d, &m, &a);
    dog->dNascimento = cadastraData(d, m, a);
    dog->qtVacinas = 0; // Inicialmente, o cão não tem vacinas.
}

void vacinacao(Cao *dog, Vacina vc)
{
    if (dog->qtVacinas < 10)
    {
        dog->carterinha[dog->qtVacinas] = vc;
        dog->qtVacinas++;
    }
    else
    {
        printf("O cão já recebeu o máximo de vacinas permitidas.\n");
    }
}

Cao *cruzamento(Cao pai, Cao mae)
{
    Cao *filhote = (Cao *)malloc(sizeof(Cao));
    strcpy(filhote->nome, "Filhote");
    filhote->idade = 0;
    filhote->dNascimento = cadastraData(1, 1, 2024); // Exemplo de data de nascimento
    filhote->qtVacinas = 0;
    strcpy(filhote->nomePai, pai.nome);
    strcpy(filhote->nomeMae, mae.nome);
    return filhote;
}

int main()
{
    system("clear");
    setlocale(LC_ALL, "");

    Cao caes[4];
    Vacina vacinas[4];

    // Cadastrar cães
    for (int i = 0; i < 4; i++)
    {
        printf("Cadastrando Cão %d:\n", i + 1);
        cadastraCao(&caes[i]);
    }

    // Cadastrar vacinas
    for (int i = 0; i < 4; i++)
    {
        printf("Cadastrando Vacina %d:\n", i + 1);
        cadastraVacina(&vacinas[i]);
    }

    // Aplicar vacinas nos cães
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            vacinacao(&caes[i], vacinas[j]);
        }
    }

    // Realizar cruzamento e registrar filhote
    Cao *filhote = cruzamento(caes[0], caes[1]);
    vacinacao(filhote, vacinas[0]);
    vacinacao(filhote, vacinas[1]);

    // Mostrar dados dos cães e vacinas
    for (int i = 0; i < 4; i++)
    {
        printf("Dados do Cão %d:\n", i + 1);
        mostraDadosCao(caes[i]);
    }

    printf("Dados do Filhote:\n");
    mostraDadosCao(*filhote);

    free(filhote);
    return 0;
}
