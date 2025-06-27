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

AmazonSales ASales[50000];
int CarregaDados();

#endif // DADOS_H_INCLUDED
