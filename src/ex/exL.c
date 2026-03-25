#include <stdio.h>
#include <stdlib.h>


typedef struct Nodo 
{
	int dato;
	struct Nodo *sig; 
	struct Nodo *ante;

}Nodo;

typedef struct Lista
{
	Nodo *inicio;
	Nodo *final;
	int Tam;
	
}Lista;

void capturarDato(Lista *lista, int dato);
void crearNodo(Nodo **nodo, int dato);

int main(void)
{
	//inicializas lista
	Lista *lista = {NULL, NULL, 0};
	
	capturarDato(lista, 2);
	
}
void crearNodo(Nodo **nodo, int dato)
{
	
	(*nodo) = malloc(sizeof(Nodo));
	(*nodo)->dato = dato;
	(*nodo)->sig = NULL;
	(*nodo)->ante = NULL;



}
void capturarDato(Lista *lista, int dato)
{
	//creamos nodo
	Nodo nuevoNodo;
	crearNodo(&nuevoNodo, dato);
	
	//hacemos auxiliar
	Nodo *aux = lista->inicio;

	//verificamos que tenga algo el inicio de lista
	if(aux!= NULL)
	{

		while(aux!=NULL)
		{
			aux = aux->sig;

		}
		nuevoNodo.ante = aux;
		aux->sig = &nuevoNodo;

		lista->final= &nuevoNodo;
	
		
	}
	
}

