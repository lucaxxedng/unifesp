//*******************************************************************
// Lista de Exerc�cios : Aula 05
// Autor: Thauany Moedano
// Matricula: 92486
// Data: 06/10/2014
// Curso : BCT Noturno - Turma B
// Prof: Val�rio Rosset
//*******************************************************************


/* Exerc�cio LDDE -

a) Escreva uma rotina para remo��o do primeiro
elemento de uma LCD-DE.

b) Escreva uma fun��o para remo��o do elemento
intermedi�rio de uma LCD-DE*/


#include <stdio.h>
#include <stdlib.h>
#include "listaLDDE.h"


int main()
{
    //Declarando o tipo lista LDDE
    tipoLDDE listaTeste;

    //Inicializando
    inicializaLista(&listaTeste);

    int opcao = 0;

    //Criando la�o
    while (opcao != 4) 
	{

        printf ("Digite 1 - Adicionar elemento, 2 - Remover, 3 - Imprimir, 4 - Sair: ");
        scanf ("%d", &opcao);

        //Op��o 1 - Adiciona elemento
        if (opcao == 1) 
		{
            //Como o excercicio tem foco em remo��o s� � utilizada inser��o ao final da lista
            insereElementoFinal(&listaTeste);
        }

        //Op�� 2 - remove um elemento da lista
        else if (opcao == 2) 
		{
            int valor;
            //Lendo o valor a ser removido
            scanf ("%d", &valor);

            //Dependendo da posi��o do valor, um tipo diferente de remo��o ser� implementado
            if (valor == listaTeste.primeiro->info) 
			{
                removeElementoInicio(&listaTeste);
            }

            else if (valor == listaTeste.ultimo->info)
			{
                removeElementoFim(&listaTeste);
            }
            else 
			{
                //Para remover elementos intermedi�ros procuramos quais os antecessores e sucessores do elemento
                tipoElemento *valoR = buscaValor(&listaTeste, valor);
                tipoElemento *ant;
                tipoElemento *prox;

                ant = valoR->ant;
                prox = valoR->prox;
                removeElementoIntermedario(&listaTeste, valoR, ant, prox);
            }
        }
        //Op��o 3 - imprime a lista
        else if (opcao == 3) 
		{
            imprimeLista(&listaTeste);
        }

        else if (opcao == 4) 
		{
            return(0);
        }


    }
	return (0);
}
