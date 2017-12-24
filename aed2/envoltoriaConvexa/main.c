//Thauany Moedano
//RA 92486

///////////////////////////////////////////////////////////////////////////
// Envolt�ria convexa
///////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////
// Structure para armazenar os pontos 2d
///////////////////////////////////////////////////////////////////////////
typedef struct
{
  int x;
  int y;
} ponto2D;

///////////////////////////////////////////////////////////////////////////
//  Prototipos das funcoes
///////////////////////////////////////////////////////////////////////////
void calculaEnvoltoria (ponto2D **pontos, int nPontos, ponto2D **envoltoria, int *nEnvoltoria);
double areaComSinal (ponto2D *p1, ponto2D *p2, ponto2D *p3);
void *mallocX (unsigned int nbytes);
void leCoordenadas (ponto2D **pontos, int *nPontos);
void escreveCoordenadas (ponto2D **pontos, int nPontos);
void ordenadaPorX (ponto2D **pontos, int n);
void trocaPontos2D (ponto2D *a, ponto2D *b);

///////////////////////////////////////////////////////////////////////////
// Funcao principal
///////////////////////////////////////////////////////////////////////////
int main ()
{
  int nPontos, nEnvoltoria, i;
  ponto2D *pontos, *envoltoria;

  // Lendo a lista de coordenadas
  leCoordenadas (&pontos, &nPontos);

  // Ordenando a lista de coordenatas
  // sem esse passo, a funcao calculaEnvoltoria
  // nao retornara o resultado esperado
  ordenadaPorX (&pontos, nPontos);

  // Calculando a envoltoria convexa
  calculaEnvoltoria (&pontos, nPontos, &envoltoria, &nEnvoltoria);

  // Escrevendo a envoltoria convexa
  escreveCoordenadas (&envoltoria, nEnvoltoria);

  free (pontos);
  free (envoltoria);

  return (0);
}


///////////////////////////////////////////////////////////////////////////
// IMPLEMENTE SEU ALGORITMO DE ORDENACAO AQUI
///////////////////////////////////////////////////////////////////////////

/* A ideia era usar um algoritmo est�vel o que elimina de cara Selection, Heap e Quicksort. Tamb�m � invi�vel utilizar algum m�todo
em tempo linear. O MergeSort seria uma �tima op��o mas ele usa mem�ria auxiliar... O que talvez n�o fosse bom ao armazenar coordenadas na envolt�ria que j� usa vetor auxiliar.
Logo escolhi o Bubble que embora tenha O(n�) � um m�todo simples in place*/
void ordenadaPorX (ponto2D **pontos, int nPontos) //Bubble Sort
{
  int i, j;
  for(i = 0; i < nPontos; i++) {

    for(j = 1; j < (nPontos-i); j++) {
        if((*pontos)[j].x < (*pontos)[j-1].x)
            trocaPontos2D(&(*pontos)[j], &(*pontos)[j-1]);
    }
  }

}

void trocaPontos2D (ponto2D *a, ponto2D *b)
{
  ponto2D aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

///////////////////////////////////////////////////////////////////////////
// IMPLEMENTE O CALCULO DA ENVOLTORIA CONVEXA AQUI
///////////////////////////////////////////////////////////////////////////
void calculaEnvoltoria (ponto2D **pontos, int nPontos,
                        ponto2D **envoltoria,  int *nEnvoltoria)
{
    /*A envolt�ria � dividida em duas partes: Superior e inferior. Come�amos calculando a parte superior*/
    int i, inferior = 0; //Iniciando o contado inferior da envolt�ria
    (*envoltoria) = mallocX ((nPontos+1) * sizeof (ponto2D)); //Alocando vetor envoltoria
    *nEnvoltoria = 0; //Iniciando o contador da posi��o do vetor

    //Calculando superior, vai de zero ao ultimo ponto de *pontos
    for (i = 0; i < nPontos; i++) {

        //Verificando se � necess�rio excluir pontos da envoltoria
        while(areaComSinal(&(*envoltoria)[*nEnvoltoria-2], &(*envoltoria)[*nEnvoltoria-1], &(*pontos)[i]) > 0.0 && *nEnvoltoria >= 2)
            *nEnvoltoria -= 1; //Sempre que os pontos estiverem em sentido anti-hor�rio, devemos elimin�-lo, diminuindo nosso vetor

        //Ao final sempre o i-�simo ponto � colocado
         (*envoltoria)[*nEnvoltoria] = (*pontos)[i];
         *nEnvoltoria += 1;

    }
    //Como o while sempre soma +1 na envolt�ria. No fim da itera��o a envolt�ria ter� um ponto duplicado e devemos exclu�-lo
    *nEnvoltoria-=1;

    //O processo � similar na envolt�ria inferior
    //Calculando parte inferior. Como o �ltimo ponto sempre � colocado na superior. Come�amos em nPontos-2 at� zero
    for (i = nPontos-1; i >= 0; i--) {

        //Verificando se precisa excluir pontos
        while(areaComSinal(&(*envoltoria)[*nEnvoltoria-2], &(*envoltoria)[*nEnvoltoria-1], &(*pontos)[i]) > 0.0 && inferior >= 2) {
            *nEnvoltoria -= 1;
            inferior--; //Utilizamos um contador auxiliar
        }

         (*envoltoria)[*nEnvoltoria] = (*pontos)[i];
         *nEnvoltoria += 1;
         inferior++;

    }
    //No fim nEnvoltoria fica com um n�mero a mais. Ent�o diminuimos um da envoltoria
   *nEnvoltoria-=1;
}

double areaComSinal (ponto2D *p1, ponto2D *p2, ponto2D *p3)
{
  return ((*p2).x - (*p1).x) * ((*p3).y - (*p1).y) -
         ((*p2).y - (*p1).y) * ((*p3).x - (*p1).x);
}

///////////////////////////////////////////////////////////////////////////
// Auxiliary functions to read and write data
///////////////////////////////////////////////////////////////////////////

void *mallocX (unsigned int nbytes)
{
  void *ptr;
  ptr = malloc (nbytes);
  if (ptr == NULL)
  {
    printf ("Memoria insuficiente!\n");
    exit (EXIT_FAILURE);
  }
  return ptr;
}

void leCoordenadas (ponto2D **pontos, int *nPontos)
{
  int i;

  scanf ("%d", nPontos);
  (*pontos) = mallocX ((*nPontos) * sizeof (ponto2D));

  for (i = 0; i < (*nPontos); i++)
    scanf ("%d %d", &(*pontos)[i].x, &(*pontos)[i].y);

}

void escreveCoordenadas (ponto2D **pontos, int nPontos)
{
  int i;


  for (i = 0; i < nPontos; i++)
    printf ("%d %d \n", (*pontos)[i].x, (*pontos)[i].y);

    printf ("%d %d \n", (*pontos)[0].x, (*pontos)[0].y);
}

