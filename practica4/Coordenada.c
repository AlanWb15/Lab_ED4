#include "Laberinto.h"

Coordenada* crearCoordenada(int fila, int columna)
{
    Coordenada *nueva = malloc(sizeof(Coordenada));
    nueva->fila = fila;
    nueva->columna = columna;
    return nueva;
}

void imprimirCoordenada(void *dato)
{
    Coordenada *c = dato;
    printf("[%-2d,%-2d]", c->fila, c->columna);
}

int compararCoordenada(void *a, void *b)
{
    Coordenada *ca = a, *cb = b;
    if (ca->fila == cb->fila && ca->columna == cb->columna)
        return 1;
    return 0;
}
