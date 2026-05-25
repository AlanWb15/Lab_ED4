#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>


int* crearEntero(int dato);
void imprimirEntero(void *a);
int compararEntero(void *a, void *b);

int main(void)
{
    Arbol arbolA = {NULL, 0, &imprimirEntero, &compararEntero, &free};
    Arbol arbolB = {NULL, 0, &imprimirEntero, &compararEntero, &free};
	int opc, valor, aux;

	do{

	printf("\nMENU DE ARBOLES");
	printf("\n1.Insertar arbol A ");
	printf("\n2.Insertar arbol B ");
	printf("\n3.Comparar arboles");
	printf("\n4.Eliminar dato A");
	printf("\n5.Eliminar dato B ");
	printf("\n6.Profundidades ");
	printf("\n7.Equilibrar ");
	printf("\n8.Mostrar Arboles ");
	printf("\n9.Salir ");
	printf("\n");
	scanf("%d", &opc);


	switch(opc){

		case 1:


				printf("Dame numero entero\n");
				scanf("%d", &aux);

				insertarArbol(&arbolA, crearEntero(aux));

			break;

		case 2:


   			 	printf("Dame numero entero\n");
    			scanf("%d", &aux);

    			insertarArbol(&arbolB, crearEntero(aux));

			break;
		case 3:
    		compararArboles(arbolA, arbolB);
    		break;

    		case 4:
                printf("Valor a eliminar en Arbol A: ");
                scanf("%d", &valor);
                eliminarDato(&arbolA, &valor);
                break;

            case 5:
                printf("Valor a eliminar en Arbol B: ");
                scanf("%d", &valor);
                eliminarDato(&arbolB, &valor);
                break;


            case 6:
                profundidad(arbolA, arbolB);
                break;


            case 7:
                equilibrar(&arbolA);
                equilibrar(&arbolB);
                break;

			case 8:
				printf("\nArbol A:\n");
				imprimirArbol(arbolA);
				printf("\n\nArbol B:\n");
				imprimirArbol(arbolB);
				printf("\n");
				break;

			case 9:
				printf("\nLiberando memoria (postorden)...\n");
				eliminarArbol(&arbolA);
				eliminarArbol(&arbolB);
				printf("FIN DE PROGRAMA\n");
				break;

			default:
				printf("Opcion invalida.\n");
				break;
		}

	}while(opc != 9);

	return 0;
}

int* crearEntero(int dato)
{
    int *nuevo = malloc(sizeof(int));
    *nuevo = dato;
    return nuevo;
}

int compararEntero(void *a, void *b)
{
    int *aa = a, *bb = b;
    if (*aa == *bb) return 0;
    else if (*aa < *bb) return -1;
    else return 1;
}

void imprimirEntero(void *a)
{
    int *aa = a;
    printf("%d", *aa);
}
