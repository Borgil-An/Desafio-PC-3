#include <stdio.h>
#include <stdlib.h>

#define TAM 100
#define ARQUIVO "produtos.bin"

typedef struct produto
{
    char nome[TAM];
    double preco;
    int id;
    struct produto *prox;
} produto;

void AdicionarProduto(produto **comeco);
void RemoverProduto(produto **comeco);
void ImprimirLista(produto *comeco);
void CarregarLista(produto **comeco);
void SalvarLista(produto *comeco);
void LiberarLista(produto **comeco);

int main(void)
{
    produto *comeco = NULL;
    int escolha;

    while (1)
    {
        printf("\n1-Adicionar Produto\n");
        printf("2-Remover Produto\n");
        printf("3-Imprimir Lista\n");
        printf("4-Carregar Lista em produtos.bin\n");
        printf("5-Salvar Lista Atual no Arquivo produtos.bin\n");
        printf("0-Sair\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            AdicionarProduto(&comeco);
            break;

        case 2:
            RemoverProduto(&comeco);
            break;

        case 3:
            ImprimirLista(comeco);
            break;

        case 4:
            CarregarLista(&comeco);
            break;

        case 5:
            SalvarLista(comeco);
            break;

        case 0:
            LiberarLista(&comeco);
            printf("\nLista liberada da memoria e o programa encerrado.\n");
            exit(0);
            break;
            
        default:
            printf("\nValor Invalido\n");
        }
    }
}

void AdicionarProduto(produto **comeco)
{
    produto *novo_produto = (produto *)malloc(sizeof(produto));
    printf("\nInforme o nome do produto:\n");
    getchar();
    fgets(novo_produto->nome, TAM, stdin);
    printf("\nInforme o preço do produto:\n ");
    scanf("%lf", &novo_produto->preco);
    printf("\nInforme o ID do produto:\n ");
    scanf("%d", &novo_produto->id);

    produto *atual = *comeco;
    produto *anterior = NULL;

    while (atual != NULL && atual->preco < novo_produto->preco)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL)
    {
        novo_produto->prox = *comeco;
        *comeco = novo_produto;
    }
    else
    {
        anterior->prox = novo_produto;
        novo_produto->prox = atual;
    }
}

void RemoverProduto(produto **comeco)
{
    int id;
    printf("\nDigite o ID do produto a ser removido:\n");
    scanf("%d", &id);

    produto *atual = *comeco;
    produto *anterior = NULL;

    while (atual != NULL && atual->id != id)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("\nProduto com ID:%d não encontrado na lista.\n", id);
    }
    else
    {
        if (anterior == NULL)
        {
            *comeco = atual->prox;
        }
        else
        {
            anterior->prox = atual->prox;
        }
        free(atual);
        printf("\nProduto com ID:%d removido da lista.\n", id);
    }
}

void ImprimirLista(produto *comeco)
{
    printf("\n---- Lista de Produtos ----\n");

    produto *atual = comeco;
    while (atual != NULL)
    {
        printf("\nNome: %s\n", atual->nome);
        printf("Preco: %.2lf\n", atual->preco);
        printf("ID: %d\n", atual->id);
        atual = atual->prox;
    }
}

void SalvarLista(produto *comeco){
FILE *fp;

fp = fopen("produtos.bin", "w+b");

if (fp == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return;
}

produto *atual = comeco;

while (atual != NULL){
    if(fwrite(atual, sizeof(produto), 1, fp) != 1) {
        printf("Erro ao salvar produto no arquivo.\n");
        break;
    }
    atual = atual->prox;
}

fclose(fp);

printf("\nLista salva com sucesso!\n");
}

void CarregarLista(produto **comeco)
{
FILE *arquivo = fopen(ARQUIVO, "rb");

if (arquivo == NULL)
{
    printf("\nArquivo de Produtos não encontrado.\n");
    return;
}

produto *novo_produto;

while (novo_produto = (produto *)malloc(sizeof(produto)), fread(novo_produto, sizeof(produto), 1, arquivo))
{
    novo_produto->prox = NULL;

    produto *atual = *comeco;
    produto *anterior = NULL;

    while (atual != NULL && atual->preco < novo_produto->preco)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL)
    {
        novo_produto->prox = *comeco;
        *comeco = novo_produto;
    }
    else
    {
        anterior->prox = novo_produto;
        novo_produto->prox = atual;
    }
}

fclose(arquivo);
printf("\nLista de produtos carregada do arquivo com sucesso.\n");
}

void LiberarLista(produto **comeco)
{
produto *atual = *comeco;
while (atual != NULL)
{
    produto *prox = atual->prox;
    free(atual);
    atual = prox;
}

*comeco = NULL;
}
