        //Thauany Moedano
        //RA 92486

        #include <stdio.h>
        #include <stdlib.h>
        #include <math.h>

        //Definindo um Arranjo em TItem Chave
        typedef int  TChave;

        typedef struct  {
         TChave Chave;
        /* outros compomentes */
        } TItem;

        //Fun��o para alocar este Arranjo
            TItem *Aloca(int n)
        {
            return ((n > 0) ? ((TItem *) malloc(n * sizeof(TItem))) : (NULL));
        }

        //Fun��o que carrega o n�mero de itera��es, o quanto custa para exibir o filme e as receitas
        int Carrega(TItem **A)
        {
            int i, n, receita, C, lucroZero = 1; //Variavel que verifica se o mo�o ter� lucro algum dia

            scanf("%d", &n); //Lendo quantas vezes o algoritmo ira rodar
            scanf("%d", &C); //Lendo o custo C para exibir o filme

            (*A) = Aloca(n); //Alocando um espa�o na mem�ria para A

            for (i = 0; i < n ; i++) {
                scanf("%d", &receita);
                (*A)[i].Chave = receita - C; //O vetor vai armazenar apenas os lucros do individuo que e o queremos analisar
                if(receita > C)
                    lucroZero = 0; //Caso a receita seja maior do que zero, significa que ele ter� algum lucro em exibir o filme
            }
            if(lucroZero == 1)
                n = 0; //Se todas as receitas s� derem prejuizo, o algoritmo retorna o valor de n zerado (n�o havera dias para comparar o lucro)
            return n;
        }

        //Fun��o que resolve o caso do meio separadamente
        int EncontraLucroMeio(TItem *A, int menor, int maior, int meio) {
            //Definindo as somas para valores pequenos
            int somaE = -5000, somaD = -5000, soma = 0, i, j;
            //primeiramente devemos encontrar a soma da direita, procurando quais os valores que fornecem o maior lucro
            for(i = meio+1; i <= maior; i++) {

                soma+= A[i].Chave;
                if(soma > somaD)
                    somaD = soma;

            }

            soma = 0;
            //A mesma coisa para a soma da esquerda
            for(j = meio; j >= menor; j--) {

                soma += A[j].Chave;
                if(soma > somaE)
                    somaE = soma;

            }
           // printf("%d %d", somaD, somaE);
            return(somaD+somaE);

        }

        //Fun��o que encontra o lucro maximo
        int EncontraLucroMaximo(TItem *A, int menor, int maior){//, int *lucro) {

            int meio, somaE, somaD, somaM;
            //Condi��o de parada
            if(maior == menor)
                return(A[menor].Chave);

            else {
                meio = (menor+maior)/2;
                somaE = EncontraLucroMaximo(A, menor, meio); //Chamadas recursivas
                somaM = EncontraLucroMeio(A, menor, maior, meio);
                somaD = EncontraLucroMaximo(A, meio+1, maior);

                //Verificando qual dos subproblemas fornece o maior lucro
                if(somaE >= somaD && somaE >= somaM)
                    return(somaE);


                else if(somaD >= somaE && somaD >= somaM)
                    return(somaD);


                else
                    return(somaM);

            }

        }

      void Libera(TItem **A)
    {
        if ((*A) != NULL) {
            free(*A);
            (*A) = NULL;
        }
    }
        int main()
        {


            int C, i, N, lucro;
            TItem *A;
            N = Carrega(&A);
            if(N == 0) //Se N � zero, o algoritmo n�o � executado. O mo�o nao teve lucro e portanto aparecer� zero na tela
                printf("%d\n", 0);
            else{ //Caso contr�rio, basta calcular o lucro de acordo com a fun��o
            lucro = EncontraLucroMaximo(A, 0, N-1); //Definindo o lucro
            printf("%d\n", lucro); //printando o lucro
            }


            Libera(&A);

            return 0;
        }
