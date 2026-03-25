#include <stdio.h>
#include "Alumno.h"
#include <listadoble.h>
#include <iostring.h>
#include <stdbool.h>

//prototipos de funciones
int dispMenu();
int dispMenuOrdenamiento();
int dispMenuBusquedaPorMiembro();
int dispMenuImprimir();

int main()
{
	ListaD lista = {NULL,NULL,0,imprimirAlumno,compararMatricula,free};
	Alumno *aux = NULL;
	int (*auxComp)(void*,void*);
	int auxEntero;
	char auxNombre[LEN];
	float auxFloat;
	unsigned int auxSinSigno;
	NodoD *auxNodoD = NULL;
	while(true){
		switch(dispMenu()){
			case 1:
				
				auxComp = lista.comparar;
				lista.comparar = compararMatricula;
				aux = crearAlumno();
				if(buscarDatoD(lista,&aux->matricula)){
					printf("\nNo puedes aniadir dos alumnos con misma matricula");
					free(aux);
					lista.comparar = auxComp;
				}
				else{
					lista.comparar = auxComp;
					insertEnOrdenD(&lista,aux);
				}

			break;

			case 2:
				
				if(!lista.inicio){
					printf("\nESTA VACIA NO PUEDES IMPIMIR NADA");
					break;
				}

				switch(dispMenuImprimir()){
					case 1:
						imprimirListaDIF(lista);
					break;

					case 2:
						imprimirListaDFI(lista);
					break;

					default:
						printf("\nOPCION INCORRECTA, NO SE IMPRIMIO NADA");
					break;
				}
			break;
			case 3:
				if(!lista.inicio){
					printf("\nESTA VACIA NO PUEDES REORDENAR NADA");
					break;
				}

				switch(dispMenuOrdenamiento()){
					case 1:
						reordenarD(&lista,compararMatricula);
					break;

					case 2:
						reordenarD(&lista,compararNombre);
					break;

					case 3:
						reordenarD(&lista,compararSemestre);
					break;

					case 4:
						reordenarD(&lista,compararPromedio);
					break;

					default:
						printf("\nOPCION INCORRECTA, NO SE CAMBIO NADA");
					break;
				}
				
			break;
 
			case 4:
				if(!lista.inicio){
					printf("\nESTA VACIA NO PUEDES BUSCAR NADA");
					break;
				}
				auxComp = lista.comparar;

				switch(dispMenuBusquedaPorMiembro()){
					case 1:
						lista.comparar = compararMatricula;
						do{
						}while(!inputEnteroSinSigno("\nIngrese matricula del alumno a buscar: ",&auxSinSigno));
						auxNodoD = buscarDatoD(lista,&auxSinSigno);
					break;

					case 2:
						lista.comparar = compararNombreInput;
						//pedida de nombre
						do{
						}while(!inputCadena("\nIngrese nombre del alumno a buscar: ",auxNombre,LEN));
						auxNodoD = buscarDatoD(lista,auxNombre);
					break;

					case 3:
						lista.comparar = compararSemestreInput;
						do{
						}while(!inputEntero("\nIngrese semestre del alumno a buscar: ",&auxEntero));
						auxNodoD = buscarDatoD(lista,&auxEntero);
					break;

					case 4:
						lista.comparar = compararPromedioInput;
						do{
						}while(!inputFloat("\nIngrese promedio del alumno a buscar: ",&auxFloat));
						auxNodoD = buscarDatoD(lista,&auxFloat);
					break;

					default:
						printf("\nOPCION INCORRECTA, REGRESANDO A MENU");
					break;
				}
				if(auxNodoD && auxNodoD->dato){
					imprimirAlumno(auxNodoD->dato);
				}
				else{
					printf("\nLos datos enviados no pertenecen a ningun alumno");
				}
				lista.comparar = auxComp;
			break;

			case 5:
				if(!lista.inicio){
					printf("\nESTA VACIA NO PUEDES ELIMINAR NADA");
					break;
				}

				auxComp = lista.comparar;
				lista.comparar = compararMatricula;
				
				do{
				}while(!inputEnteroSinSigno("\nIngrese matricula del alumno a eliminar: ",&auxSinSigno));
				borrarDatoD(&lista,&auxSinSigno);
				
				lista.comparar = auxComp;
			break;

			case 6:
				printf("\nSaliendo del programa");
				return 0;
			break;

			default:
				printf("\nOPERACION INCORRECTA");
			break;
		}
	}

	return 0;
}

int dispMenu(){
	int numRetornar;
	do{
		printf("\n---MENU---");
		printf("\n[1] para registrar Alumno");
		printf("\n[2] para desplegar alumnos");
		printf("\n[3] para Reordenar");
		printf("\n[4] para buscar alumno");
		printf("\n[5] para borrar alumno");
		printf("\n[6] para salir del programa");
	}while(!inputEntero("\nIngrese su seleccion: ",&numRetornar));
	return numRetornar;
}

int dispMenuOrdenamiento(){
	int numRetornar;
	do{
		printf("\n---MENU DE ORDENADO DE LISTA---");
		printf("\n[1] para ordenar por matricula");
		printf("\n[2] para ordenar por nombre");
		printf("\n[3] para ordenar por semestre");
		printf("\n[4] para ordenar por promedio");
	}while(!inputEntero("\nIngrese su seleccion: ",&numRetornar));
	return numRetornar;
}

int dispMenuBusquedaPorMiembro(){
	int numRetornar;
	do{
		printf("\n---MENU DE BUSQUEDA POR MIEMBRO	---");
		printf("\n[1] para buscar por matricula");
		printf("\n[2] para buscar por nombre");
		printf("\n[3] para buscar por semestre");
		printf("\n[4] para buscar por promedio");
	}while(!inputEntero("\nIngrese su seleccion: ",&numRetornar));
	return numRetornar;
}



int dispMenuImprimir(){
	int numRetornar;
	do{
		printf("\n---MENU DE IMPRESION DE LISTA---");
		printf("\n[1] para imprimir ascendente");
		printf("\n[2] para imprimir descendente");
	}while(!inputEntero("\nIngrese su seleccion: ",&numRetornar));
	return numRetornar;
}