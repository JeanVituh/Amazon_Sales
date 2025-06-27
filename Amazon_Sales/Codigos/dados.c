#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "avl.h"
#include "dados.h"



char* replace(char s[], char c1, char c2)
{
    int l = strlen(s);
    for (int i = 0; i < l; i++)
    {
        if (s[i] == c1)
            s[i] = c2;
    }
    return s;
}

// SUA FUNÇÃO CarregaDados, EXATAMENTE COMO VOCÊ FORNECEU
int CarregaDados()
{
    FILE *fp = fopen("amazon.csv", "r");
    if(fp == NULL)
    {
        printf("Nao abrir amazon.csv!\n");
        exit(1);
    }
    char Linha[10000], *p, texto[10000]; // Declare texto
    int cont = 0, campo;

    // Pula a linha do cabeçalho
    if(fscanf(fp, " %[^\n]", Linha) == EOF) return 0;

    while(fscanf(fp, " %[^\n]", Linha) != EOF && cont < 50000)
    {
        p = strtok(Linha, ",");
        campo = 0;
        while(p != NULL)
        {
            strcpy(texto, p);
            if(texto[0] == '\"')
            {
                strcpy(texto, p+1);
                p = strtok(NULL, "\"");
                strcat(texto, ",");
                if(p != NULL) strcat(texto, p);
            }

            if(campo == 0) strcpy(ASales[cont].product_id, texto);
            if(campo == 1) strcpy(ASales[cont].product_name, texto);
            if(campo == 2) strcpy(ASales[cont].category, texto);
            if(campo == 3) ASales[cont].discounted_price = strtof(replace(texto, ',', '.'), NULL);
            if(campo == 4) ASales[cont].actual_price = strtof(replace(texto, ',', '.'), NULL);
            if(campo == 5) ASales[cont].discount_percentage = atoi(texto);
            if(campo == 6) ASales[cont].rating = strtof(replace(texto, ',', '.'), NULL);
            if(campo == 7) strcpy(ASales[cont].product_link, texto);

            p = strtok(NULL, ",");
            campo++;
        }
        cont++;
    }
    fclose(fp);
    return cont;
}

int Busca (int VET[], int n, int v) // BUSCA SEQUENCIAL PARA SER IMPLEMENTADA
{
    for (int i=0; i< n; i++)
    {
        if (VET[i]== v) return i;
    }
    return -1;
}
