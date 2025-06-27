#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "interface.h"
#include "avl.h"
#include <conio.h>
// =============================================================================
// FUNÇÕES DA INTERFACE
// =============================================================================

void TelaPrincipalAmazon()
{
    textcolor(WHITE);
    textbackground(BLACK); // Volta o console pro fundo preto
    system("cls");

    textbackground(LIGHT_BLUE); // Agora só os elementos que você desenhar vão ficar azuis
    Borda(1, 1, 76, 28, 1, 0);
    gotoxy(27, 3);
    printf("ANALISE DE VENDAS - AMAZON");
    Borda(5, 5, 66, 21, 0, 0);
    gotoxy(32, 7);
    printf("MENU PRINCIPAL");
    gotoxy(34, 28);
    printf("Versao Beta");
}


// =============================================================================
// FUNÇÃO PRINCIPAL (MAIN)
// =============================================================================

int main()
{
    char opcoes[][50] =
    {
        "1. Carregar Dados e Gerar Arquivo Binario",
        "2. Criar Indice AVL por Categoria",
        "3. Pesquisar Produto por Categoria (AVL)",
        "4. Pesquisar Categoria (Sequencial)",
        "5. Sair"
    };
    int x[] = {13, 13, 13, 13, 13};
    int y[] = {9, 12, 15, 18, 21};
    int tam[] = {50, 50, 50, 50, 50};

    int opcao = 0;
    int dadosCarregados = 0;
    int indiceCriado = 0;

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
            Borda(10, 8, 80, 6, 1, 0);
            gotoxy(12, 10);
            printf("Iniciando carregamento do arquivo 'amazon.csv'...");

            int totalRegistros = CarregaDados(); // Chamando sua função original

            gotoxy(12, 10);
            printf("Carregamento finalizado. Gravando arquivo binario...");

            FILE* fpDados = fopen("Dados.txt", "wb");
            if (fpDados == NULL)
            {
                gotoxy(12, 11);
                printf("ERRO: Nao foi possivel criar o arquivo 'Dados.txt'.");
                getch();
                break;
            }

            for (int i = 0; i < totalRegistros; i++)
            {
                fwrite(&ASales[i], sizeof(AmazonSales), 1, fpDados);
            }
            fclose(fpDados);

            gotoxy(12, 11);
            printf("%d registros gravados com sucesso em 'Dados.txt'!", totalRegistros);
            dadosCarregados = 1;

            getch();
            break;

        case 1:
            textcolor(WHITE);
            textbackground(BLACK);
            system ("cls");
            textbackground(LIGHT_BLUE);
            Borda(10, 8, 60, 6, 1, 0);
            gotoxy(12, 10);
            if (dadosCarregados)
            {
                printf("Funcao para criar indice (A ser implementada).");
                // Futuramente: indiceCriado = 1;
            }
            else
            {
                printf("ERRO: Voce precisa carregar os dados primeiro (Opcao 1).");
            }
            getch();
            break;

        case 2:
            textcolor(WHITE);
            textbackground(BLACK);
            system ("cls");
            textbackground(LIGHT_BLUE);
            Borda(10, 8, 60, 6, 1, 0);
            gotoxy(12, 10);
            if (indiceCriado)
            {
                printf("Funcao de pesquisa (A ser implementada).");
            }
            else
            {
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
              Borda(10, 8, 60, 6, 1, 0);
              gotoxy(12, 10);
                printf("ainda trabalhando nisso");
               //PesquisarPorCategoria_Sequencial();
            }
            else
            {
                // Interface para mostrar erro
                textcolor(WHITE);
                textbackground(BLACK);
                system("cls");
                textbackground(LIGHT_BLUE);
                Borda(10, 8, 60, 6, 1, 0);
                gotoxy(12, 10);
                printf("ERRO: Voce precisa carregar os dados primeiro (Opcao 1).");

            }
            getch();
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
