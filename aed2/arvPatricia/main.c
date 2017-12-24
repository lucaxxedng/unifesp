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
	int digito;
} TNo;

int retornaDigito(TChave x, int digito)
{
	return ((x >> digito) & 1);
}

int EhInterno(TArvBin No)
{
	return ((No == NULL) || (No->Esq != NULL) || (No->Dir != NULL));
}

int EhExterno(TArvBin No)
{
	return ((No != NULL) && (No->Esq == NULL) && (No->Dir == NULL));
}

TArvBin Inicializa()
{
	return NULL;
}

TArvBin Pesquisa(TArvBin No, TChave x)
{   //Semelhante a patricia, se o n� � NULL, retorna NULL
	if(No == NULL)
        return NULL;
   //Se � interno devemos pesquisar para a direita ou esquerda
    else if(EhInterno(No)) {

        if(retornaDigito(x, No->digito) == 1)
            return(Pesquisa(No->Dir, x));

        else if(retornaDigito(x, No->digito) == 0)
            return(Pesquisa(No->Esq, x));
    }
    //Se o N� � externo verifico:
    else if(EhExterno(No)) {
        if(No->Item.Chave == x) //Se a chave � igual retorno o NO
            return(No);
        else
            return(NULL); //Senao retorno NULL
    }
}

//InsereEntre acha a nova posi��o que foi pulada durante a inser��o
void InsereEntre(TArvBin *Raiz, TItem x, int d) {

    //Ser� criado um NoInterno e um NoExterno
    TArvBin NoInterno, NoExterno;
    //Se o n� � interno e o d�gito � maior que o d�gito do N�, devemos deslocar nossa inser��o at� encontrar o lugar correto
    if(EhInterno(*Raiz) && d > (*Raiz)->digito) {

        if(retornaDigito(x.Chave, (*Raiz)->digito) == 1)
            InsereEntre(&(*Raiz)->Dir, x, d);
        else
            InsereEntre(&(*Raiz)->Esq, x, d);

    }
    //Quando chegamos em um n� externo, devemos verificar pra que lado ocorrer� as modifica��es
    else {
        //Primeiro j� deixamos criado o novo n� interno de separa��o
        NoInterno = (TArvBin) malloc(sizeof (TNo));
        NoInterno->digito = d;
        //E tamb�m ja criamos o N� externo que ser� inserido
        NoExterno = (TArvBin) malloc(sizeof (TNo));
        NoExterno->Esq = NULL;
        NoExterno->Dir = NULL;
        NoExterno->Item = x;
        //Se o d�gito for 1, o N� externo � inserido � Direita, e a Raiz desloca para a esquerda
        if(retornaDigito(x.Chave, d) == 1) {
            NoInterno->Dir = NoExterno;
            NoInterno->Esq = (*Raiz);
            (*Raiz) = NoInterno;
        }
        //Se o d�gito � zero ent�o basta fazer a ordem inversa
        else {
            NoInterno->Esq = NoExterno;
            NoInterno->Dir = (*Raiz);
            (*Raiz) = NoInterno;
        }
    }
}
//Fun��o que procura qual � o d�gito incomum entre duas chaves
int achaDigitoDiferenciador(TArvBin NoAux, TItem x) {
    int d = 0;
    while(retornaDigito(NoAux->Item.Chave, d) == retornaDigito(x.Chave, d))
        d++;
    return d;
}

int Insere(TArvBin *pRaiz, TItem x)
{   //O insere funciona de maneira semelhante
    TArvBin NoAux; //Utilizamos um auxiliar para achar o d�gito diferenciador
    NoAux = *pRaiz;
    int digitoDiferenciador;

    if(*pRaiz == NULL) {

        NoAux = (TArvBin) malloc(sizeof (TNo));
        NoAux->Esq = NULL;
        NoAux->Dir = NULL;
        NoAux->Item = x;
        *pRaiz = NoAux;
        return(1);
    }

    else {
        //Enquanto o n� � interno caminha na �rvore
        while(EhInterno(NoAux)) {
            if(retornaDigito(x.Chave, NoAux->digito) == 1)
               NoAux = NoAux->Dir;
            else if(retornaDigito(x.Chave, NoAux->digito) == 0)
                NoAux = NoAux->Esq;
        }
        //Se as chaves sao iguais, retorno zero
        if(x.Chave == NoAux->Item.Chave)
            return(0);
        //Se as chaves n�o s�o iguais, descobrimos em qual d�gito ela se diferencia
        else {
            digitoDiferenciador = achaDigitoDiferenciador(NoAux, x);
            InsereEntre(pRaiz, x, digitoDiferenciador); //E usamos InsereEntre para rearranjar a �rvore
            return(1); //Retorno de 1 para inser��o com sucesso
        }
    }
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
		printf("(");
		if (EhExterno(No))
			printf("C%d", No->Item.Chave);
		else
			printf("D%d", No->digito);
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
	scanf("%d", &x.Chave);
	if (Pesquisa(Raiz, x.Chave) == NULL)
		Insere(&Raiz, x);
	Imprime(Raiz);
	Libera(&Raiz);

	return 0;
}
