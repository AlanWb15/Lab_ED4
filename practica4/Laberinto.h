#ifndef LABERINTO_H
#define LABERINTO_H

#include <stdio.h>
#include <stdlib.h>
#include <pila.h>

#define REN 27
#define COL 26

typedef unsigned char **Laberinto;

typedef struct
{
	int fila, columna;
} Coordenada;

typedef struct
{
	int arriba, abajo, izquierda, derecha;
} Movimientos;

// FUNCIONES DEL LABERINTO
Laberinto crear_laberinto(void);
void liberarLaberinto(Laberinto lab);
void imprimirLab(Laberinto lab);
void setOrigen(Laberinto lab, Coordenada origen);
void setDestino(Laberinto lab, Coordenada destino);

// FUNCIONES DE RESOLUCION
Pila resolverLaberinto(Laberinto lab, Coordenada inicio);
void marcarCamino(Laberinto lab, Pila pila);

// FUNCIONES DE COORDENADAS
Coordenada* crearCoordenada(int fila, int columna);
int compararCoordenada(void *a, void *b);
void imprimirCoordenada(void *dato);

// FUNCIONES DE MOVIMIENTOS
Movimientos movimientosPosibles(Laberinto lab, Coordenada punto);
int bloqueado(Movimientos mov);
void imprimirMovimientos(Movimientos movimientos);

#endif
