#include "func_trab.h"

pNodoA* InsereAVL (pNodoA* a, char* palavra, int *ok )
{


    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore*/
    pNodoA* arv_consul;
    arv_consul = localiza(a, palavra);                            // consulta palavra para ver se já não foi inserido

    if(arv_consul == NULL)                                      // significa que não há esta palavra na arvore
    {
        if (a == NULL)
        {
            a = (pNodoA*) malloc(sizeof(pNodoA));               //aloca memória para "a" do tipo pNodoA
            a->esq = NULL;                                      //esquerda inicializado em NULL, pois é uma folha
            a->dir = NULL;                                      //direita inicializado em NULL, pois é uma folha
            a->lfreq = NULL;                                    //ponteiro para a lista de palavras adjacentes, inicia em NULL
            a->freq_a = 1;                                      //float para a frequencia, começa sendo a soma de vezes que a palavra aparece no texto
            strcpy(a->palavra, palavra);                        //copia para string palavra do nó a palavra que foi encontrada
            a->FB = 0;                                          //fator de balanceamento inicializado em 0 (balanceado)
            *ok = 1;
        }
        else if (strcmp(palavra,a->palavra) <  0)               //palavra < a->palavra (ordem alfabética baseado na tabela ASCII)
        {

            a->esq = InsereAVL(a->esq, palavra, ok);   //percorre a esquerda
            if (*ok)
            {
                switch (a->FB)
                {
                case -1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case 0:
                    a->FB = 1;
                    break;
                case 1:
                    a=Caso1(a,ok);
                    break;
                }
            }

        }
        else //palavra > a->palavra (ordem alfabética baseado na tabela ASCII)
        {

            a->dir = InsereAVL(a->dir, palavra, ok); //percorre a direita
            if (*ok)
            {
                switch (a->FB)
                {
                case 1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case 0:
                    a->FB = -1;
                    break;
                case -1:
                    a = Caso2(a,ok);
                    break;
                }
            }
        }
        return a;
    }
    else  // caso já tenha a palavra na árvore
    {
        arv_consul->freq_a++;
        //puts(arv_consul->palavra);
        //printf("freq = (%.6f)\n", arv_consul->freq_a);

        return a;
    }
}

pNodoA* Caso1 (pNodoA* a , int *ok)     //função para balanceamento da árvore, caso o ok = 1
{
    pNodoA *ptu;
    ptu = a->esq;
    if (ptu->FB == 1)
    {
        a = rotacao_direita(a);  //é feita rotação a direita caso o fator de balanceamento = 1
    }
    else
    {
        a = rotacao_dupla_direita(a);  //é feita rotação dupla a direita caso o balanceamento != 1
    }
    a->FB = 0;  //fator de balanceamento é zerado, pois esta balanceado
    *ok = 0;
    return a;
}

pNodoA* Caso2 (pNodoA* a , int *ok)
{
    pNodoA *ptu;
    ptu = a->dir;
    if (ptu->FB == -1)
    {
        a=rotacao_esquerda(a);  //é feita rotação a direita caso o fator de balanceamento = -1
    }
    else
    {
        a=rotacao_dupla_esquerda(a);  //é feita rotação dupla a direita caso o balanceamento != -1
    }
    a->FB = 0; //fator de balanceamento é zerado, pois esta balanceado
    *ok = 0;
    return a;
}



