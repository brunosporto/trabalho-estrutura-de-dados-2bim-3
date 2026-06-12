#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABELA 10
#define TAM_PALAVRA 50
#define TAM_DEFINICAO 200

typedef struct No {
    char palavra[TAM_PALAVRA];
    char definicao[TAM_DEFINICAO];
    struct No *prox;
} No;

No *tabela[TAM_TABELA];

int quantidadeElementos = 0;
int quantidadeColisoes = 0;

int funcaoHash(char *palavra) {
    int soma = 0;

    for (int i = 0; palavra[i] != '\0'; i++) {
        soma += palavra[i];
    }

    return soma % TAM_TABELA;
}

void inserir(char *palavra, char *definicao) {
    int indice = funcaoHash(palavra);

    No *novo = (No *)malloc(sizeof(No));

    strcpy(novo->palavra, palavra);
    strcpy(novo->definicao, definicao);
    novo->prox = NULL;

    if (tabela[indice] != NULL) {
        quantidadeColisoes++;
    }

    novo->prox = tabela[indice];
    tabela[indice] = novo;

    quantidadeElementos++;

    printf("Palavra inserida com sucesso!\n");
}

void buscar(char *palavra) {
    int indice = funcaoHash(palavra);

    No *atual = tabela[indice];

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            printf("\nPalavra: %s\n", atual->palavra);
            printf("Definicao: %s\n", atual->definicao);
            return;
        }

        atual = atual->prox;
    }

    printf("Palavra nao encontrada!\n");
}

void removerPalavra(char *palavra) {
    int indice = funcaoHash(palavra);

    No *atual = tabela[indice];
    No *anterior = NULL;

    while (atual != NULL) {

        if (strcmp(atual->palavra, palavra) == 0) {

            if (anterior == NULL) {
                tabela[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);
            quantidadeElementos--;

            printf("Palavra removida com sucesso!\n");
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Palavra nao encontrada!\n");
}

void exibirTabela() {
    printf("\n===== TABELA HASH =====\n");

    for (int i = 0; i < TAM_TABELA; i++) {

        printf("[%d] -> ", i);

        No *atual = tabela[i];

        while (atual != NULL) {
            printf("(%s) -> ", atual->palavra);
            atual = atual->prox;
        }

        printf("NULL\n");
    }
}

void exibirEstatisticas() {

    int maiorLista = 0;

    for (int i = 0; i < TAM_TABELA; i++) {

        int tamanhoLista = 0;

        No *atual = tabela[i];

        while (atual != NULL) {
            tamanhoLista++;
            atual = atual->prox;
        }

        if (tamanhoLista > maiorLista) {
            maiorLista = tamanhoLista;
        }
    }

    float fatorCarga = (float)quantidadeElementos / TAM_TABELA;

    printf("\n===== ESTATISTICAS =====\n");
    printf("Quantidade de elementos: %d\n", quantidadeElementos);
    printf("Quantidade de colisoes: %d\n", quantidadeColisoes);
    printf("Fator de carga: %.2f\n", fatorCarga);
    printf("Maior lista encadeada: %d\n", maiorLista);
}

void liberarMemoria() {

    for (int i = 0; i < TAM_TABELA; i++) {

        No *atual = tabela[i];

        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}

int main() {

    int opcao;

    char palavra[TAM_PALAVRA];
    char definicao[TAM_DEFINICAO];

    for (int i = 0; i < TAM_TABELA; i++) {
        tabela[i] = NULL;
    }

    do {

        printf("\n===== DICIONARIO HASH =====\n");
        printf("1 - Inserir palavra\n");
        printf("2 - Buscar palavra\n");
        printf("3 - Remover palavra\n");
        printf("4 - Exibir tabela hash\n");
        printf("5 - Exibir estatisticas\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            case 1:

                printf("Palavra: ");
                fgets(palavra, TAM_PALAVRA, stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                printf("Definicao: ");
                fgets(definicao, TAM_DEFINICAO, stdin);
                definicao[strcspn(definicao, "\n")] = '\0';

                inserir(palavra, definicao);
                break;

            case 2:

                printf("Digite a palavra: ");
                fgets(palavra, TAM_PALAVRA, stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                buscar(palavra);
                break;

            case 3:

                printf("Digite a palavra: ");
                fgets(palavra, TAM_PALAVRA, stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                removerPalavra(palavra);
                break;

            case 4:
                exibirTabela();
                break;

            case 5:
                exibirEstatisticas();
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria();

    return 0;
}