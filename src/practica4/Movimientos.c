#include "Laberinto.h"


Movimientos movimientosPosibles(Laberinto lab,Coordenada punto)
{
	Movimientos movimientos = {0,0,0,0};
	//ARRIBA
	if( lab[punto.x-1][punto.y] == '*' || lab[punto.x-1][punto.y] == 'B')
		movimientos.up = 1;
	//ABAJO
	if( lab[punto.x+1][punto.y] == '*' || lab[punto.x+1][punto.y] == 'B')
		movimientos.down = 1;
	//DERECHA
	if( lab[punto.x][punto.y+1] == '*' || lab[punto.x][punto.y+1] == 'B')
		movimientos.right = 1;
	//IZQUIERDA
    if( lab[punto.x][punto.y-1] == '*' || lab[punto.x][punto.y-1] == 'B')
		movimientos.left = 1;
	return movimientos;	
}

Movimientos regresosPosibles(Laberinto lab,Coordenada punto)
{
	Movimientos movimientos = {0,0,0,0};
	//ARRIBA
	if( lab[punto.x-1][punto.y] == '.')
		movimientos.up = 1;
	//ABAJO
	if( lab[punto.x+1][punto.y] == '.')
		movimientos.down = 1;
	//DERECHA
	if( lab[punto.x][punto.y+1] == '.')
		movimientos.right = 1;
	//IZQUIERDA
    if( lab[punto.x][punto.y-1] == '.')
		movimientos.left = 1;
	return movimientos;	
}

void moverseEnLaberinto(Laberinto lab, Pila *movimientos)
{
	Coordenada *punto = movimientos->cima->dato;
	Movimientos posibles = movimientosPosibles(lab, *punto);
	
	//MOVERSE ARRIBA
	if(posibles.up == 1)
	{
		//imprimirMovimientos(posibles);
		
		lab[punto->x][punto->y] = '.';
		pushDato(movimientos, crearCoordenada(punto->x - 1,punto->y));
	}
	//MOVERSE ABAJO
	else if(posibles.down == 1)
	{
		//imprimirMovimientos(posibles);
		
		lab[punto->x][punto->y] = '.';
		pushDato(movimientos, crearCoordenada(punto->x + 1,punto->y));
	}
	//MOVERSE A LA DERECHA
	else if(posibles.right == 1)
	{
		//imprimirMovimientos(posibles);
		
		lab[punto->x][punto->y] = '.';
		pushDato(movimientos, crearCoordenada(punto->x,punto->y+1));
	}
	//MOVERSE A LA IZQUIERDA
	else if(posibles.left == 1)
	{
		//imprimirMovimientos(posibles);
		
		lab[punto->x][punto->y] = '.';
		pushDato(movimientos, crearCoordenada(punto->x,punto->y-1));
	}
	
}

void atras(Laberinto lab,Pila *movimientos)
{
	Coordenada *anterior = movimientos->cima->dato;
	Movimientos posibles = regresosPosibles(lab, *anterior);
	
	//MOVERSE ARRIBA
	if(posibles.up == 1)
	{
		//imprimirMovimientos(posibles);
		
		lab[anterior->x][anterior->y] = ',';
		free(popDato(movimientos));
		
	}
	//MOVERSE ABAJO
	else if(posibles.down == 1)
	{
		//imprimirMovimientos(posibles);
		
		lab[anterior->x][anterior->y] = ',';
		free(popDato(movimientos));
	}
	//MOVERSE A LA DERECHA
	else if(posibles.right == 1)
	{
		//imprimirMovimientos(posibles);
		
		lab[anterior->x][anterior->y] = ',';
		free(popDato(movimientos));
	}
	//MOVERSE A LA IZQUIERDA
	else if(posibles.left == 1)
	{
		//imprimirMovimientos(posibles);
		
		lab[anterior->x][anterior->y] = ',';
		free(popDato(movimientos));
	}
}

void imprimirMovimientos(Movimientos movimientos)
{	
	printf("\n");
	//ARRIBA
	if( movimientos.up == 1)
		printf(" ARRIBA");
	//ABAJO
	else if( movimientos.down == 1)
		printf(" ABAJO");
	//DERECHA
	else if( movimientos.right == 1)
		printf(" DERECHA");
	//IZQUIERDA
	else if( movimientos.left == 1)
		printf(" IZQUIERDA");
	
}

int compararMovimientos(Movimientos a, Movimientos b)
{
	if(a.up == b.up &&
	   a.down == b.down &&
	   a.right == b.right &&
	   a.left == b.left)
	   {
		   return 1;
	   }		   
	   
	   return 0;
}

