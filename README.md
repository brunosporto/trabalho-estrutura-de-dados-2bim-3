# trabalho-estrutura-de-dados-2bim-3

1. Estruturas e Variáveis Globais
#define TAM_TABELA 10
#define TAM_PALAVRA 50
#define TAM_DEFINICAO 200

Essas constantes definem:

TAM_TABELA: quantidade de posições da tabela hash.
TAM_PALAVRA: tamanho máximo da palavra.
TAM_DEFINICAO: tamanho máximo da definição.
Estrutura do nó
typedef struct No {
    char palavra[TAM_PALAVRA];
    char definicao[TAM_DEFINICAO];
    struct No *prox;
} No;

Cada nó da lista encadeada armazena:

uma palavra;
uma definição;
um ponteiro para o próximo nó.

Exemplo:

[Casa] -> [Carro] -> [Cachorro] -> NULL
Tabela Hash
No *tabela[TAM_TABELA];

É um vetor de ponteiros.

Visualmente:

Índice
0 -> NULL
1 -> Casa -> Carro
2 -> NULL
3 -> Bola
4 -> NULL
...

Cada posição pode apontar para uma lista encadeada.

Estatísticas
int quantidadeElementos = 0;
int quantidadeColisoes = 0;

Servem para contar:

quantas palavras existem;
quantas colisões ocorreram.

2. Função Hash
int funcaoHash(char *palavra) {
    int soma = 0;

    for (int i = 0; palavra[i] != '\0'; i++) {
        soma += palavra[i];
    }

    return soma % TAM_TABELA;
}

A função hash transforma uma palavra em um índice.

3. Inserção
void inserir(char *palavra, char *definicao)

Recebe uma palavra e sua definição.

Descobre o índice
int indice = funcaoHash(palavra);

Exemplo:

indice = 3;
Cria novo nó
No *novo = (No *)malloc(sizeof(No));

malloc reserva memória dinamicamente.

Copia os dados
strcpy(novo->palavra, palavra);
strcpy(novo->definicao, definicao);
Verifica colisão
if (tabela[indice] != NULL) {
    quantidadeColisoes++;
}

Se já existe alguém naquele índice, ocorreu colisão.

Insere no início da lista
novo->prox = tabela[indice];
tabela[indice] = novo;

Supondo:

Antes:

índice 2

Casa -> Carro

Depois de inserir "Cachorro":

Cachorro -> Casa -> Carro

4. Busca
void buscar(char *palavra)

Primeiro encontra o índice.

int indice = funcaoHash(palavra);
Percorre a lista
while (atual != NULL)

Compara palavras
if (strcmp(atual->palavra, palavra) == 0)

strcmp retorna 0 quando as strings são iguais.

5. Remoção
void removerPalavra(char *palavra)

Usa dois ponteiros:

No *atual;
No *anterior;
Caso 1: remover o primeiro nó

Antes:

Casa -> Carro -> NULL

Remover "Casa":

tabela[indice] = atual->prox;

Depois:

Carro -> NULL
Caso 2: remover do meio

Antes:

Casa -> Carro -> Cachorro

Remover "Carro":

anterior->prox = atual->prox;

Depois:

Casa -> Cachorro
Libera memória
free(atual);

Muito importante para evitar vazamento de memória.

6. Exibição da Tabela
void exibirTabela()

Percorre todas as posições.

for (int i = 0; i < TAM_TABELA; i++)

7. Estatísticas
void exibirEstatisticas()
Quantidade de elementos

Já é armazenada em:

quantidadeElementos
Quantidade de colisões

Já é armazenada em:

quantidadeColisoes
Fator de carga
float fatorCarga =
(float)quantidadeElementos / TAM_TABELA;

Maior lista encadeada

Percorre todas as listas:

while (atual != NULL)

Conta quantos nós existem.

8. Liberação de Memória
void liberarMemoria()

Percorre toda a tabela.

while (atual != NULL)

Vai removendo cada nó:

free(temp);

Isso evita vazamento de memória quando o programa termina.

9. Função Main

É o menu principal.

do {
   ...
} while(opcao != 0);

Repete até o usuário escolher sair.

Menu
1 - Inserir
2 - Buscar
3 - Remover
4 - Exibir tabela
5 - Estatísticas
0 - Sair
