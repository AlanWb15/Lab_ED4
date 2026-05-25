#include "heap.h"



Heap crearHeap(unsigned char tipo,fn_comparar comparar,fn_imprimir imprimir)
{
	Heap heap = {tipo,0,NULL,NULL,comparar,imprimir};
	return heap;
}
void imprimirHeap(Heap heap)
{
	printf("\n HEAP: \n");
	if(heap.cantidad)
	{
		for( int i = 0; i < heap.cantidad; i++)
		{
			printf(" [%d] ",i);
			heap.imprimir( heap.datos[i] );
			printf("\n");
		}

	}
	else
		printf("VACIO");
}

void insertarHeap( Heap *heap,void *dato)
{
	void **aux = NULL;
	if(!heap->cantidad)
		heap->datos = calloc(1,sizeof(void*));
	else
	{
		while(!aux)
			aux = realloc(heap->datos, (heap->cantidad+1) * sizeof(void*) );
		heap->datos = aux;
	}
	heap->datos[heap->cantidad++] = dato;
	//HEAPIFY
	heapify(heap);
}


void* eliminarHeap(Heap *heap)
{
	void *dato = NULL;
	if(!heap->cantidad)
		return dato;
	dato = heap->datos[0];
	if(heap->cantidad == 1)
	{
		free(heap->datos);
		heap->datos = NULL;
		heap->cantidad--;
		return dato;
	}
	heap->datos[0] = heap->datos[heap->cantidad-1];
	void **aux = NULL;
	while(!aux)
		aux = realloc(heap->datos, (heap->cantidad-1) * sizeof(void*) );
	heap->datos = aux;
	heap->cantidad--;
	//HEAPIFY
	heapify(heap);
	return dato;
}





void imprimir_heap(Heap heap, int idx, int nivel, fn_imprimir imprimir)
{
    if (idx >= heap.cantidad || !heap.datos) return;

    int hijo_der = 2 * idx + 2;
    int hijo_izq = 2 * idx + 1;


    imprimir_heap(heap, hijo_der, nivel + 1, imprimir);

    // Imprimir nodo actual con sangría según nivel
    for (int i = 0; i < nivel; i++)
        printf("        ");
    printf("[");
    imprimir(heap.datos[idx]);
    printf("]\n");

    // Luego el subárbol izquierdo (aparece abajo)
    imprimir_heap(heap, hijo_izq, nivel + 1, imprimir);
}

void imprimirHeapA(Heap heap)
{
    if (!heap.datos || heap.cantidad == 0)
    {
        printf("\nHEAP VACÍO\n");
        return;
    }
    printf("\n--- ÁRBOL ---\n");
    imprimir_heap(heap, 0, 0, heap.imprimir);
    printf("\n");
}




void heapify_min( Heap *heap,int padre)
{
	if( padre < 0 || padre > (heap->cantidad/2-1) )
		return;
	int min = padre; //17
	int izq = 2*padre+1;  //24
	int dch = 2*padre+2;  //29
	switch(heap->tipo)
	{
		case HEAP_MIN:
			if( heap->comparar( heap->datos[min] , heap->datos[izq] ) > 0 )
				min = izq;
			if( dch < heap->cantidad && heap->comparar( heap->datos[min] , heap->datos[dch] ) > 0 )
				min = dch;
			break;
		case HEAP_MAX:
			if( heap->comparar( heap->datos[izq]/*24*/ , heap->datos[min] /*17*/) > 0 )
				min = izq; /*24*/
			if( dch < heap->cantidad && heap->comparar( heap->datos[dch] , heap->datos[min] ) > 0 )
				min = dch;
			break;
	}
	if( min!=padre)
	{
		void *dato = heap->datos[padre]; /*17*/
		heap->datos[padre] = heap->datos[min];/*24*/
		heap->datos[min] = dato;
		heapify_min(heap,min);
	}
	heapify_min(heap,padre-1);


}


void heapify(Heap *heap)
{
	int indice = heap->cantidad/2-1;
	heapify_min(heap,indice);

}
