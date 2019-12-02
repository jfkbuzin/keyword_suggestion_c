#include "func_trab.h"
//cd UFRGS\Estruturas de Dados\Trab Livros\tj\bin\Debug

int main(int argc, char *argv[])
//argc eh um inteiro que conta quantos parametros foram passados pela linha de comando
//argv guarda o texto dos parametros, argv[1] eh o primeiro parametro, argv[2] eh o segundo paramento, etc
{
    char linha[1000]; //para armazenar as linhas do arquivo;
    FILE *entrada, *consulta, *saida; //ponteiros para os arqivos de entrada e saída
    char *palavra=NULL;
    char anterior[30];
    char pal[30];
    int ok;

    clock_t start, end, elapsed;

    //const char s[30] = " ,#$.'!?:;/\\\\\"1234567890-  \n";
    const char s[50] = {" *0123456789, .&%\?!;/-'@\"$#=><()][}{:\n\t"};

    int cont;

    pNodoA* arv=NULL;

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    if (argc != 5)
    {
        printf("Numero incorreto de parametros.\n Sintaxe: minhaaplicacao arq_origem arq_consulta arq_destino numero\n");
        return 1;
    }
    else
    {
        entrada = fopen (argv[1], "r"); // abre para leitura o arquivo passado como parametro
        saida = fopen (argv[3],"w"); // cria o arquivo de saida
        consulta = fopen (argv[2], "r");
        cont = atoi(argv[4]);

        if (entrada == NULL || saida == NULL || consulta == NULL)
        {
            printf("Arquivo nao encontrado.\n");
            return 1;
        }
        else
        {
            start=clock();
            while(!feof(entrada))
            {
                if(fgets(linha,1000,entrada) != NULL)
                {

                    if (linha[0] != '\n')
                    {
                        palavra = (char*)strtok(linha, s); //primeira palavra da linha

                        if(palavra != NULL)
                        {
                            palavra = strlwr(palavra);

                            strcpy(anterior, palavra); //a palavra atual vai ser a anterior no subwhile
                            arv = InsereAVL(arv, palavra, &ok); //insere a primeira palavra da linha na AVL
                            //puts(palavra);

                            while(palavra != NULL) //da segunda palavra da linha até o fim da linha
                            {
                                palavra = (char*)strtok(NULL, s);
                                palavra = strlwr(palavra); //torna todas as letras minusculas


                                if(palavra != NULL)
                                {
                                    strcpy(pal, palavra); //captura a palavra subsequente
                                    arv = insere_freq(arv, anterior, pal); //insere a palavra subsequente na sublista, se ela ainda não está
                                    //o codigo abaixo tem que sempre estar abaixo do insere_freq
                                    strcpy(anterior, palavra); //a palavra atual vai ser a anterior na proxima vez que rodar o while
                                    arv = InsereAVL(arv, pal, &ok); //insere a palavra na AVL, se a palavra ainda não está na lista

                                }

                            }
                        }

                    }


                }
            }


            fclose(entrada);

            while(!feof(consulta))
            {
                if(fgets(linha,1000,consulta) != NULL)//lê as palavras do arquivo de consulta
                {
                    if (linha[0] != '\n')
                    {
                        palavra = (char*)strtok(linha, s);
                        palavra = strlwr(palavra);

                        strcpy(pal, palavra);

                        formula(arv, pal); //calcula a formula
                        arv = decrescente(arv, pal);//torna a lista decrescente conforme a medida estatistica
                        formula2(arv, pal, cont, saida);//imprime a lista no arquivo de saida
                        //imprime2(arv, pal);


                    }
                }
            }

            end=clock();
            elapsed = 1000 * (end - start) / (CLOCKS_PER_SEC); //calcula o tempo decorrido em milissegundos
            fprintf(saida, "\nO tempo gasto na tokenizacao do arquivo foi de %ld ms\n", elapsed);
            printf("\nO tempo gasto na tokenizacao do arquivo foi de %ld ms\n", elapsed);

            fclose(consulta);
        }

        fclose(saida);
        printf("\nArquivo %s criado, palavras consultadas : %d.\n",argv[3],cont);
        return 0;
    }

}
