#include "arbol.h"


void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(!raiz->izq)			
			raiz->izq = crearNodoA(dato);
		else if(!raiz->dch && comparar(dato,raiz->dato)==0)			
			raiz->dch = crearNodoA(dato);
		else			
			insertarArbolOrdenado(raiz->izq,dato,comparar);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}



void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else 
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}



void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}


void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}


void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq,liberar);
	eliminar_NodosA(raiz->dch,liberar);
	//LIBERAR
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
}


void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

void invertirRamas(NodoA *raiz)
{
	if(!raiz)
		return;
	NodoA *aux = raiz->izq;
	raiz->izq = raiz-> dch;
	raiz->dch = aux;
	invertirRamas(raiz->izq);
	invertirRamas(raiz->dch);
}
 
void invertir(Arbol *arbol)
{
	invertirRamas(arbol->raiz);	
}


Resultado buscarEnArbol(Arbol arbol, void *dato)
{
	Resultado result= {NULL, NULL, NULL, DERECHA};;
	NodoA *raiz = arbol.raiz;
	
	while(raiz)
	{

		if(arbol.comparar(raiz->dato, dato) == 0)
		{
			result.nodo = raiz;
			result.dato = result.nodo->dato;
			if(result.padre && result.padre -> izq==raiz)
				result.rama = IZQUIERDA;
			else if(result.padre&&result.padre->dch==raiz)
					result.rama=DERECHA;

			break;
		}
		
		else
		{
			result.padre=raiz;
			 
			if(arbol.comparar(raiz->dato, dato)>0)
			{
				raiz = raiz->izq;
				
			}
			else
			raiz = raiz->dch;
	}
}

	return result;
}
//hacer imprimirEntero
void imprimirEntero(void *dato)
{
	int data = *(int *)dato;
	printf("%d", data);

}

void imprimirResultado(Resultado resultado, Arbol *arbol)
{
	if(resultado.nodo)
	{
		if(resultado.padre)
		{
			printf("\nPadre");
			imprimirEntero(resultado.padre->dato);
		}
		printf("\n Nodo");
		imprimirEntero(resultado.nodo->dato);
		printf("\n RAMA %s", 
				(resultado.rama) ? "DERECHA": "IZQUIERDA");
		}
	

}


void eliminarNodo(Arbol *arbol, void *dato)
{
	Resultado res = buscarEnArbol(*arbol, dato);

	if (res.nodo == NULL)
	{
		printf("No se encontro nada de nada");
		return;	
	}

	NodoA *nodo = res.nodo;
	NodoA *padre = res.padre;
	
	//crear checks para ver si tienen hijos
	int checkIzq = (nodo->izq != NULL);
	int checkDch = (nodo->dch != NULL);
	
	//cuando no tiene hijos
	if(!checkIzq && !checkDch)
	{
		if(padre==NULL)
		{
			arbol->raiz=NULL;
		}
		else if(res.rama==IZQUIERDA)
			{
				padre->izq=NULL;
			}
			else
			{
				padre->dch=NULL;
			}
		arbol->liberar(nodo->dato);
    	free(nodo);
 	    arbol->cantidad--;
	}

	
	//cuando tiene 1 hijo
	else if(checkIzq||checkDch)
		{
			NodoA *hijo = checkIzq ? nodo -> izq : nodo ->dch;
			
			if(padre == NULL)
				arbol->raiz = hijo;

			else if(res.rama == IZQUIERDA)
					padre->izq = hijo;
				
				else
					padre->dch = hijo;

			arbol->liberar(nodo->dato);
			free(nodo);
			arbol->cantidad--;
		}
	//cuando tiene 2 o mas hijos;
	else 
		{
			NodoA *sucesor = nodo->dch;
			NodoA *padreSucesor = nodo;
			
			while(sucesor->izq!=NULL)
			{
					padreSucesor = sucesor;
					sucesor = sucesor->izq;
			}
			nodo->dato = sucesor->dato;
			
			if(padreSucesor==nodo)
				padreSucesor->dch = sucesor->dch;
			else 
				padreSucesor->izq = sucesor->dch;

			free(sucesor);
			arbol->cantidad--;
					
		}
}			

int altura(NodoA *nodo)
{
	//recorrer arbol desde raiz
	if(!nodo)
		return -1; //su profundidad es 0

	int izq = altura(nodo->izq);
	int dch = altura(nodo->dch);
	
	return (1 + (izq>dch ? izq : dch));
}
//profundidad, recursividad
void profundidad(Arbol arbolA, Arbol arbolB)
{
    //aqui se tiene que iniciar la recursividad
	printf("Profundidad de Arbol A: %d", altura(arbolA.raiz));
	printf("Profundidad de Arbol B: %d", altura(arbolB.raiz));

}

//comparar arboles

int compararNodos(NodoA *a, NodoA *b, int (*comparar)(void*, void*))
{
	//tope de recursion
	if(!a && !b) //los dos toparon igual
		return 1;
	if(!a || !b) //toparon diferente
		return 0;

	return (comparar( a->dato, b->dato) == 0 
			&& compararNodos(a->izq, b->izq, comparar)
			&& compararNodos(a->dch, b->dch, comparar));

}

int compararEstructura(NodoA *a, NodoA *b)
{
	//tope de recursion
	if(!a && !b) //los dos toparon igual
        return 1;
    if(!a || !b) //toparon diferente
        return 0;

	return(compararEstructura(a->izq, b->izq) && compararEstructura(a->dch, b->dch));
}

void compararArboles(Arbol arbolA, Arbol arbolB)
{
	
	int checkDatos = compararNodos(arbolA.raiz, arbolB.raiz, arbolA.comparar);
	int checkEstr = compararEstructura(arbolA.raiz, arbolB.raiz);
	
	if(checkDatos && checkEstr)
		printf("los dos son iguales\n");
	else if(checkDatos)
			printf("Mismos datos, diferente Estructura\n");
		else
			printf("No comparte ninguna similitud\n");

}
 
void ordenArr(NodoA *raiz, void **arreglo, int *indice)
{
	if(!raiz)
		return;
	
	ordenArr(raiz->izq, arreglo, indice);
	arreglo[*indice] = raiz->dato;

	printf("%d", *(int*)arreglo[*indice]);

	(*indice)++;

	ordenArr(raiz->dch, arreglo, indice);

}

void reordenar(Arbol *arbol, void **datos, int inicio, int fin)
{
	if(inicio>fin)
		return;
	int centro = (inicio + fin)/2;
	insertarArbol(arbol, datos[centro]);
	
	//parte izq
	reordenar(arbol, datos, inicio, centro -1);
	//parte dch
	reordenar(arbol, datos, centro +1, fin);
}


//equilibrar arbol
void equilibrar(Arbol *arbol)
{
	/*Paso 1: Guardar inorden en un arreglo
	Paso 2: Reconstruir desde el centro
	Paso 3: Reemplazar el árbol original*/
	void **datos = malloc(arbol->cantidad *sizeof(void*));
	int indice = 0;
	ordenArr(arbol->raiz, datos, &indice);
	
	//PASO2
	eliminar_NodosA(arbol->raiz, NULL);
	arbol->raiz=NULL;
	arbol->cantidad = 0;
	
	//PASO3
	reordenar(arbol, datos, 0, indice -1);
	
	free(datos);

	
}
