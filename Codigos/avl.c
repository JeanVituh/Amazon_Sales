#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avl.h"
#include "dados.h"
#include "interface.h"
#include "ordenacao.h"
int altura(AvlNode* a)
{
    return (a == NULL) ? -1 : a->altura;
}

int maior(int x, int y)
{
    return (x > y) ? x : y;
}

int fatorBalanceamento(AvlNode* a)
{
    if (a == NULL) return 0;
    return altura(a->esq) - altura(a->dir);
}

AvlNode* rotacaoLL(AvlNode* a)
{
    AvlNode* no = a->esq;
    a->esq = no->dir;
    no->dir = a;
    a->altura = maior(altura(a->esq), altura(a->dir)) + 1;
    no->altura = maior(altura(no->esq), a->altura) + 1;
    return no;
}

AvlNode* rotacaoRR(AvlNode* a)
{
    AvlNode* no = a->dir;
    a->dir = no->esq;
    no->esq = a;
    a->altura = maior(altura(a->esq), altura(a->dir)) + 1;
    no->altura = maior(altura(no->dir), a->altura) + 1;
    return no;
}

AvlNode* rotacaoLR(AvlNode* a)
{
    a->esq = rotacaoRR(a->esq);
    return rotacaoLL(a);
}

AvlNode* rotacaoRL(AvlNode* a)
{
    a->dir = rotacaoLL(a->dir);
    return rotacaoRR(a);
}

AvlNode* inserirAvl(AvlNode* a, const char* chave, long pos)
{
    if (a == NULL)
    {
        AvlNode* novo = (AvlNode*)malloc(sizeof(AvlNode));
        strcpy(novo->chave, chave);
        novo->altura = 0;
        novo->esq = novo->dir = NULL;
        novo->posicoes = (ListaPos*)malloc(sizeof(ListaPos));
        novo->posicoes->posicao = pos;
        novo->posicoes->proximo = NULL;
        return novo;
    }

    int cmp = strcasecmp(chave, a->chave);
    if (cmp == 0)
    {
        ListaPos* novoPos = (ListaPos*)malloc(sizeof(ListaPos));
        novoPos->posicao = pos;
        novoPos->proximo = a->posicoes;
        a->posicoes = novoPos;
        return a;
    }
    if (cmp < 0)
    {
        a->esq = inserirAvl(a->esq, chave, pos);
    }
    else
    {
        a->dir = inserirAvl(a->dir, chave, pos);
    }
    a->altura = maior(altura(a->esq), altura(a->dir)) + 1;

    int fb = fatorBalanceamento(a);

    if (fb > 1)
    {
        if (strcasecmp(chave, a->esq->chave) < 0)
        {
            a = rotacaoLL(a);
        }
        else
        {
            a = rotacaoLR(a);
        }
    }
    else if (fb < -1)
    {
        if (strcasecmp(chave, a->dir->chave) > 0)
        {
            a = rotacaoRR(a);
        }
        else
        {
            a = rotacaoRL(a);
        }
    }
    return a;
}

AvlNode* CriarIndiceAVL(int* pTotalAcessos)
{
    FILE* fp = fopen("Dados.txt", "rb");
    if (fp == NULL)
    {
        printf("ERRO: Nao foi possivel abrir 'Dados.txt'. Crie o arquivo na Opcao 1.\n");
        getch();
        return NULL;
    }

    AmazonSales reg;
    AvlNode* raiz = NULL;
    long posicaoAtual = ftell(fp);
    *pTotalAcessos = 0;

    while(fread(&reg, sizeof(AmazonSales), 1, fp) == 1)
    {
        (*pTotalAcessos)++;

        char categoriaCopia[401];
        strcpy(categoriaCopia, reg.category);

        char* token = strtok(categoriaCopia, "|&");
        while (token != NULL)
        {
            raiz = inserirAvl(raiz, token, posicaoAtual);
            token = strtok(NULL, "|&");
        }

        posicaoAtual = ftell(fp);
    }

    fclose(fp);
    return raiz;
}
int contarNos(AvlNode* a)
{
    if (a == NULL)
    {
        return 0;
    }
    return 1 + contarNos(a->esq) + contarNos(a->dir);
}

