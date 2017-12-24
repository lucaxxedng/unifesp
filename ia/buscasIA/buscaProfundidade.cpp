/* Busca em Profundidade para resolver o problema 8-puzzle
(Quebra cabe�a de oito pe�as).
Thauany Moedano
RA: 92486 */
#include <iostream>
#include <stack>
#include <string>
#include <list>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>

#define PIECES 3

using namespace std;

/* Estruturas utilizadas para o trabalho */
typedef struct
{
   	int v;
   	int w;
} Edge;
Edge EDGE(int, int);
typedef struct graph *Graph;

/* Estrutura de inicializa��o da matriz. Monta uma matriz com os valores aleat�rios.
** Uma f�rmula de pseudo-gera��o de valores aleat�rias � utilizada.
** params: n�mero de linhas (rows) e colunas (columns).
** return: matriz de inteiros para associar ao grafo.
*/
int **MATRIXint (int r, int c)
{
    int i, j;
    int numbers[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int chosenNumber;
    int **t = (int **) malloc (r * sizeof (int *));

    for (i = 0; i < r; i++)
        t[i] = (int *) malloc (c * sizeof (int));

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
        {
            do
            {
                srand((unsigned)time(0));
                int maior = 8;
                int menor = 0;
                chosenNumber = rand()%(maior-menor+1) + menor;
            } while(numbers[chosenNumber] == 1);
            numbers[chosenNumber] = 1;
            t[i][j] = chosenNumber;
        }
    return t;
}

/* Estrutura do grafo */
struct graph { int V; int E; int **adj; };
Graph GRAPHinit (int V)
{
    Graph G = (Graph) malloc (sizeof *G);
    G->V = V;
	G->E = 0;
    G->adj = MATRIXint (V, V);
    return G;
}

/* Fun��o de inser��o de valores */
void GRAPHinsertE (Graph G, Edge e, int peca)
{
    int v = e.v, w = e.w;
    G->adj[v][w] = peca;
}

/* Fun��o que verifica se a matriz atual corresponde ao estado-objetivo esperado
** param: id que representa o estado da matriz
** return: true se chegou ao resultado, falso se for o contr�rio
*/
bool verificaEhObjetivo(string id)
{
    string estadoFinal = "012345678";

   if(id.compare(estadoFinal) == 0)
        return true;

    return false;
}

/* Fun��o que dado um grafo G, gera um ID �nico para a matriz daquele grafo. O Id � extraido
** das posi��es das pe�as na matriz. Por exemplo, se o estado �:
** 2 0 1
** 8 5 4
** 3 6 7
** O id gerado ser� "201854367"
** params: Grafo G
** return: Id do grafo G
*/
string geraId(Graph G)
{
    int a, b;
    stringstream peca;
    for(int a = 0; a < PIECES; ++a)
    {
        for(int b = 0; b < PIECES; ++b)
        {
            peca << G->adj[a][b];

        }
    }
    return peca.str();
}

/* Fun��o que verifica se a troca j� n�o gera um estado visitado.
** params: Grafo G, linha e coluna do estado desejado, linha e coluna do estado atual e uma lista
** que cont�m todos os IDs dos estados visitados.
** return: true se a troca gera um n�o visitado. Falso do contr�rio.
*/
bool testaTroca(Graph G, int linha, int coluna, int& xPos, int& yPos, list<string> listIDs)
{

    int troca = G->adj[linha][coluna];
    G->adj[xPos][yPos] = troca;
    G->adj[linha][coluna] = 8;

    string id = geraId(G);

    troca = G->adj[xPos][yPos];
    G->adj[linha][coluna] = troca;
    G->adj[xPos][yPos] = 8;

    if((find(listIDs.begin(), listIDs.end(), id) == listIDs.end()))
    {
        return true;
    }
    return false;
}

/* Verifica se � poss�vel mover para um novo estado
** params: Grafo G, posi��o X e Y da pe�a em branco, lista com os IDs j� visitados
** return 1 caso seja poss�vel. 0 do contr�rio.
*/
int getProximo(Graph G, int& xPos, int& yPos, list<string> listIDs, int ordem[])
{
    int linha = xPos;
    int coluna = yPos;
    srand((unsigned)time(0));
    int maior = 4;
    int menor = 1;
    int chosenNumber;
    srand((unsigned)time(0));
    for(int i = 0; i < 30; ++i)
    {

        chosenNumber = rand()%(maior-menor+1) + menor;

        if(xPos+1 <= 2  && testaTroca(G, linha+1, coluna, xPos, yPos, listIDs) && chosenNumber == ordem[3])
        {
             xPos += 1;
             return 1;
        }

        else if(yPos-1 >= 0  && testaTroca(G, linha, coluna-1, xPos, yPos, listIDs) && chosenNumber == ordem[1])
        {
             yPos -= 1;
             return 1;
        }

        else if(yPos+1 <= 2 && testaTroca(G, linha, coluna+1, xPos, yPos, listIDs) && chosenNumber == ordem[2])
        {
             yPos += 1;
             return 1;
        }

        else if(xPos-1 >= 0  && testaTroca(G, linha-1, coluna, xPos, yPos, listIDs) && chosenNumber == ordem[0])
        {
             xPos -= 1;
             return 1;
        }
    }
    srand((unsigned)time(0));
    return 0;
}

/* Algoritmo de busca em largura que procura a solu��o para o quebra cabe�a de oito pe�as
** params: grafo G, posi��o X e Y da pe�a em branco
*/
void DFS (Graph G, int& xPos, int& yPos, int &numMov)
{
    cout << "Calculando... " << endl;

    clock_t start, timePassed;
    int profundidade = 0;
    int xPosAnterior, yPosAnterior, saveXPos, saveYPos, troca;
    list<string> listIDs;
    stack<int> linhaS;
    stack<int> colunaS;
    string idAtual = geraId(G);
    int ordem[4] = {1, 2, 3, 4};

    linhaS.push(xPos);
    colunaS.push(yPos);

    start = clock();
    timePassed = clock();
    while(!verificaEhObjetivo(idAtual) && (((float)timePassed-start)/CLOCKS_PER_SEC < 90))
    {

        listIDs.push_back(idAtual);
        saveXPos = xPos;
        saveYPos = yPos;

        //Faz um movimento
        if(getProximo(G, xPos, yPos, listIDs, ordem))
        {
            xPosAnterior = saveXPos;
            yPosAnterior = saveYPos;
            troca = G->adj[xPos][yPos];
            G->adj[xPosAnterior][yPosAnterior] = troca;
            G->adj[xPos][yPos] = 8;

            linhaS.push(xPos);
            colunaS.push(yPos);

            idAtual = geraId(G);
            profundidade += 1;
        }
        //Se todos os movimentos geram estados j� visitados, desempilha o n�
        else
        {
            if(!linhaS.empty())
            {
                troca = G->adj[xPosAnterior][yPosAnterior];
                G->adj[xPos][yPos] = troca;
                G->adj[xPosAnterior][yPosAnterior] = 8;

                linhaS.pop();
                colunaS.pop();
                xPos = xPosAnterior;
                yPos = yPosAnterior;

                linhaS.pop();
                colunaS.pop();

                xPosAnterior = linhaS.top();
                yPosAnterior = colunaS.top();

                linhaS.push(xPos);
                colunaS.push(yPos);
            }
        }

        numMov+=1;
        timePassed = clock();
        for(int i = 0; i < 4; ++i)
        {
            ordem[i] += 1;
            if(ordem[i] > 4)
                ordem[i] = 1;

        }

    }

    cout << "Algorimo terminou: " << endl;
    if(idAtual.compare("012345678") ==  0)
        cout << "Solucao encontrada!" << endl;
    else
    {
        cout << "O algoritmo nao encontrou solucao." << endl;

    }
    cout << "Matriz final: " << endl;
    for(int a = 0; a < PIECES; ++a)
    {
        for(int b = 0; b < PIECES; ++b)
        {
            if(G->adj[a][b] == 8)
                cout << "  ";
            else
                cout << G->adj[a][b] << " ";

        }
        cout << endl;
    }
    cout << "Tempo final: " << ((float)timePassed-start)/CLOCKS_PER_SEC << endl;
    cout << "N�mero de movimentos: " << numMov << endl;
    cout << endl;

}

int main()
{
    Graph G;
    int xPos, yPos;
    G = GRAPHinit(PIECES);
    int numMov = 0;

    for(int a = 0; a < PIECES; ++a)
    {
        for(int b = 0; b < PIECES; ++b)
        {

            if(G->adj[a][b] == 8)
            {
                xPos = a;
                yPos = b;
                cout << "  ";
            }
            else
                cout << G->adj[a][b] << " ";
        }
        cout << endl;
    }

    DFS(G, xPos, yPos, numMov);
    return 0;
}
