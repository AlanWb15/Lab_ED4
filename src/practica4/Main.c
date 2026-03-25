#include <stdio.h>
#include <stdlib.h>

#include "Laberinto.h"




int main(void)
{
    Laberinto labe = crear_laberinto();
	Coordenada origen = {1,1};
	Coordenada destino = {25,24};
	Pila movimientos = {NULL,0,-1,NULL,NULL};
	Movimientos nah = {0,0,0,0};
	setOrigen(labe,origen);
	setDestino(labe,destino);
	imprimirLab(labe);
	
	pushDato(&movimientos,&origen);
	Coordenada *cima = movimientos.cima->dato;
	
	while(!pilaVacia(movimientos) && !(compararCoordenada(cima,&destino)))
	{
		if(!compararMovimientos(movimientosPosibles(labe,*cima),nah))
		{
			moverseEnLaberinto(labe,&movimientos);
			imprimirLab(labe);
			printf("\n");
		}
		else
		{
			if(!compararMovimientos(regresosPosibles(labe,*cima),nah))
			{
				atras(labe,&movimientos);
				printf("\n");
			}
		}
		cima = movimientos.cima->dato;
	}
	
    imprimirLab(labe);
	liberarLaberinto(labe);
	printf("\n");
    printf("Fin bye");
    return 0;
}

