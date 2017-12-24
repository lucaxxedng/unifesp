//Thauany Moedano
//RA 92486

/*  Encontrar se dado um grafo G e v�rtices A e B, se A e B s�o mutualmente relacionados. Para isso
    � utilizado o algoritmo de CFC's. Este algoritmo segue a ideia do pseudo-algoritmo passado em aula
    com uma adapta��o. Ao inv�s de separar os conjuntos CFC's em �rvores, existe uma numera��o para cada
    conjunto: 1, 2, 3... . Quando executa o DFS no grafo transposto para encontrar o conjunto de CFC,
    um vetor CFCgroup marca quais v�rtices pertencem ao grupo atual. Por exemplo: Se o DFS roda para o
    v�rtice 5 com a variavel numGroup marcado em 1 e encontra os v�rtices 2 e 3 ent�o CFCgroup[5], CFCgroup[2]
    e CFCgroup[3] recebem o numGroup 1 indicando que pertencem ao mesmo conjunto CFC. Ent�o a vari�vel numGroup
    � incrementada para computar o pr�ximo conjunto de v�rtices.
*/

#include <iostream>
#include <stack>
#include <stdlib.h>

using namespace std;
//Definindo estruturas
typedef struct{
int v;
int w;
} Edge;
Edge EDGE(int, int);
typedef struct graph *Graph;
Graph GRAPHinit (int);
void GRAPHinsertE (Graph, Edge);
void GRAPHremoveE (Graph, Edge);
Graph GRAPHcopy (Graph);
void GRAPHdestroy (Graph);

typedef struct node *link;
struct node {
    int v;
    link next;
};
struct graph {
    int V;
    int E;
    link *adj;
};

link NEW (int v, link next) {
    link x = (link) malloc (sizeof *x);
    x->v = v;
    x->next = next;
 return x;
}

Graph GRAPHinit (int V) {
 int v;
 Graph G = (Graph) malloc (sizeof *G);
 G->V = V;
 G->E = 0;
 G->adj = (link*) malloc (V*sizeof (link));
 for (v=0;v<V; v++)
    G->adj[v] = NULL;
 return G;
}

void GRAPHinsertE (Graph G, Edge e) {
    int v = e.v, w = e.w;
    G->adj[v] = NEW (w, G->adj[v]);
    G->E++;
}
/*  Funcao que verifica se o vertice v tem um vizinho n�o marcado
    caso sim, retorna o v�rtice. caso n�o, retorna -1
*/
int GRAPHsearch(Graph G, int v, int mark[]) {
    link t;

    for (t = G->adj[v]; t != NULL; t = t->next) {
        if(mark[t->v] == 0) {
            return(t->v);
        }
    }
    return(-1);

}

///Execu��o do DFS
/*  G: grafo, r: vertice inicial, mark: vetor que controla os vertices visitados,
    f[]: tempo de entrada, p[]: predecessor, l[]: tempo de saida, flagD_t: flag que indica
    se estamos tratando o grafo transposto ou n�o, numGroup: ID de cada conjunto de CFC,
    CFCGroup[]: vetor que inidica a que conjunto CFC pertence cada vertice, passedAll:
    variavel que verifica se todos os v�rtices foram marcados na execu�ao do CFC com G transpoto,
    markAll: variavel que verifica se todos os v�rtices foram marcados na execu��o do CFC com G
*/

void DFS(Graph G, int r, int mark[], int f[], int p[], int l[], int flagD_t, int numGroup, int CFCgroup[],
         int& passedAll, int& markAll, int &i) {
    int u, v;
    stack<int> S;
    f[r] = i;
    mark[r] = 1;
    markAll += 1; //Assinalando que o primeiro elemento foi marcado
    S.push(r); //empilha o elemento de origem
    if(flagD_t) {
      CFCgroup[r] = numGroup;
      passedAll += 1;
    }

    while(!S.empty()) {
        u = S.top(); //Assinala u como topo
        i++;
        v = GRAPHsearch(G, u, mark); //verifica se u tem um vizinho nao marcado

        if(v != -1) {
            mark[v] = 1;
            markAll += 1;
            S.push(v); //Marca e empilha v
            p[v] = u;
            f[v] = i;
            if(flagD_t) { //Se tratando do G transposto, assinala a qual conjunto CFC, v pertence
                CFCgroup[v] = numGroup;
                passedAll += 1;
            }
        }
        else { //Se o v�rtice u nao tem um vizinho, desempilha e marca o tempo de saida
            S.pop();
            l[u] = i;
        }
    }
}

