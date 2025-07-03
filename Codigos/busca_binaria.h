#ifndef BUSCA_BINARIA_H_INCLUDED
#define BUSCA_BINARIA_H_INCLUDED
typedef struct
{
    char chave[201];       // A palavra-chave (ex: "cables")
    long posicaoOriginal;  // A posição do produto no arquivo Dados.txt
} IndiceChave;

IndiceChave* criarEOrdenarIndice(int* pTotalChaves);
void insertionSortParaIndice(IndiceChave* indice, int n);
int buscarNoIndice(const char* categoriaBusca, IndiceChave* indice, int totalChaves, int* pCount, int* pComparacoes);
void exibirEGerenciarResultados(int count, int primeiroEncontrado, IndiceChave* indice, const char* categoriaBusca, int totalChaves, double tempoGasto, int comparacoes);
void ExecutarBuscaBinaria(void);
#endif // BUSCA_BINARIA_H_INCLUDED
