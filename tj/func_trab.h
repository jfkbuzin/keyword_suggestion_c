#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <time.h>

typedef struct TipoInfoNo InfoNo;
typedef struct TipoPtNo PtNo;

struct TipoInfoNo{
       char pal_b[30];
       float freq_b;
       };

struct TipoPtNo{
       InfoNo info;
       PtNo *lfreq;
       };


struct TNodoA
{
    char palavra[50];
    float freq_a;        //vetor de caracteres para armazenar uma palavra
    PtNo *lfreq;
    int FB;             //variável para fator de balanceamento
    struct TNodoA *esq; //ponteiro do tipo tNodoA para caminho a esquerda
    struct TNodoA *dir; //ponteiro do tipo tNodoA para caminho a direita
};
typedef struct TNodoA pNodoA;

pNodoA* InsereAVL (pNodoA* a, char* palavra, int *ok);

pNodoA* Caso1 (pNodoA* a , int *ok);

pNodoA* Caso2 (pNodoA* a , int *ok);

pNodoA* rotacao_dupla_esquerda (pNodoA* pt);

pNodoA* rotacao_dupla_direita (pNodoA* pt);

pNodoA* rotacao_esquerda(pNodoA* pt);

pNodoA* rotacao_direita(pNodoA* pt);

pNodoA* localiza(pNodoA* pt, char* consulta);


pNodoA* insere_freq (pNodoA *pt, char ant[], char pal[]);
pNodoA* insere_freq2 (pNodoA *pt, char ante[], char pal[]);
void formula(pNodoA *pt, char pal[]);
void formula2(pNodoA *pt, char pal[], int cont, FILE *arq);
pNodoA* decrescente(pNodoA  *pt, char pal[]);
void imprime2(pNodoA *pt, char pal[]);
