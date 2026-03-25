#include <stdio.h>
#include <stdlib.h>
#include "iostring.h"
#include "lista.h"
#include "Alumno.h"

void mostrarMenu(void)
{
    printf("\n   SISTEMA DE GESTION DE ALUMNOS");
   
    printf("\n 1. Registrar Alumno");
    printf("\n 2. Desplegar Alumnos");
    printf("\n 3. Reordenar Lista");
    printf("\n 4. Buscar Alumno");
    printf("\n 5. Borrar Alumno");
    printf("\n 6. Finalizar programa");
    
    printf("\n Seleccione una opcion: ");
}


int menuReordenar(void)
{
    int opcion;
    
    printf("\n   REORDENAR POR:");
    
    printf("\n 1. Matricula");
    printf("\n 2. Nombre");
    printf("\n 3. Semestre");
    printf("\n 4. Promedio");
    
    inputEntero("\n Seleccione criterio: ", &opcion);
    return opcion;
}


int menuBuscar(void)
{
    int opcion;
    
    printf("\n   BUSCAR POR:");
    
    printf("\n 1. Matricula");
    printf("\n 2. Nombre");
    printf("\n 3. Semestre");
    printf("\n 4. Promedio");
    
    inputEntero("\n Seleccione criterio: ", &opcion);
    return opcion;
}


int matriculaExiste(Lista lista, unsigned int matricula)
{
    Alumno temp;
    temp.matricula = matricula;
    
  
    int (*comparadorOriginal)(void*, void*) = lista.comparar;
    lista.comparar = compararMatricula;
    
    Resultado res = buscar(lista, &temp);
    

    lista.comparar = comparadorOriginal;
    
    return (res.enco != NULL);
}

// Función para registrar un alumno
void registrarAlumno(Lista *lista)
{
    Alumno *nuevo;
    unsigned int matricula;
    int valido = 0;
    
    
    printf("\n   REGISTRAR NUEVO ALUMNO");
    
    
    // Verificar que la matrícula sea única
    do {
        inputEnteroSinSigno("\n Matricula: ", &matricula);
        
        if (matriculaExiste(*lista, matricula)) {
            printf("\n *** ERROR: La matricula %u ya existe. Intente con otra. ***\n", matricula);
        } else {
            valido = 1;
        }
    } while (!valido);
    
    // Crear alumno con la matrícula validada
    nuevo = calloc(1, sizeof(Alumno));
    nuevo->matricula = matricula;
    inputCadena(" Nombre: ", nuevo->nombre, LEN);
    inputEntero(" Semestre: ", &nuevo->semestre);
    inputFloat(" Promedio: ", &nuevo->promedio);
    
    agregarEnOrden(lista, nuevo);
    printf("\n *** Alumno registrado exitosamente! ***\n");
}

// Función para desplegar todos los alumnos
void desplegarAlumnos(Lista lista)
{
    
    printf("\n   LISTA DE ALUMNOS");
    
    
    if (!lista.inicio) {
        printf("\n No hay alumnos registrados.\n");
        return;
    }
    
    printf("\n %-7s | %-40s | %-8s | %-8s", "MATRIC", "NOMBRE", "SEMESTRE", "PROMEDIO");
    printf("\n--------+-----------------------------------------+----------+----------");
    
    imprimirLista(lista);
}

void reordenarLista(Lista *lista)
{
    int opcion = menuReordenar();
    int (*comparador)(void*, void*) = NULL;
    
    switch(opcion) {
        case 1:
            comparador = compararMatricula;
            printf("\n Reordenando por Matricula...\n");
            break;
        case 2:
            comparador = compararNombre;
            printf("\n Reordenando por Nombre...\n");
            break;
        case 3:
            comparador = compararSemestre;
            printf("\n Reordenando por Semestre...\n");
            break;
        case 4:
            comparador = compararPromedio;
            printf("\n Reordenando por Promedio...\n");
            break;
        default:
            printf("\n *** Opcion invalida. ***\n");
            return;
    }
    
    reordenar(lista, comparador);
    printf("\n *** Lista reordenada exitosamente! ***\n");
}


