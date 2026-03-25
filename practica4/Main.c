#include <stdio.h>
#include <stdlib.h>
#include <pila.h>
#include "Laberinto.h"

int main(void)
{
    Laberinto lab = crear_laberinto();

    Coordenada origen  = {1,  1};
    Coordenada destino = {25, 24};

    setOrigen(lab, origen);
    setDestino(lab, destino);
    imprimirLab(lab);

    Pila camino = resolverLaberinto(lab, origen);

    marcarCamino(lab, camino);
    imprimirLab(lab);

    liberarLaberinto(lab);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}
