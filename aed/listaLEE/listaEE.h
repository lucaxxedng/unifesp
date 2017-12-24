//Biblioteca com fun��es de implementa��o de Lista encadeada

#ifndef LISTAEE_H_INCLUDED
#define LISTAEE_H_INCLUDED
#define N 10
#endif 

//Declarando estrtura do tipo Lista Encadeada
struct info 
{
    int valor;
    int prox;
};
    typedef struct info tipoInfo;

struct listaEE 
{
    int tamanhoLista;
    int primeiro;
    int ultimo; // 0 ocupado, 1 livre
    int posLivre[N];
    tipoInfo elemento[N];
}; typedef struct listaEE tipoListaEE;


//Procedimento que inicializa a lista
void inicializaLista (tipoListaEE *listaAux) 
{


     // Inicializa elementos da lista
     listaAux->tamanhoLista = 0;
     listaAux->primeiro = -1;
     listaAux->ultimo = -1;

     int i;
       //Atribuindo valores zero e -1 a todos os elementos da lista. Indicando que a posi��o � livre (= 1)
     for (i = 0; i < N; i++) 
	 {
        listaAux->elemento[i].valor = 0;
        listaAux->elemento[i].prox = -1;
        listaAux-> posLivre[i] = 1;
    }
}

//Fun��o que indica qual a pr�xima posi��o livre
int proxPosLivre(tipoListaEE *listaAux)
{

    int i;
    //Procura um espa�o na lista que esteja vazio
    for (i = 0; i < N; i++)
	{
        if (listaAux->posLivre[i]== 1)
        return (i);
    }
 //Caso n�o haja espa�os a lista retorna -1
 return (-1);
}

//Insere um elemento no fim da lista
void insereElementoFinal (tipoListaEE *listaAux, int posicao) 
{

    if (posicao != -1)
	{
        scanf ("%d", &listaAux->elemento[posicao].valor);
    }

    //Atualiza elementos da lista conforme o seu tamanho
    if (listaAux->tamanhoLista != 0) 
	{

        listaAux->elemento[listaAux->ultimo].prox = posicao;
        listaAux->elemento[posicao].prox = -1;
        listaAux->tamanhoLista ++;
        listaAux->ultimo = posicao;
        listaAux->posLivre[posicao]= 0;
    }


    if (listaAux->tamanhoLista == 0) 
	{

        listaAux->primeiro = posicao;
        listaAux->ultimo = posicao;
        listaAux->posLivre[posicao] = 0;
        listaAux->tamanhoLista++;

    }
    printf ("Elemento adicionado com sucesso! \n");
}

//Insere um elemento antes do primeiro na lista
/*N�o est� sendo utilizada no programa pois o enfoque dele � para a remo��o de elementos*/
void insereElementoInicio (tipoListaEE *listaAux, int posicao) 
{

    //Guardamos o primeiro elemento em uma vari�vel
    int primeiroE = listaAux->primeiro;

    if (posicao!=-1) 
	{
        printf ("Digite o elemento da lista:  ");
        scanf ("%d", &listaAux->elemento[posicao].valor);
    }

    if (listaAux->tamanhoLista == 0) 
	{
        listaAux->primeiro = posicao;
        listaAux->posLivre[posicao] = 0;
        listaAux->tamanhoLista++;
    }

    //Atribuimos a listaAux->primeiro o novo indice do primeiro elemento.
    else 
	{
        listaAux->elemento[posicao].prox = primeiroE;
        listaAux->tamanhoLista++;
        listaAux->primeiro = posicao;
        listaAux->posLivre[posicao] = 0;
    }
    printf ("Elemento adicionado com sucesso!\n");

}

