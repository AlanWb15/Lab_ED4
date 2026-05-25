#include "pila.h"

int comparar(void *x, void *y)
{
    int a = *(int *)x;
    int b = *(int *)y;
    if (a > b) return 1;
    if (a < b) return -1;
    return 0;
}

void imprimirEntero(void *dato)          // ← faltaba definirla
{
    printf("%d ", *(int *)dato);
}

void *check(Pila *p)
{
    if (pilaVacia(*p))
        return NULL;
    return p->cima->dato;
}

// ← comparar debe retornar int, no void
void ordenarPila(Pila *pila, int(*comparar)(void*, void*))
{
    Pila aux = {NULL, 0, -1, NULL, NULL};  // ← Pila por valor, no puntero
    void *actual;

    while (!pilaVacia(*pila))
    {
        actual = popDato(pila);

        // ← *aux → aux (ya es valor), comparar retorna int no void
        while (!pilaVacia(aux) && comparar(check(&aux), actual) > 0)
        {
            pushDato(pila, popDato(&aux));  // ← &aux correcto ahora
        }
        pushDato(&aux, actual);             // ← &aux
    }

    while (!pilaVacia(aux))
    {
        pushDato(pila, popDato(&aux));      // ← &aux
    }
}

int main()
{
    int val[7] = {9, 3, 2, 10, 6, 5, 8};
    Pila pila = {NULL, 0, 7, &imprimirEntero, NULL};

    for (int i = 0; i < 7; i++)           // ← declarar i aquí, evita warning
    {
        pushDato(&pila, &val[i]);
    }

    printf("pila OG\n");
    imprimirPila(pila);
    ordenarPila(&pila, comparar);          // ← pasar comparar, no imprimirEntero
    printf("pila ordenada\n");
    imprimirPila(pila);
    return 0;
}
