#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "avl.h"
#include "busca_binaria.h"
#include "dados.h"
#include "interface.h"
#include "ordenacao.h"

void insertionSortParaIndice(IndiceChave* indice, int n)
{
    int i, j;
    IndiceChave chave;

    for (i = 1; i < n; i++)
    {
        chave = indice[i];
        j = i - 1;
        while (j >= 0 && strcasecmp(indice[j].chave, chave.chave) > 0)
        {
            indice[j + 1] = indice[j];
            j = j - 1;
        }
        indice[j + 1] = chave;
    }
}

IndiceChave* criarEOrdenarIndice(int* pTotalChaves) {
    int totalRegistros;

    // Carrega os dados do arquivo para a memória global ASales
    gotoxy(3, 5); printf("Passo 1: Lendo 'Dados.txt' para a memoria...");
    FILE* fp = fopen("Dados.txt", "rb");
    if (fp == NULL) {
        printf("\nERRO ao abrir Dados.txt");
        getch();
        return NULL;
    }
    totalRegistros = fread(ASales, sizeof(AmazonSales), 50000, fp);
    fclose(fp);

    // Cria o Índice Invertido
    gotoxy(3, 7); printf("Passo 2: Criando indice de palavras-chave...");
    IndiceChave* indice = malloc(totalRegistros * 10 * sizeof(IndiceChave));
    if (indice == NULL) {
        printf("\nERRO de alocacao de memoria para o indice.");
        getch();
        return NULL;
    }

    *pTotalChaves = 0;
    for (int i = 0; i < totalRegistros; i++) {
        char categoriaCopia[401];
        strcpy(categoriaCopia, ASales[i].category);
        char* token = strtok(categoriaCopia, "|&");
        while (token != NULL) {
            strcpy(indice[*pTotalChaves].chave, token);
            indice[*pTotalChaves].posicaoOriginal = i * sizeof(AmazonSales);
            (*pTotalChaves)++;
            token = strtok(NULL, "|&");
        }
    }

    // Ordena o Índice com Insertion Sort
    gotoxy(3, 8); printf("Passo 3: Ordenando %d palavras-chave com Insertion Sort...", *pTotalChaves);
    gotoxy(3, 9); printf("AVISO: Este processo pode ser um pouco lento. Por favor, aguarde...");
    insertionSortParaIndice(indice, *pTotalChaves);

    return indice;
}

