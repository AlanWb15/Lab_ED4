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

void invertirArbol(Arbol *arbol);
void invertirRama(NodoA *raiz);
void eliminarArbol(Arbol *arbol);
void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);
void imprimirOrden(Arbol arbol,int opcion);
void eliminarNodo(Arbol *arbol, void *dato);
void imprimirResultado(Resultado resultado, Arbol *arbol);
void imprimirEntero(void *dato);
int altura(NodoA *nodo);
void profundidad(Arbol arbolA, Arbol arbolB);
int compararNodos(NodoA *a, NodoA *b, int (*comparar)(void*, void*));
int  compararEstructura(NodoA *a, NodoA *b);
void compararArboles(Arbol arbolA, Arbol arbolB);
void ordenArr(NodoA *raiz, void **arreglo, int *indice);
void reordenar(Arbol *arbol, void **datos, int inicio, int fin);
void equilibrar(Arbol *arbol);

#endif
