    //Thauany Moedano
    //RA 92486
     ///Algoritmo que dado percursos em ordem e pr� ordem devolve uma �rvore bin�ria de busca///
    #include <stdio.h>
    #include <stdlib.h>

    typedef int TChave;

    typedef struct {
        TChave Chave;
        /* outros compomentes */
    } TItem;

    typedef struct SNo *TArvBin;

    typedef struct SNo {
        TItem Item;
        TArvBin Esq, Dir;
    } TNo;

    TItem *Aloca(int n)
    {
        return ((n > 0) ? ((TItem *) malloc(n * sizeof(TItem))) : (NULL));
    }

    int Carrega(TItem **PreOrdem, TItem **EmOrdem)
    {
        int i, n;

        scanf("%d", &n);

        (*PreOrdem) = Aloca(n);
        for (i = 0; i < n ; i++)
            scanf("%d", &(*PreOrdem)[i].Chave);

        (*EmOrdem) = Aloca(n);
        for (i = 0; i < n ; i++)
            scanf("%d", &(*EmOrdem)[i].Chave);

        return n;
    }

    void Libera(TArvBin *pNo)
    {
        TArvBin No;

        No = *pNo;
        if (No != NULL) {
            Libera(&No->Esq);
            Libera(&No->Dir);
            free(No);
            (*pNo) = NULL;
        }
    }

    //Fun��o recursiva que devolve uma �rvore constru�da a partir de dois vetores

    TArvBin Constroi(TItem *PreOrdem, TItem *EmOrdem, int esq, int dir, int *no) //N� � passado por referencia
    {

        TArvBin pNo = NULL; //Declarando um n� nulo
        int raiz;
        if (esq <= dir) { //Enquanto esq for diferente de direita n�veis de recurs�o s�o chamados

            for (raiz = esq; raiz <= dir; raiz++) {

                if ((PreOrdem)[*no].Chave == (EmOrdem)[raiz].Chave) { //Procuro o n� da pr� ordem no vetor em ordem

                    TNo* No = (TNo*) malloc (sizeof(TNo)); //Crio uma sub�rvore com esse n� encontrado
                    No->Item = (PreOrdem)[*no];
                    *no += 1;
                    No->Esq = Constroi(PreOrdem, EmOrdem,esq, raiz-1, &(*no)); //Os filhos esq e dir s�o procurados a partir de cortes no vetor em ordem
                    No->Dir = Constroi(PreOrdem, EmOrdem,  raiz+1, dir, &(*no));
                    pNo = No;

                }
            }

        //Quando a recurs�o acaba, deveria retornar uma �rvore

        }
          return(pNo);

    }








    void PosOrdem(TArvBin No)
    {
        if(No != NULL) {
            PosOrdem(No->Esq); //Imprimindo em p�s ordem - Primeiro Imprime todos os filhos esq
            PosOrdem(No->Dir); //Dir e depois a raiz
            printf("%d ", No->Item.Chave);
        }
        printf("\n");
    }

    int main()
    {
        TItem *PreOrdem, *EmOrdem;
        TArvBin Raiz = NULL;
        int n, esq = 0, dir, no = 0;

        n = Carrega(&PreOrdem, &EmOrdem);
        dir = n - 1;
        Raiz = Constroi(PreOrdem, EmOrdem,  esq, dir, &no);
        PosOrdem(Raiz);
        Libera(&Raiz);
        free(EmOrdem);
        free(PreOrdem);

        return 0;
    }
