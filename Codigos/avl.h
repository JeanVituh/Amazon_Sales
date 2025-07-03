#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

typedef struct ListaPos {
    long posicao;
    struct ListaPos* proximo;
} ListaPos;

typedef struct AvlNode {
    char chave[201]; // A categoria ou subcategoria
    int altura;
    struct AvlNode *esq, *dir;
    ListaPos* posicoes;// Ponteiro para a lista de produtos com esta chave
} AvlNode;
int contarNos(AvlNode* a);
int altura(AvlNode* a);
int maior(int x, int y);
int fatorBalanceamento(AvlNode* a);
AvlNode* rotacaoLL(AvlNode* a);
AvlNode* rotacaoRR(AvlNode* a);
AvlNode* rotacaoLR(AvlNode* a);
AvlNode* rotacaoRL(AvlNode* a);
AvlNode* inserirAvl(AvlNode* a, const char* chave, long pos);
AvlNode* CriarIndiceAVL(int* pTotalAcessos);
void PesquisarNaArvoreAVL(AvlNode* raiz);
void LiberarArvore(AvlNode* raiz);


#endif // AVL_H_INCLUDED
