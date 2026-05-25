#include "arbol.h"

Resultado buscarEnArbol(Arbol arbol, void *dato)
{
	Resultado result = {NULL, NULL, NULL, DERECHA};
	NodoA *raiz = arbol.raiz;

	while(raiz)
	{
		if(arbol.comparar(raiz->dato, dato)==0)
		{
			result.nodo =raiz;
			result.dato=raiz->dato;
			break;
		}
		else if(arbol.comparar(raiz->dato, dato)>0)
		{
			result.padre=raiz;
			result.rama = IZQUIERDA;
			raiz = raiz->izq;
		}
		else
		{
			result.padre=raiz;
			result.rama = DERECHA;
			raiz= raiz->dch;
		}
	}
		return result;
}

void invertirRamas(NodoA *raiz)
{
	if(!raiz)
		return;
	NodoA *aux = raiz->izq;
	raiz->izq = raiz-> dch;
	raiz->dch = aux;
	invertirRamas(raiz->izq);
	invertirRamas(raiz->dch);
}


void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(!raiz->izq)
			raiz->izq = crearNodoA(dato);
		else if(!raiz->dch && comparar(dato,raiz->dato)==0)
			raiz->dch = crearNodoA(dato);
		else
			insertarArbolOrdenado(raiz->izq,dato,comparar);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}



void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}



void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);
}


void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN:
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN:
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO:
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN:
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}


void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq,liberar);
	eliminar_NodosA(raiz->dch,liberar);
	//LIBERAR
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
}


void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}


void eliminarDato(Arbol *arbol, void *dato)
{
		Resultado res = buscarEnArbol(*arbol, dato);//raiz
		if(!res.nodo)
			return;

		NodoA *aux= res.nodo;
		if(arbol->cantidad ==1 )
		{
		eliminarArbol(arbol);
		return;
		}

	else if(!aux->izq || !aux->dch)
	{
		NodoA *hijo = aux->izq ? aux->izq : aux->dch;

		if(!res.padre) // raíz
			arbol->raiz = hijo;
		else if(res.rama == IZQUIERDA)
			res.padre->izq = hijo;
		else
			res.padre->dch = hijo;

		arbol->liberar(aux->dato);

	free(aux);
	}
	else
	{
		NodoA *padreSuc = aux;
		NodoA *suc = aux->dch;

		while(suc->izq)
		{
   			padreSuc = suc;
    		suc = suc->izq;
		}

		aux->dato = suc->dato;

		if(padreSuc->izq == suc)
    		padreSuc->izq = suc->dch;
		else
    		padreSuc->dch = suc->dch;
		free(suc);
	}
}


int iguales(NodoA *a, NodoA *b, int (*comparar)(void*,void*))
{
	if(!a && !b) return 1;
	if(!a || !b) return 0;

	if(comparar(a->dato, b->dato) != 0)
		return 0;

	return iguales(a->izq, b->izq, comparar) &&
	       iguales(a->dch, b->dch, comparar);
}

void llenarArray(NodoA *raiz, void **arr, int *i)
{
	if(!raiz)
		return;

	llenarArray(raiz->izq, arr, i);
	arr[*i] = raiz->dato;
	(*i)++;
	llenarArray(raiz->dch, arr, i);
}

int mismosDatos(Arbol arbolA, Arbol arbolB)
{
	if(arbolA.cantidad != arbolB.cantidad)
		return 0;

	void *arr1[arbolA.cantidad];
	void *arr2[arbolB.cantidad];

	int i=0, j=0;

	llenarArray(arbolA.raiz, arr1, &i);
	llenarArray(arbolB.raiz, arr2, &j);

	for(int k=0; k<arbolA.cantidad; k++)
	{
		if(arbolA.comparar(arr1[k], arr2[k]) != 0)
			return 0;
	}
	return 1;
}

void compararArboles(Arbol arbolA, Arbol arbolB)
{
	if(iguales(arbolA.raiz, arbolB.raiz, arbolA.comparar))
	{
		printf("\nSon IGUALES en estructura y datos");
		return;
	}

	if(mismosDatos(arbolA, arbolB))
	{
		printf("\nTienen los mismos DATOS pero distinta estructura");
		return;
	}

	printf("\nSon DIFERENTES");
}

int altura(NodoA *raiz)
{
	if(!raiz)
		return 0;

	int izq = altura(raiz->izq);
	int der = altura(raiz->dch);

	return (izq > der ? izq : der) + 1;
}

NodoA* construirBalanceado(void **arr, int ini, int fin)
{
	if(ini > fin)
		return NULL;

	int mid = (ini + fin) / 2;

	NodoA *nuevo = crearNodoA(arr[mid]);

	nuevo->izq = construirBalanceado(arr, ini, mid - 1);
	nuevo->dch = construirBalanceado(arr, mid + 1, fin);

	return nuevo;
}

void balancearArbol(Arbol *arbol)
{
	if(!arbol->raiz)
		return;

	void *arr[arbol->cantidad];
	int i = 0;

	llenarArray(arbol->raiz, arr, &i);

	eliminar_NodosA(arbol->raiz, NULL);

	arbol->raiz = construirBalanceado(arr, 0, arbol->cantidad - 1);
}

void profundidad(Arbol arbolA, Arbol arbolB)
{
    int profA = altura(arbolA.raiz);
    int profB = altura(arbolB.raiz);

    printf("\nProfundidad Arbol A: %d", profA);
    printf("\nProfundidad Arbol B: %d", profB);

    if (profA > profB)
        printf("\nEl Arbol A es mas profundo");
    else if (profB > profA)
        printf("\nEl Arbol B es mas profundo");
    else
        printf("\nAmbos arboles tienen la misma profundidad");
}

void equilibrar(Arbol *arbol)
{
    balancearArbol(arbol);
    printf("\nArbol equilibrado. Nueva profundidad: %d", altura(arbol->raiz));
}
