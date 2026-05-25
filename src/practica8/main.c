#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostring.h>
#include <heap.h>
#include <arbol.h>


#define HEAP_MIN 0
#define HEAP_MAX 1
#define LONGI 10

typedef struct Archivo{

    char nombre[LONGI];
    int paginas;


}Archivo;

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);
Archivo *generarDocumento();
void imprimirArchivo(void *a);
int compararArchivo(void *a, void *b);
int buscarEnHeap(Heap heap, void *dato);
void* eliminarNodoHeap(Heap *heap, int indice);

int main(void)
{
    srand(time(NULL));
    Heap heap = crearHeap(HEAP_MIN,compararArchivo,imprimirArchivo);

    int opc, opc2;
    char tempo[LONGI];
    Archivo res;


    do{
        printf("1. CAMBIAR PRIORIDADO\n");
        printf("2. MOSTRAR COLA DE IMPRESIÓN\n");
        printf("3. AGREGAR ARCHIVO\n");
        printf("4. PROCESAR/IMPRIMIR ARCHIVO\n");
        printf("5. ELIMINAR ARCHIVO\n");
        printf("6. ELIMINAR TODOS LOS ARCHIVOS\n");
        printf("0. TERMINAR PROGRAMA\n");
        printf("\nselecciona una opcion: ");
        scanf("%d", &opc);

        switch(opc)
        {
            case 1:


                printf("\n1. MAXIMO\n");
                printf("\n2. MINIMO\n");
                scanf("%d", &opc2);

                if(opc2==1)
                    heap.tipo = 1;
                else
                    heap.tipo = 0;

                if(!heap.datos)
                {
                    printf("ACCION INVALIDA\n");
                }else{
                    heapify(&heap);
                    imprimirHeapA(heap);
                }
                break;

            case 2:
                if(heap.datos == NULL)
                {
                    printf("No hay elementos en espera\n");
                    break;
                }else
                {
                    imprimirHeapA(heap);
                    break;
                }

            case 3:

                insertarHeap(&heap, generarDocumento());
                printf("\n");
                imprimirHeap(heap);
                break;

            case 4:
                imprimirHeap(heap);
                imprimirHeapA(heap);
                printf("procesando...");
                void *temp = heap.datos[0];
                heap.datos[0] = heap.datos[heap.cantidad - 1];
                heap.datos[heap.cantidad - 1] = temp;

                heap.cantidad--;
                free(heap.datos[heap.cantidad]);

                heapify(&heap);
                imprimirHeapA(heap);
                break;
            case 5:
                printf("\nInserte el nombre del archivo que se desee eliminar: ");
                printf("\n");
                scanf("%s", tempo);
                strcpy(res.nombre, tempo);
                int indice = buscarEnHeap(heap,  &res);
                if(indice != -1)
                {
                    Archivo *eliminado = eliminarNodoHeap(&heap, indice);
                    printf("Eliminado: %s (%d pags)\n", eliminado->nombre, eliminado->paginas);
                    free(eliminado);
                }
                else
                    printf("No encontrado\n");
                break;

            case 6:
                printf("eliminando...\n");
                int i;
                    for(i = 0; i < heap.cantidad; i++)
                    {
                        free(heap.datos[i]);
                    }
                    free(heap.datos);
                    heap.datos = NULL;
                    heap.cantidad = 0;
                break;




            default:
             break;
        }

    }while(opc!=0);

    printf("\nBYE\n");

    return 0;

}


Archivo* generarDocumento()
{

    Archivo *arch = calloc(1,sizeof(Archivo));
    char palabra[LONGI];
    int num;

    char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    int maxIndex = sizeof(caracteres) - 2;

    for (i = 0; i < LONGI; i++) {

        palabra[i] = caracteres[rand() % (maxIndex + 1)];
        num = rand() % 67;

    }
    palabra[LONGI - 1] = '\0';

   strcpy(arch->nombre, palabra);
   arch->paginas = num;

   printf("%d - - - - - %s", arch->paginas, arch->nombre);

   return arch;

}

int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

int compararArchivo(void *a, void *b)
{
    Archivo *aa = a, *bb = b;
    if(aa->paginas == bb->paginas) return 0;
    else if(aa->paginas < bb->paginas) return -1;
    else return 1;
}

void imprimirArchivo(void *a)
{
    Archivo *arch = a;
    printf("%s (%d pags)", arch->nombre, arch->paginas);
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}

int compararNombre(void *a, void *b)
{
    Archivo *aa = a, *bb = b;
    return strcmp(aa->nombre, bb->nombre);
}

int buscarEnHeap(Heap heap, void *dato)
{
    if(!heap.cantidad || !heap.datos)
        return -1;

    int i;
    for(i = 0; i < heap.cantidad; i++)
    {
        if(compararNombre(heap.datos[i], dato) == 0)
        {
            Archivo *arch = (Archivo*)heap.datos[i];
            printf("encontrado: %s\n", arch->nombre);
            return i;
        }
    }
    return -1;
}
void* eliminarNodoHeap(Heap *heap, int indice)
{
    if(indice < 0 || indice >= heap->cantidad)
        return NULL;

    void *dato = heap->datos[indice];


    heap->datos[indice] = heap->datos[heap->cantidad - 1];

    void **aux = NULL;
    while(!aux)
        aux = realloc(heap->datos, (heap->cantidad - 1) * sizeof(void*));
    heap->datos = aux;
    heap->cantidad--;

    heapify(heap);
    return dato;
}
