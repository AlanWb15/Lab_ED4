
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <stdarg.h>
#include <time.h>
#include "iostring.h"
#include <ctype.h>
#include "pila.h"
#include "arbol.h"

typedef struct {
    char nombre;
    float valor;
} Variable;



int verificarParentesis(char *cadena);
char* crearChar(char dato);
char obtenerChar(void *dato);
void imprimirChar(void*);
void infixToPostfix(char infix[], char postfix[], Pila *pila);
int prioridad(char op);
int esOperador(char c);
int esOperando(char c);
NodoA* crearArbol(char postfix[], Pila *pila, Arbol arbol);
int yaExiste(char nombre, Variable vars[], int numVars);
void capturarVariables(char postfix[], Variable vars[], int *numVars);
float evaluarArbol(NodoA *nodo, Variable vars[], int numVars);


int main()
{
    Variable vars[52];
    int numVars = 0;
    Pila pila = {NULL,0,100,NULL,free};
    Arbol arbol;
    arbol.raiz = NULL;
    arbol.cantidad = 0;
    arbol.imprimir = &imprimirChar;
    arbol.comparar = NULL;
    arbol.liberar = &free;

    char infix[100];
    char postfix[100];
    int opc;
    NodoA *raiz = NULL;

    do {
        printf("\nMenu\n");
        printf("0. capturrar\n");
        printf("1. imprimir\n");
        printf("2. evaular\n");
        printf("3. exit\n");
        printf("Ingrese opcion: ");
        scanf("%d", &opc);

        switch(opc)
        {
            case 0:
                printf("Ingresa expresion infix: ");
                scanf("%s", infix);

                if(!verificarParentesis(infix))
                {
                    printf("Error: parentesis incorrectos\n");
                }
                else
                {

                    infixToPostfix(infix, postfix, &pila);
                    printf("Postfix: %s\n", postfix);
                    raiz = crearArbol(postfix, &pila, arbol);
                    memset(vars, 0, sizeof vars);
                }
                break;
            case 1:
                arbol.raiz = raiz;
                imprimirArbol(arbol);
                break;

            case 2:
            capturarVariables(postfix, vars, &numVars);
            printf("%f",evaluarArbol(raiz, vars, numVars));
                break;
            case 3:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion invalida\n");
        }

    } while(opc != 3);

    eliminarPila(&pila);

    return 0;
}


char* crearChar(char dato)
{
    char *nuevo = (char*) malloc(sizeof(char));
	*nuevo = dato;
	return nuevo;
}

char obtenerChar(void *dato)
{
    return *(char*)dato;
}

void imprimirChar(void *a)
{
    char *aa=a;
    printf("%c",*aa);
}


float* crearFloat(float dato)
{
    float *nuevo = (float*) malloc(sizeof(float));
    *nuevo = dato;
    return nuevo;
}

float obtenerFloat(void *dato)
{
    return *(float*)dato;
}


int verificarParentesis(char *cadena)
{
    Pila pila = {NULL,0,100,NULL,NULL};
    char *ptr = cadena;

    while(*ptr != '\0')
    {
        if(*ptr == '(')
        {
            pushDato(&pila, crearChar('('));
        }
        else if(*ptr == ')')
        {
            if(pila.cima == NULL)
            {
                vaciarPila(&pila);
                return 0;
            }

            char *dato = (char*)popDato(&pila);
            free(dato);
        }

        ptr++;
    }

    int valido = (pila.cima == NULL);
    vaciarPila(&pila);

    return valido;
}

void infixToPostfix(char infix[], char postfix[], Pila *pila)
{
    vaciarPila(pila);
    int j = 0;

    for(int i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];

        if(esOperando(c))
        {
            postfix[j++] = c;
        }

        else if(c == '(')
        {
            pushDato(pila, crearChar(c));
        }

        else if(c == ')')
        {
            while(!pilaVacia(*pila) && obtenerChar(pila->cima->dato) != '(')
            {
                postfix[j++] = obtenerChar(popDato(pila));
            }
            popDato(pila); // quitar '('
        }

        else if(esOperador(c))
        {
            while(!pilaVacia(*pila) &&
                  prioridad(obtenerChar(pila->cima->dato)) >= prioridad(c))
            {
                postfix[j++] = obtenerChar(popDato(pila));
            }

            pushDato(pila, crearChar(c));
        }
    }

    while(!pilaVacia(*pila))
    {
        postfix[j++] = obtenerChar(popDato(pila));
    }

    postfix[j] = '\0';
}

/*
void crearArbol(char postfix[], Pila pila, Arbol arbol)
{
    vaciarPila(&pila);

    for(int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        if(esOperando(c))
        {
            pushDato(&pila,crearChar(c));
        }

        else
        {
            insertarArbol(&arbol, crearChar(c));
            c = *(char*)pila.cima->dato;
            popDato(&pila);
            arbol.raiz->dch=crearNodoA(crearChar(c));
            c = *(char*)pila.cima->dato;
            popDato(&pila);
            arbol.raiz->izq=crearNodoA(crearChar(c));
            pushDato(&pila, arbol.raiz);
        }
    }

}
*/

int prioridad(char op)
{
    switch(op)
    {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
    }
    return 0;
}

int esOperador(char c)
{
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='^';
}

int esOperando(char c)
{
    return isalnum(c);
}


NodoA *crearArbol(char postfix[], Pila *pila, Arbol arbol)
{
    int i = 0;
    char temp = postfix[i];


    while (postfix[i])
    {
        temp = postfix[i];
       if(esOperador(temp))
       {

            NodoA *nodo = crearNodoA(crearChar(temp));
            NodoA *derecho = popDato(pila);
            NodoA *izquierdo = popDato(pila);
            nodo->dch = derecho;
            nodo->izq = izquierdo;
            pushDato(pila, nodo);
       }
       else
       {
        pushDato(pila, crearNodoA(crearChar(temp)));
       }
       i++;
    }
    return popDato(pila);
}

void capturarVariables(char postfix[], Variable vars[], int *numVars)
{
    int i = 0;
    char temp = postfix[i];
    float valor =0;

    while (postfix[i])
    {
        temp = postfix[i];

        if(isalpha(temp) && yaExiste(temp, vars, *numVars) ==0)
        {
            vars[*numVars].nombre = temp;
            printf("Ingresa valor de %c: ", temp);
            scanf("%f", &valor);
            vars[*numVars].valor = valor;
            (*numVars)++;
        }


        i++;
    }
}

int yaExiste(char nombre, Variable vars[], int numVars)
{
    char temp = nombre;
    for(int i = 0; i < numVars; i++)
        if(vars[i].nombre ==temp)
            return 1;
    return 0;
}

float evaluarArbol(NodoA *nodo, Variable vars[], int numVars)
{
    if(!esOperador(obtenerChar(nodo->dato)))
    {
        char var = obtenerChar(nodo->dato);
        for(int i = 0; i < numVars; i++)
            if(vars[i].nombre == var)
                return vars[i].valor;
    }
    else
    {
        float izq = evaluarArbol(nodo->izq, vars, numVars);
        float der = evaluarArbol(nodo->dch, vars, numVars);

        switch(obtenerChar(nodo->dato))
        {
        case '^': return pow(izq, der);
        case '*': return izq * der;
        case '/': return izq / der;
        case '+': return izq + der;
        case '-': return izq - der;
        }

    }
    return 0;
}