void buscarAlumno(Lista *lista)
{
    int opcion = menuBuscar();
    Alumno temp;
    Resultado res;
    int (*comparadorOriginal)(void*, void*) = lista->comparar;
    
    
    printf("\n   BUSCAR ALUMNO");
    
    
    switch(opcion) {
        case 1:
            inputEnteroSinSigno("\n Ingrese matricula: ", &temp.matricula);
            lista->comparar = compararMatricula;
            break;
        case 2:
            inputCadena("\n Ingrese nombre: ", temp.nombre, LEN);
            lista->comparar = compararNombre;
            break;
        case 3:
            inputEntero("\n Ingrese semestre: ", &temp.semestre);
            lista->comparar = compararSemestre;
            break;
        case 4:
            inputFloat("\n Ingrese promedio: ", &temp.promedio);
            lista->comparar = compararPromedio;
            break;
        default:
            printf("\n *** Opcion invalida. ***\n");
            lista->comparar = comparadorOriginal;
            return;
    }
    
    res = buscar(*lista, &temp);
    
    if (res.enco) {
        printf("\n\n *** ALUMNO ENCONTRADO ***");
        printf("\n %-7s | %-40s | %-8s | %-8s", "MATRIC", "NOMBRE", "SEMESTRE", "PROMEDIO");
        printf("\n--------+-----------------------------------------+----------+----------");
        imprimirAlumno(res.dato);
        printf("\n");
    } else {
        printf("\n *** Alumno NO encontrado. ***\n");
    }
    
    lista->comparar = comparadorOriginal;
}


void borrarAlumno(Lista *lista)
{
    unsigned int matricula;
    Alumno temp;
    Resultado res;
    int (*comparadorOriginal)(void*, void*) = lista->comparar;
    char confirmacion;
    
    
    printf("\n   BORRAR ALUMNO");
    
    
    if (!lista->inicio) {
        printf("\n No hay alumnos registrados para borrar.\n");
        return;
    }
    
    inputEnteroSinSigno("\n Ingrese la matricula del alumno a eliminar: ", &matricula);
    
    temp.matricula = matricula;
    lista->comparar = compararMatricula;
    
    res = buscar(*lista, &temp);
    
    if (res.enco) {
        printf("\n Alumno a eliminar:");
        printf("\n %-7s | %-40s | %-8s | %-8s", "MATRIC", "NOMBRE", "SEMESTRE", "PROMEDIO");
        printf("\n--------+-----------------------------------------+----------+----------");
        imprimirAlumno(res.dato);
        printf("\n");
        
        inputChar("\n Esta seguro de eliminar este alumno? (s/n): ", &confirmacion);
        
        if (confirmacion == 's' || confirmacion == 'S') {
            eliminarDato(lista, &temp);
            printf("\n *** Alumno eliminado exitosamente! ***\n");
        } else {
            printf("\n *** Operacion cancelada. ***\n");
        }
    } else {
        printf("\n *** Alumno con matricula %u NO encontrado. ***\n", matricula);
    }
    
    lista->comparar = comparadorOriginal;
}

int main(void)
{
    
    Lista lista = {NULL, NULL, 0, imprimirAlumno, compararMatricula, free};
    int opcion;
    int continuar = 1;
    
   
    printf("\n BIENVENIDO AL SISTEMA DE GESTION");
    
    
    while (continuar) {
        mostrarMenu();
        inputEntero("", &opcion);
        
        switch(opcion) {
            case 1:
                registrarAlumno(&lista);
                break;
            case 2:
                desplegarAlumnos(lista);
                break;
            case 3:
                reordenarLista(&lista);
                break;
            case 4:
                buscarAlumno(&lista);
                break;
            case 5:
                borrarAlumno(&lista);
                break;
            case 6:
                printf("\n Finalizando programa...");
                printf("\n Gracias por usar el sistema!\n\n");
                continuar = 0;
                break;
            default:
                printf("\n *** Opcion invalida. Intente nuevamente. ***\n");
        }
        
        if (continuar) {
            printf("\n Presione ENTER para continuar...");
            getchar();
        }
    }
    
   
    while (lista.inicio) {
        eliminarInicio(&lista);
    }
    
    return 0;
}