/*  Fun��o que verifica qual o maior tempo de saida de G. quando encontrado, o tempo de saida
    � simbolicamente apagado sendo escrito como -1. A fun��o retorna o v�rtice com o maior
    tempo de sa�da.
*/
int maxlv(int N, int l[]) {
    int i, maior = -1, verticeChose = 0;
    for(i = 0; i < N; i++) {
        if(l[i] > maior) {
            maior = l[i];
            verticeChose = i;
        }
    }
    l[verticeChose] = -1;

    return(verticeChose);
}

// CFC: Fun��o que encontra os conjuntos de CFC's

void CFC(Graph G, Graph G_t, int mark[], int mark_t[], int f[], int f_t[], int l[], int l_t[],
         int p[], int p_t[], int N, int CFCgroup[]) {

    int i = 0, j = 0, v = 0, passedAll = 0, numGroup = 1, markAll = 0;
    /* Enquanto houver v�rtice n�o marcado em G, executar DFS a partir de v. MarkAll � uma vari�vel
      que verifica se todos os v�rtices foram marcados
    */
    while(markAll < N) {
        while(mark[v] == 1)
            v++;
        DFS(G, v, mark, f, p, l, 0, -1, CFCgroup, passedAll, markAll, i);
        v = 0;
    }

    /* Para cada v�rtice ainda n�o marcado em G transposto em ordem descrecente de l[v], executar
    DFS(G transposto, v). A vari�vel passedAll verifica se todos os v�rtices em G transposto foram
    marcados. numGroup controla a qual grupoCFC cada v�rtice pertence.
    */



    while(passedAll < N) {
        v = maxlv(N, l);
        if(mark_t[v] == 0) {
            DFS(G_t, v, mark_t, f_t, p_t, l_t, 1, numGroup, CFCgroup, passedAll, markAll, j);
            numGroup++;
        }
    }
    /*v�rtices isolados recebem n�meros de grupos separadamente*/
    numGroup++;
    for(i = 0; i < N; i++) {
        if(CFCgroup[i] == 0) {
            CFCgroup[i] = numGroup;
            numGroup++;
        }
    }

}

int main() {

    int N, M, P, i, A, B, origin, wanted;

    Graph G;
    Graph G_t;
    Edge e, e_t;

    cin >> N;
    cin >> M;
    int f[N], l[N], p[N], f_t[N], l_t[N], p_t[N], mark[N], mark_t[N], CFCgroup[N];
    G = GRAPHinit(N);
    G_t = GRAPHinit(N);
    //inicializando os vetores
    for(i = 0; i < N; i++) {
        f[i] = 0;
        l[i] = 0;
        p[i] = 0;
        f_t[i] = 0;
        l_t[i] = 0;
        p_t[i] = 0;
        mark[i] = 0;
        mark_t[i] = 0;
        CFCgroup[i] = 0;
    }
    //Computando as arestas de G e G transposto
    for(i = 0; i < M; i++) {
        cin >> A;
        cin >> B;
        e.v = A;
        e.w = B;
        e_t.v = B;
        e_t.w = A;
        GRAPHinsertE(G, e);
        GRAPHinsertE(G_t, e_t);
    }
    CFC(G, G_t, mark, mark_t, f, f_t, l, l_t, p, p_t,  N, CFCgroup);

    cin >> P;
    for(i = 0; i < P; i++) {
        //Se os v�rtices pertencem ao mesmo grupo, s�o mutualmente excluvisos
        cin >> origin;
        cin >> wanted;
        if(CFCgroup[origin] == CFCgroup[wanted])
            cout << "1" << endl;
        else
            cout << "0" << endl;
    }

    return 0;
}
