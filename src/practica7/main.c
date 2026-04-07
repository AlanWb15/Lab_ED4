
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <iostring.h>
#include <arbol.h>
#include "variable.h"
#include "expresion.h"


void abortar(void);
void ordenIterativo(NodoA *raiz,void (*imprimir)(void*));
void imprimirDoubleDouble(void *);

int main(void)
{
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.imprimir = &imprimirVariable;
	arbol.comparar = &compararVariable;
	arbol.liberar = &free;
	
	
	//NOTA
	arbol.cantidad = 7; // <<-- ACTUALIZAR ESTE VALOR SI SE CREA MANUALMENTE EL ARBOL	
	arbol.raiz = crearNodoA(crearVariable('^'));	
	arbol.raiz->izq = crearNodoA(crearVariable('X'));	
	arbol.raiz->dch = crearNodoA(crearVariable('^'));	
	arbol.raiz->dch->izq = crearNodoA(crearVariable('X'));	
	arbol.raiz->dch->dch = crearNodoA(crearVariable('^'));	
	arbol.raiz->dch->dch->izq = crearNodoA(crearVariable('X'));	
	arbol.raiz->dch->dch->dch = crearNodoA(crearVariable('Y'));	
	
	printf("\n ARBOL\n");
	imprimirArbol(arbol);
	evaluar(arbol);

	
	
	eliminarArbol(&arbol);

	printf("\n\n FIN DE PROGRAMA\n");
	
	
	return 0;
}


void imprimirDoubleDouble(void *ptr)
{
	double **ptrdouble= ptr;	
	if(!ptrdouble)	
	{		
		printf("null ") ;
		return;
	}
	printf("%lf ",**ptrdouble); 
}

void ordenIterativo(NodoA *raiz,void (*imprimir)(void*))
{
	Pila pila = {NULL,0,-1,imprimir,NULL};
	if(!raiz)
		return;
	NodoA* aux = raiz;
	while( aux || !pilaVacia(pila))
	{			
		while(aux)
		{
			pushDato(&pila,aux);	
			aux = aux->izq;
		}		
		aux = popDato(&pila);
		imprimir(aux);		
		printf(" ");		
		aux= aux->dch;
	}	
	vaciarPila(&pila);
}

void abortar(void)
{
	char c = 'e';
	if( (c=getchar()) == 'e')
		exit(0);
}