pNodoA* rotacao_esquerda(pNodoA *pt)
{
    pNodoA *ptu;
    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

pNodoA* rotacao_direita(pNodoA *pt)
{
    pNodoA *ptu;
    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

pNodoA* rotacao_dupla_esquerda (pNodoA *pt)
{
    pNodoA *ptu, *ptv;
    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1) pt->FB = 1;
    else pt->FB = 0;
    if (ptv->FB == 1) ptu->FB = -1;
    else ptu->FB = 0;
    pt = ptv;
    return pt;
}


pNodoA* rotacao_dupla_direita (pNodoA *pt)
{
    pNodoA *ptu, *ptv;
    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;
    if (ptv->FB == 1) pt->FB = -1;
    else pt->FB = 0;
    if (ptv->FB == -1) ptu->FB = 1;
    else ptu->FB = 0;
    pt = ptv;
    return pt;
}


pNodoA* localiza(pNodoA* pt, char* consulta) //função de busca da palavra da árvore
{
    while (pt != NULL)
    {
        if (strcmp(consulta, pt->palavra) ==  0) //consulta == a->palavra (caso encontrar a palavra)
        {
            return pt;
        }
        else if (strcmp(consulta, pt->palavra) <  0) //consulta < a->palavra (ordem alfabética)
        {
            pt = localiza(pt->esq, consulta);
            return pt;
        }
        else if (strcmp(consulta, pt->palavra) >  0) //consulta > a->palavra (ordem alfabética)
        {
            pt = localiza(pt->dir, consulta);
            return pt;
        }
        else
            return NULL;
    }
    return NULL;
}


pNodoA* insere_freq(pNodoA* pt, char ante[30], char pal[30])
//verifica se a palavra já está na lista de adjacentes, se sim,soma 1 ao float freq_a da estrutura de dados
//do elemento a que a palavra repetida se refere, se não, chama outra funcao(insere_freq2) para inserir um novo elemento
{
    pNodoA *ptaux = localiza(pt,ante); //ponteiro auxiliar para o nodo da palavra na AVL cuja lista de palavras
    //ajacentes será criada/atualizada


    PtNo *ptfreq = ptaux->lfreq; //ponteiro auxiliar para percorrer a lista

    while(ptfreq !=NULL)
    {
        if(strcmp(ptfreq->info.pal_b, pal) == 0) //se a palavra já está na lista, soma um na estrutura->frequencia e sai da funcao
        {
            ptfreq->info.freq_b++;
            //puts(ptaux->palavra);
            //puts(ptfreq->info.pal_b);
            //printf("freq = (%.6f)\n", ptfreq->info.freq_b);
            return pt;
        }

        ptfreq = ptfreq->lfreq;
    }
    return insere_freq2(pt, ante, pal);//inserir novo elemento na lista se a palavra não foi encontrada

}

pNodoA* insere_freq2 (pNodoA *pt, char ante[30], char pal[30])
//insere um novo elemento na lista
{
    pNodoA *ptaux = localiza(pt,ante); //ponteiro auxiliar para o nodo da palavra na AVL cuja lista de palavras
    //ajacentes será criada/atualizada

    PtNo *ptfreq = ptaux->lfreq; //ponteiro auxiliar para percorrer a lista

    PtNo *novo;

    /*aloca um novo nodo */
    novo = (PtNo*) malloc(sizeof(PtNo));

    /*insere a informação no novo nodo*/
    strcpy(novo->info.pal_b, pal);
    novo->info.freq_b = 1;

    if(ptfreq == NULL) //se o elemento inserido é o primeiro a ser inserido
    {
        novo->lfreq = NULL;
        ptaux->lfreq = novo;;
        return pt;
    }

    while(ptfreq->lfreq!=NULL) //se o elemento inserido não é o primeiro a ser inserido, insere no fim
        ptfreq = ptfreq->lfreq;

    ptfreq->lfreq = novo;
    novo->lfreq = NULL;

    return pt;

}



pNodoA* decrescente(pNodoA* pt, char pal[30])
//Torna uma lista de palavras relativas à palavra consultada decrescente, conforme o numero
//de frequencia na estrutura de dados
{
     pNodoA *ptaux = localiza(pt,pal); //ponteiro auxiliar para o nodo da palavra na AVL cuja lista de palavras será modificada
     PtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
     PtNo *ptaux2; //ponteiro auxiliar para percorrer a lista
     float a, b;
     char c[30];
     int swapped;

     if(ptaux == NULL)
     {
         printf("palavra nao esta no texto\n");
     }
     else
     {

         do //percorre a lista, mudando as palavras de lugar(swap) conforme o numero de frequencia(a e b)
         {
            swapped = 0;
            ptaux2=ptaux->lfreq;
            while (ptaux2->lfreq != ant) //enquanto a posicão atual na lista não for igual à anterior
            {
                a = ptaux2->info.freq_b; //a = frequencia do nodo relativo à palavra na lista
                strcpy(c, ptaux2->info.pal_b); //c = palavra do nodo na lista de palavras adjacentes
                b = ptaux2->lfreq->info.freq_b; //b = frequencia do nodo relativo à proxima palavra na lista

                if(a < b) // se a freqeuncia da palavra da lista for menor do que a frequencia da palavra seguinte da lista
                {
                    ptaux2->info.freq_b = b; //frequencia da palavra atual vira a frequencia da palavra seguinte
                    strcpy(ptaux2->info.pal_b, ptaux2->lfreq->info.pal_b); //palavra atual vira a palavra seguinte
                    strcpy(ptaux2->lfreq->info.pal_b, c); //palavra seguinte vira a palavra atual
                    ptaux2->lfreq->info.freq_b = a; //frequencia da palavra seguinte vira a frequencia da palavra atual
                    swapped = 1;
                }
                ptaux2=ptaux2->lfreq; //vai para o proximo elemento da lista
            }
            ant = ptaux2;

         }while(swapped);
     }
    return pt;
}

void formula(pNodoA* pt, char pal[])
//Calcula a formula da medida estatistica e substitui o valor inteiro na lista pelo valor da estatistica
{
    pNodoA *ptaux = localiza(pt,pal); //ponteiro auxiliar para o nodo da palavra na AVL cuja lista de palavras será modificada
    pNodoA *ptaux2 = pt;  //ponteiro auxiliar para o nodo da palavra na AVL que é adjacente à primeira palavra
    //para calculo da medida estatistica
    PtNo *ptaux3; //ponteiro auxiliar para percorrer a lista
    char lista[30];
    float a;
    float ab;
    float b;
    float estatistica;

     if(ptaux == NULL)
     {
         return;
     }
     else
     {
         a = ptaux->freq_a; //a = frequencia do nodo relativo à palavra na AVL
         ptaux3 = ptaux->lfreq;

          while(ptaux3 != NULL) //enquanto a lista não acabou
          {

            strcpy(lista, ptaux3->info.pal_b); //lista = palavra do nodo na lista de palavras adjacentes
            ab = ptaux3->info.freq_b; //ab = frequencia do nodo na lista de palavras adjacentes

            ptaux2 = localiza(pt,lista); //localiza a palavra na AVL que for igual à palavra na lista de adjacência
            b = ptaux2->freq_a; //a = frequencia do nodo relativo à palavra ajacente, na AVL
            ptaux2 = pt; //reseta o ponteiro ptaux2 para a raiz da AVL, pois será usado para fazer novas pesquisas durante a execução do while

            estatistica = (ab/(sqrt(a)*sqrt(b))); //formula da estatistica
            ptaux3->info.freq_b = estatistica; //troca o valor da porcentagem pela estatistica

            ptaux3 = ptaux3->lfreq; //vai para o proximo elemento da lista
         }
     }
}

void formula2(pNodoA* pt, char pal[], int cont, FILE *arq)
//Grava as palavras e a estatistica consultadas no novo arquivo texto
{
    pNodoA *ptaux = localiza(pt,pal);//ponteiro auxiliar para o nodo da palavra na AVL cuja lista de palavras será impressa no arquivo

    PtNo *ptaux3; //ponteiro auxiliar para percorrer a lista
    int i;
    char lista[30];

     if(ptaux == NULL)
     {
         return;
     }
     else
     {
         fprintf(arq, "\n");
         fprintf(arq, "Consulta: ");
         fprintf(arq, ptaux->palavra); //salva no arquivo a palavra encontrada na AVL
         fprintf(arq, "\n");

         ptaux3 = ptaux->lfreq;

         for(i=1; i<=cont; i++) //enquanto não chegar ao numero de palavras pesquisadas
         {

             if(ptaux3 != NULL) //se ainda não chegou no fim da lista
             {

                strcpy(lista, ptaux3->info.pal_b); //lista = palavra da lista de adjacentes

                fprintf(arq, "Sugestão: ");
                fprintf(arq, lista);  //salva no arquivo a palavra encontrada na lista de adjacentes
                fprintf(arq, "                  (%.6f)\n", ptaux3->info.freq_b); //salva no arquivo a frequencia ou estatistica

                ptaux3 = ptaux3->lfreq; //vai para o proximo elemento da lista
             }

         }
     }
}
void imprime2(pNodoA* pt, char pal[])
//funcao auxiliar para correcao de eventuais erros
{
     pNodoA *ptaux = localiza(pt,pal);
     PtNo* ptaux2;
     if (pt == NULL)
        puts("vazio");
     else
        for (ptaux2=ptaux->lfreq; ptaux2!=NULL; ptaux2=ptaux2->lfreq)
         printf("\nPalavra a = %s, Palavra b = %s, Frequencia = %.2f\n",ptaux->palavra, ptaux2->info.pal_b, ptaux2->info.freq_b);
}
