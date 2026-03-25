#include "pila.h"

int comparar(void *x, void *y)
{
	int a = *(int *)x;
	int b = *(int *)y;
	if (a > b)
	{
		return 1;
	}
	if (a < b)
	{
		return (-1);
	}
	
	return 0;
}

void *check(Pila *p)
{
	if(pilaVacia(p))
	{
		return NULL;
	}
	return(p->cima->dato);
}

void ordenarPila(Pila *pila, void(*comparar)(void*,void*))
{
	Pila *aux;
	void *actual;
	aux->cima = NULL;
	while(!pilaVacia(pila))
	{
		actual = popDato(pila);
		
		while(!pilaVacia(aux) && comparar(check(aux), actual)>0)
		{
			pushDato(pila, popDato(&aux));
		}
		pushDato(&aux, actual);
	}
	
	while(!pilaVacia(&aux))
	{
		pushDato(pila, popDato(&aux));
	}
	
}

int main()
{
	int i=0;
	int val[7] = {9, 3, 2, 10, 6, 5, 8};
	Pila pila = {NULL, 0, 7, imprimirEntero, NULL};
	for(i; i<7; i++)
	{
		pushDato(&pila, &valores[i]);
	}
	printf("pila OG\n");
	imprimirPila(pila);
	ordenarPila(&pila, comparar);
	printf("pila ordenada\n");
	imprimirPila(pila);
}