//Procedimento que insere um novo elemento exatamento no meio da lista
void insereElementoMeio (tipoListaEE *listaAux) 
{

    //Verificando em que lugar � o meio
    int meio = N/2;

    //Se n�o h� elementos, a leitura � direta
    if (listaAux->posLivre[meio] == 1) 
	{
        scanf ("%d", &listaAux->elemento[meio].valor);
    }

    if (listaAux->tamanhoLista == 0) {
        listaAux->primeiro = meio;
        listaAux->posLivre[meio] = 0;
    }

    else 
	{
        listaAux->elemento[listaAux->ultimo].prox = meio;
        listaAux->elemento[meio].prox = -1;
        listaAux->tamanhoLista++;
        listaAux->ultimo = meio;
        listaAux->posLivre[meio] = 0;
    }

    //Caso o contr�rio, o elemento que estava no meio � enviado para a pr�xima posi��o livre da lista
    if (listaAux->posLivre[meio] == 0) 
	{

        int posLivre = proxPosLivre(&listaAux);

        listaAux->elemento[posLivre].valor = listaAux->elemento[meio].valor;
        listaAux->elemento[posLivre].prox = listaAux->elemento[meio].prox;
        listaAux->posLivre[posLivre] = 0;

        int i;

        for (i = 0; i < N; i++) 
		{
            if (listaAux->elemento[i].prox == meio)
			{
                listaAux->elemento[i].prox = posLivre;
            }
        }

        //Feito isso podemos adicionar o elemento no meio da lista
        int ultimo;
        ultimo = listaAux->ultimo;

        scanf ("%d", &listaAux->elemento[meio].valor);

        listaAux->elemento[ultimo].prox = meio;
        listaAux->elemento[meio].prox = -1; listaAux->tamanhoLista++; listaAux->posLivre[meio] = 0;

    }
}

//Procedimento que remove o primeiro elemento da lista
void removeElementoInicio (tipoListaEE *listaAux) 
{
    int primeiroA = listaAux->primeiro;
    //Resetamos o �ndice onde estava o primeiro
    //O pr�ximo elemento ao primeiro se torna o novo primeiro.
    listaAux->primeiro = listaAux->elemento[primeiroA].prox;
    listaAux->elemento[primeiroA].valor = 0;
    listaAux->elemento[primeiroA].prox = -1;
    listaAux->posLivre[primeiroA] = 1;
    listaAux->tamanhoLista--;

}

//Procedimento que remove o �ltimo elemento da lista
void removeElementoFinal (tipoListaEE *listaAux) 
{

    int i;
    int ultimo;

    ultimo = listaAux->ultimo;

    //Zeramos o �ltimo elemento
    listaAux->elemento[ultimo].valor = 0;
    listaAux->elemento[ultimo].prox = -1;
    listaAux->posLivre[ultimo] = 1;
    listaAux->tamanhoLista--;

    //Procuramos o pen�ltimo elemento da lista. Ele se tornar� o novo �ltimo elemento.
    for (i = 0; i < N; i ++) 
	{
        if (listaAux->elemento[i].prox == ultimo) 
		{
            listaAux->elemento[i].prox = -1;
            listaAux->ultimo = i;
            break;
        }
    }

}

//Procedimento que remove elementos intermedi�rios
void removeElementoIntermediario (tipoListaEE *listaAux, int indice) 
{

    int i;

    //O elemento que tinha o elemento a ser apagado como pr�ximo tem como novo pr�ximo o pr�ximo do elemento apagado
    /*Ilustrando temos que por exemplo:
    indice: 4
    elemento: 5
    pr�x: indice 5

    indice: 5
    elemento: 4
    pr�x: �ndice 6

    indice: 6
    elemento 2

    se apagarmos o �ndice 5, o pr�x do �ndice 4 se torna o �ndice 6 que era o pr�ximo do �ndice 5 que foi apagado*/
    for (i = 0; i < N; i++) 
	{
        if (listaAux->elemento[i].prox == indice) 
		{
             listaAux->elemento[i].prox = listaAux->elemento[indice].prox;
             break;
        }
    }
    //Zeramos o �ndice que foi apagado
    listaAux->elemento[indice].valor = 0;
    listaAux->elemento[indice].prox = -1;
    listaAux->posLivre[indice] = 1;
    listaAux->tamanhoLista --;
}

//Procedimento que imprime a lista para verifica��o
void imprimeLista (tipoListaEE *listaAux) 
{
    int i;
    for (i = 0; i < N; i++)
	{
        if (listaAux->posLivre[i] == 0) 
		{
            printf ("%d\n", listaAux->elemento[i].valor);

        }
    }
}


