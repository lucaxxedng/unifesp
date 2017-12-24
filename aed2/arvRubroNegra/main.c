//Thauany Moedano
//RA: 92486

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
	int cor; //1 - rubro ; 0 - negro
} TNo;

//Calcula a altura Negra de uma �rvore qualquer
int AlturaNegra(TArvBin No)
{
    int esq, dir;
    if(No == NULL)
        return(0);
    else {
        esq = AlturaNegra(No->Esq); //Conta a altura negra da esquerda
        dir = AlturaNegra(No->Dir); //Conta a altura negra da direita
    }

    if(esq > dir)
        return(EhNegro(No)+esq); //Retorna somente o n�mero de n�s negros
    else
        return(EhNegro(No)+dir);
}

int EhNegro(TArvBin No)
{
return (No == NULL) || (No->cor == 0);
}
int EhRubro(TArvBin No)
{
return (No != NULL) && (No->cor == 1);
}

//Verifica se uma �rvore � Rubro Negra
int ArvoreARN(TArvBin No)
{
    if(No == NULL || (ArvoreARN(No->Esq) && ArvoreARN(No->Dir))) //Se o n� e NULL e se Dir e Esq s�o ARN, a �rvore � ARN
        return(1);

    //Se a Altura Negra da direita e da esquerda s�o diferentes ou se existem duplos rubros, a �rvore n�o � ARN
    if(AlturaNegra(No->Dir) != AlturaNegra(No->Esq) || (EhRubro(No) && (EhRubro(No->Esq) || EhRubro(No->Dir))))
        return(0);

}
//Fun��o que inverte as cores de um n�
void TrocaCores(TArvBin No)
{
    if(No != NULL) {
    if(EhNegro(No)) //Se o n� � negro, ele passa a ser rubro
        (No)->cor = 1;
    else if(EhRubro(No)) //Se o n� � rubro, ele passa a ser negro
        (No)->cor = 0;
    }
}

void RotacaoDireita(TArvBin *pA)
{
	TArvBin pB = (*pA)->Esq;
	(*pA)->Esq = pB->Dir;
    pB->Dir = (*pA);
    (*pA) = pB;
}

void RotacaoEsquerda(TArvBin *pA)
{
    TArvBin pB = (*pA)->Dir;
	(*pA)->Dir = pB->Esq;
    pB->Esq = (*pA);
    (*pA) = pB;
}


void BalancaNo(TArvBin *Avo, TArvBin *Pai, TArvBin *Filho)
{
    TArvBin Tio; //Declarando e definindo o tio
    //Verificando se � necess�rio rebalancear a �rvore
    if(EhRubro(*Pai) && EhRubro(*Filho) && (Avo) != NULL) {

        //Definindo quem � o tio
        if((*Avo)->Esq == (*Pai))
            Tio = (*Avo)->Dir;
        else if((*Avo)->Dir == (*Pai))
            Tio = (*Avo)->Esq;

        //Caso 01 - Tio � rubro - basta colorir todos os envolvidos
        if(EhRubro(Tio)){
            TrocaCores(*Pai);
            TrocaCores(Tio);
            TrocaCores(*Avo);
        }
        //Caso 02 - Tio �  negro
         else if(EhNegro(Tio)) {

            if((*Avo)->Dir == (*Pai)){
                if((*Pai)->Esq == (*Filho)) //Subcaso 02 - Pai e filho de lados opostos, fa�o uma rota��o para cair no subcaso 03
                    RotacaoDireita(Pai);
                TrocaCores(*Avo); //Subcaso 02 - Troca cores e faz uma rota��o no av�
                TrocaCores(*Pai);
                RotacaoEsquerda(Avo);

            }
            //Os mesmos casos se repetem de maneira sim�trica
            else if((*Avo)->Esq == (*Pai)){
                if((*Pai)->Dir == (*Filho))
                    RotacaoEsquerda(Pai);
                TrocaCores(*Avo);
                TrocaCores(*Pai);
                RotacaoDireita(Avo);
            }
        }
    }
 }


TArvBin Inicializa()
{
	return NULL;
}
//Fun��o que insere um n�
int InsereRec(TArvBin *Pai, TArvBin *Avo, TItem x) {

    if (*Pai == NULL) { //Caso a pesquisa seja sem sucesso inserimos utilizando a aloca��o
        TNo* No = (TNo*) malloc (sizeof(TNo));
        No->cor = 1;
        No->Item = x;
        No->Esq = NULL;
        No->Dir = NULL;
        *Pai = No;
        return(1);
    }
    //Caso contr�rio percorremos a �rvore
     else {
        if (x.Chave > (*Pai)->Item.Chave) {
                InsereRec(&(*Pai)->Dir, Pai, x);
                BalancaNo(Avo, Pai, &(*Pai)->Dir); //Toda vez que um n� � inserido, verificamos se � preciso balancear
        }
        else if (x.Chave < (*Pai)->Item.Chave) {
                InsereRec(&(*Pai)->Esq, Pai, x);
                BalancaNo(Avo, Pai, &(*Pai)->Esq);
        }
        else if (x.Chave == (*Pai)->Item.Chave)
            return(0);
    }

}

void Insere(TArvBin *pRaiz, TItem x)
{
	InsereRec(pRaiz, NULL, x);
	if((*pRaiz)!=NULL)
        (*pRaiz)->cor = 0;
}

void Carrega(TArvBin *pNo)
{
	int i, n;
	TItem x;

	scanf("%d", &n);
	for (i = 0; i < n ; i++) {
		scanf("%d", &x.Chave);
		Insere(pNo, x);
	}
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

void Imprime(TArvBin No)
{
	if (No != NULL) {
		if (EhNegro(No))
			printf("(N%d", No->Item.Chave);
		else
			printf("(R%d", No->Item.Chave);
		Imprime(No->Esq);
		Imprime(No->Dir);
		printf(")");
	}
	else
		printf("()");
}

int main()
{
	TArvBin Raiz;
	TItem x;

	Raiz = Inicializa();
	Carrega(&Raiz);
	if (ArvoreARN(Raiz)) {
		printf("%d\n", AlturaNegra(Raiz));
		Imprime(Raiz);
	}
	Libera(&Raiz);

	return 0;
}
