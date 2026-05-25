
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);

void myprintf(char *msg,char *formato,...);

int main(void)
{
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirEntero;
	arbol.comparar = &compararEntero;
	arbol.liberar = &free;
	int search;
	Resultado check;

	insertarArbol(&arbol, crearEntero(9));
	insertarArbol(&arbol, crearEntero(8));
	insertarArbol(&arbol, crearEntero(11));
	insertarArbol(&arbol, crearEntero(7));
	insertarArbol(&arbol, crearEntero(6));
	insertarArbol(&arbol, crearEntero(5));
	insertarArbol(&arbol, crearEntero(10));
	insertarArbol(&arbol, crearEntero(12));
	insertarArbol(&arbol, crearEntero(9));

	balancearArbol(&arbol);

	printf("ANTES DE INVERTIR\n");
	printf("\n");
	imprimirArbol(arbol);
	printf("\n\nQUE NODO BUSCA?\n");
	scanf("%d", &search);
	check = buscarEnArbol(arbol, &search);

	if (check.nodo != NULL)
    {
        printf("\nENCONTRADO: ");
        imprimirEntero(check.dato);
    }
    else
    {
        printf("\nno se encontro\n");
    }


	printf("\nDESPUES DE INVERTIR\n");
	printf("\n");
	invertirRamas(arbol.raiz);
	imprimirArbol(arbol);
	printf("\n");


	eliminarArbol(&arbol);
	printf("\n\n FIN DE PROGRAMA\n");
	return 0;
}


int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}


void myprintf(char* msg,char *formato,...)
{
	va_list args;
    va_start(args, formato);
	printf("\n %s ",msg);
	char *ptr = formato;
	while(*ptr!='\0')
	{
		switch(*ptr)
		{
			case 'd':
				printf("%d ",va_arg(args, int));
				break;
			case 'c':
				printf("%c ",va_arg(args, int));
				break;
			case 'f':
				printf("%f ",va_arg(args, double));
				break;
			case 'x':
				printf("%p ", (void*)va_arg(args, Arbol*));
				break;
		}
		ptr++;
	}
	va_end(args);
}