int buscarNoIndice(const char* categoriaBusca, IndiceChave* indice, int totalChaves, int* pCount, int* pComparacoes) {
    int esquerda = 0, direita = totalChaves - 1, meio;
    int primeiroEncontrado = -1;
    *pComparacoes = 0;

    // Busca binária para encontrar qualquer ocorrência
    while (esquerda <= direita) {
        (*pComparacoes)++;
        meio = esquerda + (direita - esquerda) / 2;
        int res = strcasecmp(categoriaBusca, indice[meio].chave);
        if (res == 0) {
            primeiroEncontrado = meio;
            break;
        }
        if (res > 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    *pCount = 0;
    if (primeiroEncontrado != -1) {
        int i = primeiroEncontrado;
        while (i >= 0 && strcasecmp(indice[i].chave, categoriaBusca) == 0) {
            i--;
        }
        primeiroEncontrado = i + 1;

        i = primeiroEncontrado;
        while (i < totalChaves && strcasecmp(indice[i].chave, categoriaBusca) == 0) {
            (*pCount)++;
            i++;
        }
    }
    return primeiroEncontrado;
}

void exibirEGerenciarResultados(int count, int primeiroEncontrado, IndiceChave* indice, const char* categoriaBusca, int totalChaves, double tempoGasto, int comparacoes) {

    AmazonSales* produtosEncontrados = malloc(count * sizeof(AmazonSales));
    FILE* fp = fopen("Dados.txt", "rb");
    if (fp == NULL || produtosEncontrados == NULL) {
        printf("\nERRO ao abrir arquivo ou alocar memoria.");
        getch();
        if (fp) fclose(fp);
        if (produtosEncontrados) free(produtosEncontrados);
        return;
    }

    for (int i = 0; i < count; i++) {
        fseek(fp, indice[primeiroEncontrado + i].posicaoOriginal, SEEK_SET);
        fread(&produtosEncontrados[i], sizeof(AmazonSales), 1, fp);
    }
    fclose(fp);

    // Remove duplicatas antes de exibir
    count = removerDuplicatas(produtosEncontrados, count);

    char** dadosFormatados = malloc(count * sizeof(char*));
    for (int i = 0; i < count; i++) dadosFormatados[i] = malloc(121 * sizeof(char));

    int ordemPreco = 1, ordemRating = -1, ordemDesconto = -1;
    int comando;

    do {

        for (int i = 0; i < count; i++) {
            sprintf(dadosFormatados[i], "%-12.12s |%-40.40s | $%-11.2f | %-11.2d | $%-17.2f | %.1f",
                    produtosEncontrados[i].product_id, produtosEncontrados[i].product_name,
                    produtosEncontrados[i].actual_price, produtosEncontrados[i].discount_percentage,
                    produtosEncontrados[i].discounted_price, produtosEncontrados[i].rating);
        }

        textcolor(WHITE);
        textbackground(BLACK);
        system("cls");
        textbackground(LIGHT_BLUE);
        Borda(1, 1, 115, 28, 1, 0);
        gotoxy(3, 2);
        printf("Resultados para '%s' | F1=Preco %s | F2=Rating %s | F3=Desconto(%%) %s | ENTER para acessar",
               categoriaBusca, (ordemPreco == 1 ? "<-" : "->"),
               (ordemRating == -1 ? "->" : "<-"),
               (ordemDesconto == -1 ? "->" : "<-"));
        gotoxy(3, 4);
        printf("%-12.12s|%-40.40s | %-12.12s | %-11.11s | %-16.19s | %-8.8s","ID produto", "Produto", "Preco Atual", "Desconto(%)","Preco Pos-Desconto", "Rating");
        gotoxy(3, 27);
        printf("Indice com %d palavras-chave |Tempo TOTAL: %.4f seg | Comparacoes na busca: %d", totalChaves, tempoGasto, comparacoes);
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

    } while (comando >= 1001 && comando <= 1003);
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

    for (int i = 0; i < count; i++) free(dadosFormatados[i]);
    free(dadosFormatados);
    free(produtosEncontrados);
}

void ExecutarBuscaBinaria(void)
{

    char categoriaBusca[201] = {0};
    int tecla;
    textcolor(WHITE);
    textbackground(BLACK);
    system ("cls");
    textbackground(LIGHT_BLUE);
    Borda(1, 1, 60, 24, 1, 0);
    Borda(17, 3, 30, 2, 1, 0);
    gotoxy(23,4);
    printf("MENU DE BUSCA BINARIA");
    gotoxy(6, 8);
    printf("Digite a categoria para a busca (ESC para cancelar)");
    Borda(12, 10, 40, 2, 1, 0);
    tecla = EntradaDados(14,11, 24, categoriaBusca);

    if (tecla == TEC_ESC) {
        gotoxy(17, 15);
        printf("Operacao cancelada pelo usuario.");
        getch();
        return;
    }

    clock_t inicio = clock();
    textcolor(WHITE);
    textbackground(BLACK);
    system("cls");
    textbackground(LIGHT_BLUE);
    Borda(1, 1, 78, 24, 1, 0);
    gotoxy(3, 3);
    printf("Iniciando Busca...");

    int totalChaves;

    IndiceChave* indice = criarEOrdenarIndice(&totalChaves);
    if (indice == NULL) {
        return;
    }

    gotoxy(3, 11);
    printf("Ordenacao concluida! Iniciando a busca binaria...");

    int count = 0;
    int comparacoes = 0;
    int primeiroEncontrado = buscarNoIndice(categoriaBusca, indice, totalChaves, &count, &comparacoes);

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    if (count > 0) {
        exibirEGerenciarResultados(count, primeiroEncontrado, indice, categoriaBusca, totalChaves, tempoGasto, comparacoes);
    } else {
        gotoxy(3, 15);
        printf("Nenhum produto encontrado contendo a palavra: '%s'", categoriaBusca);
        getch();
    }
    free(indice);
}
