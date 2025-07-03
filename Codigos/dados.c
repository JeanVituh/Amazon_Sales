#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "avl.h"
#include "dados.h"
#include "busca_binaria.h"

AmazonSales ASales[50000];

char* limpaStringPreco(char s[])
{
    int writer = 0;
    int reader = 0;

    while (s[reader] != '\0')
    {
        if ((s[reader] >= '0' && s[reader] <= '9') || s[reader] == '.')
        {
            s[writer] = s[reader];
            writer++;
        }
        reader++;
    }

    s[writer] = '\0';
    return s;
}

int CarregaDados()
{
    FILE *fp = fopen("amazon.csv", "r");
    if(fp == NULL)
    {
        printf("Nao abrir amazon.csv!\n");
        exit(1);
    }
    char Linha[10000], *p, texto[10000];
    int cont = 0, campo;

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
            if(campo == 3) ASales[cont].discounted_price = strtof(limpaStringPreco(texto), NULL);
            if(campo == 4) ASales[cont].actual_price = strtof(limpaStringPreco(texto), NULL);
            if(campo == 5) ASales[cont].discount_percentage = atoi(texto);
            if(campo == 6) ASales[cont].rating = strtof(texto, NULL);
            if(campo == 7) strcpy(ASales[cont].product_link, texto);

            p = strtok(NULL, ",");
            campo++;
        }
        cont++;
    }
    fclose(fp);
    return cont;
}
