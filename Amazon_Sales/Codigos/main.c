#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"
#include "avl.h"
#include "dados.h"
#include "busca_binaria.h"

void TelaPrincipalAmazon()
{
    textcolor(WHITE);
    textbackground(BLACK);
    system("cls");

    textbackground(LIGHT_BLUE);
    Borda(1, 1, 76, 28, 1, 0);
    gotoxy(27, 3);
    printf("ANALISE DE VENDAS - AMAZON");
    Borda(5, 5, 66, 21, 0, 0);
    Borda(23, 6, 30, 2, 1, 0);
    gotoxy(32,7);
    printf("MENU PRINCIPAL");
    gotoxy(34, 28);
    printf("Versao Beta");
}

int main()
{
    char opcoes[][50] =
    {
        "1. Carregar Dados e Gerar Arquivo Binario",
        "2. Criar Indice AVL por Categoria",
        "3. Pesquisar Produto por Categoria (AVL)",
        "4. Pesquisar Categoria (Binaria)",
        "5. Sair"
    };
    int x[] = {13, 13, 13, 13, 13};
    int y[] = {10, 13, 16, 19, 22};
    int tam[] = {50, 50, 50, 50, 50};
    AvlNode* arvoreIndice = NULL;
    int opcao = 0;
    int dadosCarregados = 0;
    int indiceCriado = 0;
    int acessosDisco = 0;
    do
    {

        TelaPrincipalAmazon();
        opcao = Menu(opcoes, x, y, tam, 5, opcao);

        switch (opcao)
        {
        case 0:
            textcolor(WHITE);
            textbackground(BLACK);
            system ("cls");
            textbackground(LIGHT_BLUE);
            Borda(1, 1, 80, 10, 1, 0);
            gotoxy(17, 3);
            clock_t inicio, fim;
            double tempoGasto;

            //Captura o tempo inicial
            inicio = clock();
            printf("Iniciando carregamento do arquivo 'amazon.csv'...");

            int totalRegistros = CarregaDados();

            gotoxy(15, 5);
            printf("Carregamento finalizado. Gravando arquivo binario...");

            FILE* fpDados = fopen("Dados.txt", "wb");
            if (fpDados == NULL)
            {
                gotoxy(15, 5);
                printf("ERRO: Nao foi possivel criar o arquivo 'Dados.txt'.");
                getch();
                break;
            }

            for (int i = 0; i < totalRegistros; i++)
            {
                fwrite(&ASales[i], sizeof(AmazonSales), 1, fpDados);
            }
            fclose(fpDados);
            //Captura o tempo final e calcula o tempo gasto
            fim = clock();
            tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            gotoxy(15, 7);
            printf("%d registros gravados com sucesso em 'Dados.txt'!", totalRegistros);
            dadosCarregados = 1;
            gotoxy(19, 9);
            printf("Tempo total da operacao: %.4f segundos", tempoGasto);

            getch();
            break;

        case 1:
            textcolor(WHITE);
            textbackground(BLACK);
            system("cls");
            textbackground(LIGHT_BLUE);
            Borda(1, 1, 80, 10, 1, 0);

            if (dadosCarregados)
            {
                inicio = clock();
                acessosDisco = 0;
                gotoxy(15, 3);
                printf("Criando indice AVL, isso pode levar um momento...");

                arvoreIndice = CriarIndiceAVL(&acessosDisco);
                fim = clock();
                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;


                gotoxy(15, 5);
                if (arvoreIndice != NULL)
                {
                    indiceCriado = 1;
                    printf("Indice criado com sucesso! Acessos a disco: %d    ", acessosDisco);
                    gotoxy(19, 7);
                    printf("Tempo total da operacao: %.4f segundos", tempoGasto);
                }
                else
                {
                    printf("Falha ao criar o indice. Verifique o arquivo 'Dados.txt'.");
                }
            }
            else
            {
                gotoxy(13, 6);
                printf("ERRO: Voce precisa carregar os dados primeiro (Opcao 1).");
            }
            getch();
            break;

        case 2:
            textcolor(WHITE);
            textbackground(BLACK);
            system ("cls");
            textbackground(LIGHT_BLUE);
            Borda(1, 1, 80, 10, 1, 0);

            if (indiceCriado)
            {
                PesquisarNaArvoreAVL(arvoreIndice);
            }
            else
            {
                gotoxy(13, 6);
                printf("ERRO: Voce precisa criar o indice primeiro (Opcao 2).");
            }
            getch();
            break;

        case 3:
            textcolor(WHITE);
            textbackground(BLACK);
            system ("cls");
            textbackground(LIGHT_BLUE);

            if (dadosCarregados)
            {
                ExecutarBuscaBinaria();
            }
            else
            {
                Borda(1, 1, 80, 10, 1, 0);
                gotoxy(13, 6);
                printf("ERRO: Voce precisa carregar os dados primeiro (Opcao 1).");
                getch();
            }
            break;

        case 4:
            textcolor(WHITE);
            textbackground(BLACK);
            system ("cls");
            textbackground(LIGHT_BLUE);
            Borda(8, 2, 60, 6, 1, 0);
            gotoxy(25, 5);
            printf("Obrigado por usar o sistema!\n\n");
            break;
        }

    }
    while (opcao != 4);
    gotoxy(30, 10);
    return 0;
}
