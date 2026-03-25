#include "Laberinto.h"

Movimientos movimientosPosibles(Laberinto lab, Coordenada punto)
{
    Movimientos movimientos = {0, 0, 0, 0};

    if (lab[punto.fila - 1][punto.columna] == '*')
        movimientos.arriba = 1;

    if (lab[punto.fila + 1][punto.columna] == '*')
        movimientos.abajo = 1;

    if (lab[punto.fila][punto.columna + 1] == '*')
        movimientos.derecha = 1;

    if (lab[punto.fila][punto.columna - 1] == '*')
        movimientos.izquierda = 1;

    return movimientos;
}

void imprimirMovimientos(Movimientos movimientos)
{
    printf("\nMovimientos posibles:");
    if (movimientos.arriba)   printf(" ARRIBA");
    if (movimientos.abajo)    printf(" ABAJO");
    if (movimientos.derecha)  printf(" DERECHA");
    if (movimientos.izquierda) printf(" IZQUIERDA");
    printf("\n");
}

int bloqueado(Movimientos mov)
{
    return mov.arriba == 0 && mov.abajo == 0 && mov.izquierda == 0 && mov.derecha == 0;
}
