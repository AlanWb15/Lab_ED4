#include <stdio.h>
#include <iostring.h>
#include <lista.h>
#include <listadoble.h>
#include "Alumno.h"

int main()
{
	Alumno *a,*b,*c;
	printf("\n HOLA MUNDO");
	a = crearAlumno();
	b = crearAlumno();
	c = crearAlumno();
	
	ListaD lista = {NULL,NULL,0,imprimirAlumno,compararNombre,free};
	insertarFinalD(&lista,a);
	insertarFinalD(&lista,b);
	insertarFinalD(&lista,c);
	imprimirListaDIF(lista);
	imprimirListaDFI(lista);
	borrarInicioD(&lista);
	imprimirListaDFI(lista);
	borrarListaD(&lista);
	imprimirListaDFI(lista);
	

	return 0;
}

