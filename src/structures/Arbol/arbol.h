#ifndef ARBOL_H
#define ARBOL_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>

#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
#define INVERSO 4
#define IZQUIERDA 0
#define DERECHA 1

typedef struct
{
	NodoA *padre;
	NodoA *nodo;
	void *dato;
	int rama;
}Resultado;

typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
}Arbol;


void eliminarArbol(Arbol *arbol);
void eliminarDato(Arbol *arbol, void *dato);
void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);
void imprimirOrden(Arbol arbol,int opcion);
Resultado buscarEnArbol(Arbol arbol, void *dato);
int altura(NodoA *raiz);
void invertirRamas(NodoA *raiz);
void compararArboles(Arbol arbolA, Arbol arbolB);
void balancearArbol(Arbol *arbol);
void profundidad(Arbol arbolA, Arbol arbolB);
void equilibrar(Arbol *arbol);

#endif
