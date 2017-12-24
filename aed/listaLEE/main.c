//*******************************************************************
// Lista de Exerc�cios : Aula 03
// Autor: Thauany Moedano
// Matricula: 92486
// Data: 29/09/2014
// Curso : BCT Noturno - Turma NB
// Prof: Val�rio Rosset
//*******************************************************************

/* Exerc�cio 5) Escreva uma rotina completa para remover qualquer elemento da lista EE.*/
#include <stdio.h>
#include <stdlib.h>
#include "listaEE.h"
#define N 10 /*Definimos um N constante uma vez que este exerc�cio s� mostra a respeito da exclus�o de elementos sem
                nenhum contexto espec�fico. Em uma abordagem mais detalhada N deve ser substitu�do por outra constante
                ou um n�mero digitado pelo usu�rio*/

int main() {

    //Tipo lista encadeada
    tipoListaEE testeListaEE;

    //Chamando procedimento que inicializa
    inicializaLista(&testeListaEE);

    //Declarando variaveis
    int opcao = 0;
    int posicao;
    int indice;
    int i;
    int valor;
    int valorEncontrado = 0;

    //Iniciando la�o de repeti��o para manipula��o da lista encadeada
    while (opcao != 4) 
	{

		//Imprimindo isntru��es e lendo op��o do teclado
		printf ("Digite uma uma opcao. 1 - Adiciona, 2 - Remove, 3 - Imprime, 4 - Sair: ");
		scanf ("%d", &opcao);

		//Op��o 1 - Adiciona um novo elemento na lista
		/*Somente � utilizado inser��o ao final pois o enfoque do exerc�cio � remo��o de elementos. Entranto
		na biblioteca constam todos os tipos de inser��o*/

		if (opcao == 1) 
		{

			printf ("Digite um elemento: ");
			posicao = proxPosLivre(&testeListaEE);

			//Caso a lista esteja cheia uma mensagem de erro aparecer�
			if (posicao == -1) 
			{
				printf ("Erro!. Lista est� cheia");
			}

			else 
			{
				insereElementoFinal(&testeListaEE, posicao);
			}
		}

		//Op��o 2 - Remove um elemento da lista
		if (opcao == 2) 
		{

			printf ("Digite o valor a ser exclu�do da lista: ");
			scanf ("%d", &valor);

			//Verificando se o valor digitado pertence a lista
			for (i = 0; i < N; i++) 
			{
				if (testeListaEE.elemento[i].valor == valor) 
				{
					indice = i;
					valorEncontrado = 1;
					break;
				}
			}

			//Caso n�o perten�a uma mensagem de erro aparecer�
			if (valorEncontrado == 0) 
			{
				printf ("Erro!. Valor n�o encontrado");
			}

			//Se o elemento for o primeiro utilizamos a rotina de eliminar o primeiro
			if (indice == testeListaEE.primeiro) 
			{
				removeElementoInicio(&testeListaEE);
			}
			//Se o elemento for o �ltimo utilizamos a rotina de eliminar o �ltimo
			else if (indice == testeListaEE.ultimo) 
			{
				removeElementoFinal(&testeListaEE);
			}
			//Para outros elementos utilizamos a rotina geral de elementos itnermedi�rios
			else 
			{
				removeElementoIntermediario(&testeListaEE, indice);
			}
			//Uma mensagem de remo��o aparecer� na tela
			if (valorEncontrado == 1) 
			{
				printf ("Elemento removido com sucesso!\n");
			}
		}
		//Op��o 3 - Imprime lista para verifica��o
		if (opcao == 3) 
		{
			imprimeLista(&testeListaEE);
		}
		//Op��o 4 - Encerra o programa
		if (opcao == 4) 
		{
			return (0);
		}

	}
}
