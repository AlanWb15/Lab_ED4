#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>


int main(void)
{
	Arbol arbolA = {NULL, 0, NULL, NULL, NULL};
	Arbol arbolB = {NULL, 0, NULL, NULL, NULL};
	int opc, valor, i, aux;
	
	do{

	printf("MENU DE ARBOLES");
	printf("\n1.Insertar arbol A ");
	printf("\n2.Insertar arbol B ");
	printf("\n3.Comparar arboles");
	printf("\n4.Eliminar dato A");
	printf("\n5.Eliminar dato B ");
	printf("\n6.Profundidades ");
	printf("\n7.Equilibrar ");
	printf("\n8.Mostrar Arboles ");
	printf("\n9.Salir ");
	scanf("%d", &opc);
	

	switch(opc){
		
		case 1:
			do{
			
				printf("Dame numero entero\n");
				scanf("%d", &aux);
				
				insertarArbol(&arbolA, &aux);
				printf("otro? si=1, no=0\n"); scanf("%d", &i);
				
			}while(i==1);
			break;

		case 2:
			do{
    	
   			 	printf("Dame numero entero\n");
    			scanf("%d", &aux);
    
    			insertarArbol(&arbolA, &aux);
    			printf("otro? si=1, no=0\n"); scanf("%d", &i);
    
			}while(i==1);
			break;
		case 3:
				compararArboles(arbolA, arbolB);
				break;
 
			case 4:
				printf("Valor a eliminar en Arbol A: ");
				scanf("%d", &valor);
				eliminarNodo(&arbolA, &valor);
				break;
 
			case 5:
				printf("Valor a eliminar en Arbol B: ");
				scanf("%d", &valor);
				eliminarNodo(&arbolB, &valor);
				break;
 
			case 6:
				profundidad(arbolA, arbolB);
				break;
 
			case 7:
				equilibrar(&arbolA);
				equilibrar(&arbolB);
				printf("Arboles equilibrados.\n");
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

