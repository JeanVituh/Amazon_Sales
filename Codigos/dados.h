#ifndef DADOS_H_INCLUDED
#define DADOS_H_INCLUDED

typedef struct
{
    char product_id[11], product_name[1000], category[201];
    double discounted_price, actual_price;
    int discount_percentage;
    double rating;
    char product_link[400];
} AmazonSales;

extern AmazonSales ASales[50000];
char* limpaStringPreco(char s[]);
int CarregaDados(void);

#endif // DADOS_H_INCLUDED
