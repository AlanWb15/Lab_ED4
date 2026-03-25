#include "Laberinto.h"

Laberinto crear_laberinto(void)
{
    int i, j;
    char *tmp =
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
x*x*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x**************x\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

    Laberinto lab;
    lab = (unsigned char **) malloc(sizeof(unsigned char *) * REN);

    for (i = 0; i < REN; i++)
        lab[i] = (unsigned char *) malloc(sizeof(unsigned char) * COL);

    for (i = 0; i < REN; i++)
        for (j = 0; j < COL; j++)
            lab[i][j] = tmp[(i * COL) + j];

    return lab;
}

void liberarLaberinto(Laberinto lab)
{
    for (int i = 0; i < REN; i++)
        free(lab[i]);
    free(lab);
}

void imprimirLab(Laberinto lab)
{
    int i, j;
    for (i = 0; i < REN; i++)
    {
        printf("\n\r");
        for (j = 0; j < COL; j++)
        {
            if (lab[i][j] == '*') printf("  ");
            else printf("%c ", lab[i][j]);
        }
    }
}

static void reemplazarCaracter(Laberinto lab, Coordenada punto, char caracter)
{
    for (int i = 0; i < REN; i++)
        for (int j = 0; j < COL; j++)
        {
            if (lab[i][j] == caracter)
                lab[i][j] = '*';
            if (i == punto.fila && j == punto.columna)
                lab[i][j] = caracter;
        }
}

void setOrigen(Laberinto lab, Coordenada origen)
{
    reemplazarCaracter(lab, origen, 'A');
}

void setDestino(Laberinto lab, Coordenada destino)
{
    reemplazarCaracter(lab, destino, 'B');
}

// ---- RESOLUCION ----

void marcarCamino(Laberinto lab, Pila pila)
{
    while (!pilaVacia(pila))
    {
        Coordenada *dato = popDato(&pila);
        lab[dato->fila][dato->columna] = 'O';
        free(dato);
    }
}

Pila resolverLaberinto(Laberinto lab, Coordenada inicio)
{
    Pila pila = {NULL, 0, -1, imprimirCoordenada, free};
    Coordenada actual = inicio;
    Movimientos mov = movimientosPosibles(lab, actual);

    while (lab[actual.fila][actual.columna] != 'B')
    {
        if (mov.arriba == 1)
        {
            if (lab[actual.fila][actual.columna] != 'A')
                lab[actual.fila][actual.columna] = '.';
            actual = (Coordenada){actual.fila - 1, actual.columna};
            if (lab[actual.fila][actual.columna] == 'B') break;
            mov = movimientosPosibles(lab, actual);
            Coordenada *dato = crearCoordenada(actual.fila, actual.columna);
            pushDato(&pila, dato);
        }
        else if (mov.abajo == 1)
        {
            if (lab[actual.fila][actual.columna] != 'A')
                lab[actual.fila][actual.columna] = '.';
            actual = (Coordenada){actual.fila + 1, actual.columna};
            if (lab[actual.fila][actual.columna] == 'B') break;
            mov = movimientosPosibles(lab, actual);
            Coordenada *dato = crearCoordenada(actual.fila, actual.columna);
            pushDato(&pila, dato);
        }
        else if (mov.derecha == 1)
        {
            if (lab[actual.fila][actual.columna] != 'A')
                lab[actual.fila][actual.columna] = '.';
            actual = (Coordenada){actual.fila, actual.columna + 1};
            if (lab[actual.fila][actual.columna] == 'B') break;
            mov = movimientosPosibles(lab, actual);
            Coordenada *dato = crearCoordenada(actual.fila, actual.columna);
            pushDato(&pila, dato);
        }
        else if (mov.izquierda == 1)
        {
            if (lab[actual.fila][actual.columna] != 'A')
                lab[actual.fila][actual.columna] = '.';
            actual = (Coordenada){actual.fila, actual.columna - 1};
            if (lab[actual.fila][actual.columna] == 'B') break;
            mov = movimientosPosibles(lab, actual);
            Coordenada *dato = crearCoordenada(actual.fila, actual.columna);
            pushDato(&pila, dato);
        }
        else
        {
            // Retroceder (backtracking)
            while (bloqueado(mov))
            {
                lab[actual.fila][actual.columna] = '.';
                Coordenada *dato = popDato(&pila);
                actual = *dato;
                free(dato);
                mov = movimientosPosibles(lab, actual);
            }
            lab[actual.fila][actual.columna] = '.';
        }

        Coordenada *dato = crearCoordenada(actual.fila, actual.columna);
        pushDato(&pila, dato);
    }

    return pila;
}