void PesquisarNaArvoreAVL(AvlNode* raiz)
{
    if (raiz == NULL)
    {
        gotoxy(17, 15);
        printf("ERRO: O indice ainda nao foi criado (Opcao 2).\n");
        getch();
        return;
    }

    char categoriaBusca[201] = {0};

    int tecla;
    clock_t inicio, fim;
    double tempoGasto;
    int totalChavesAVL = contarNos(raiz);
    textcolor(WHITE);
    textbackground(BLACK);
    system ("cls");
    textbackground(LIGHT_BLUE);
    Borda(1, 1, 60, 24, 1, 0);
    Borda(17, 3, 30, 2, 1, 0);
    gotoxy(25,4);
    printf("MENU DE BUSCA AVL");
    gotoxy(6, 8);
    printf("Digite a categoria para a busca (ESC para cancelar)");
    Borda(12, 10, 40, 2, 1, 0);
    tecla = EntradaDados(14,11, 24, categoriaBusca);
    if (tecla == TEC_ESC)
    {
        gotoxy(17, 15);
        printf("Operacao cancelada pelo usuario.");
        getch();
        return;
    }

    inicio = clock();
    AvlNode* noAtual = raiz;
    int acessosMemoria = 0;
    while (noAtual != NULL)
    {
        acessosMemoria++;
        int cmp = strcasecmp(categoriaBusca, noAtual->chave);
        if (cmp == 0) break;
        if (cmp < 0) noAtual = noAtual->esq;
        else noAtual = noAtual->dir;
    }

    fim = clock();
    tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    if (noAtual != NULL)
    {
        FILE* fp = fopen("Dados.txt", "rb");
        AmazonSales reg;
        ListaPos* p = noAtual->posicoes;
        int count = 0;

        //Conta quantos produtos existem
        while (p != NULL)
        {
            count++;
            p = p->proximo;
        }

        if (count > 0 && fp != NULL)
        {
            int ordemPreco = 1;
            int ordemRating = -1;
            int ordemDesconto = -1;
            AmazonSales* produtosEncontrados = malloc(count * sizeof(AmazonSales));

            p = noAtual->posicoes;
            int i = 0;
            while(p != NULL)
            {
                fseek(fp, p->posicao, SEEK_SET);
                fread(&produtosEncontrados[i], sizeof(AmazonSales), 1, fp);
                i++;
                p = p->proximo;
            }
            fclose(fp);
            count = removerDuplicatas(produtosEncontrados, count);
            char** dadosFormatados = malloc(count * sizeof(char*));
            for(i = 0; i < count; i++) dadosFormatados[i] = malloc(121 * sizeof(char));

            int comando;
            do
            {
                // preenche a lista a partir do vetor 'produtosEncontrados' e roda toda vez que a lista é reordenada.
                for (i = 0; i < count; i++)
                {
                    sprintf(dadosFormatados[i], "%-12.12s |%-40.40s | $%-11.2f | %-11.2d | $%-17.2f | %.1f",
                            produtosEncontrados[i].product_id, produtosEncontrados[i].product_name,
                            produtosEncontrados[i].actual_price, produtosEncontrados[i].discount_percentage,
                            produtosEncontrados[i].discounted_price, produtosEncontrados[i].rating);
                }

                textcolor(WHITE);
                textbackground(BLACK);
                system ("cls");
                textbackground(LIGHT_BLUE);
                ;
                Borda(1, 1, 115, 28, 1, 0);
                gotoxy(3, 2);
                printf("Resultados para '%s' | F1=Preco %s | F2=Rating %s | F3=Desconto(%%) %s | ENTER para acessar",
                       categoriaBusca,
                       (ordemPreco == 1 ? "<-" : "->"),
                       (ordemRating == -1 ? "->" : "<-"),
                       (ordemDesconto == -1 ? "->" : "<-"));
                gotoxy(3, 4);
                printf("%-12.12s|%-40.40s | %-12.12s | %-11.11s | %-16.19s | %-8.8s","ID produto", "Produto", "Preco Atual", "Desconto(%)","Preco Pos-Desconto", "Rating");
                gotoxy(3, 27);
                printf("Indice com %d palavras-chave| Tempo TOTAL: %.4f seg | Comparacoes na busca: %d",totalChavesAVL, tempoGasto, acessosMemoria);
                gotoxy(3, 25);
                printf("Total de %d produtos encontrados.", count);
                comando = Selecao2(dadosFormatados, count, 2, 6, 18);

                if (comando == 1001)
                {
                    insertionSortPorPreco(produtosEncontrados, count, ordemPreco);
                    ordemPreco *= -1;
                }
                if (comando == 1002)
                {
                    insertionSortPorRating(produtosEncontrados, count, ordemRating);
                    ordemRating *= -1;
                }
                if (comando == 1003)
                {
                    insertionSortPorDesconto(produtosEncontrados, count, ordemDesconto);
                    ordemDesconto *= -1;
                }

            }
            while(comando >= 1001 && comando <= 1003);

            if (comando != -1)
            {
                char* linkDoProduto = produtosEncontrados[comando].product_link;
                char comando_str[1000];
                sprintf(comando_str, "start \"\" \"%s\"", linkDoProduto);

                textcolor(WHITE);
                textbackground(BLACK);
                system("cls");

                textbackground(LIGHT_BLUE);
                Borda(10, 8, 60, 6, 1, 0);
                gotoxy(12, 10);
                printf("Abrindo a pagina do produto no seu navegador...");
                system(comando_str);
                getch();
            }

            for (i = 0; i < count; i++)
            {
                free(dadosFormatados[i]);
            }
            free(dadosFormatados);
            free(produtosEncontrados);


        }

        else
        {
            gotoxy(17, 15);
            printf("Nenhum produto encontrado ou erro ao abrir arquivo.");

        }
    }
    else
    {
        gotoxy(6, 15);
        printf("Nenhuma categoria encontrada no indice com este nome.");
    }
}
void LiberarArvore(AvlNode* raiz)
{
    if (raiz == NULL) return;
    LiberarArvore(raiz->esq);
    LiberarArvore(raiz->dir);
    ListaPos* p = raiz->posicoes;
    while(p != NULL)
    {
        ListaPos* temp = p;
        p = p->proximo;
        free(temp);
    }
    free(raiz);
}
