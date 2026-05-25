#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "HashQ.h"
#include "Libro.h"
#include "arbol.h"
#include "nodoarbol.h"


#define FACTOR_MIN  0
#define FACTOR_MAX  60
#define FACTOR_FIJO 45
#define TAM_INICIAL 101


static HashQTable tablaISBN;
static HashQTable tablaTitulo;
static HashQTable tablaAutor;
static HashQTable tablaFecha;
static HashQTable tablaInicialTitulo;
static HashQTable tablaInicialAutor;



static int ci_cmp(const char *a, const char *b);


static int folding_isbn      (void *v);
static int folding_titulo    (void *v);
static int folding_autor     (void *v);
static int folding_fecha     (void *v);
static int folding_ini_titulo(void *v);
static int folding_ini_autor (void *v);


static int cmp_isbn      (void *a, void *b);
static int cmp_titulo    (void *a, void *b);
static int cmp_autor     (void *a, void *b);
static int cmp_fecha     (void *a, void *b);
static int cmp_ini_titulo(void *a, void *b);
static int cmp_ini_autor (void *a, void *b);


static int arbol_cmp_titulo   (void *a, void *b);
static int arbol_cmp_fecha    (void *a, void *b);
static int arbol_cmp_ini_autor(void *a, void *b);


static HashQTable crear_tabla(fn_folding fold, fn_comparar cmp);


int    folding (void *data);
void   imprimir(void *data);
char** datos   (void);



int main(void)
{

    int    op, op2, anio, linf_a, lsup_a;
    char   buf[64], li[4], ls[4];
    char   linf_c, lsup_c;
    Libro  clave;
    Libro *encontrado;
    Arbol  resultado;
    size_t i;

    Acervo acervo = obtener_libros();

    tablaISBN          = crear_tabla(folding_isbn,        cmp_isbn);
    tablaTitulo        = crear_tabla(folding_titulo,      cmp_titulo);
    tablaAutor         = crear_tabla(folding_autor,       cmp_autor);
    tablaFecha         = crear_tabla(folding_fecha,       cmp_fecha);
    tablaInicialTitulo = crear_tabla(folding_ini_titulo,  cmp_ini_titulo);
    tablaInicialAutor  = crear_tabla(folding_ini_autor,   cmp_ini_autor);


    for (int i = 0; i < (int)acervo.cantidad; i++) {
        Libro *l = acervo.libros + i;
        fn_insertKey(&tablaISBN,          l); remap(&tablaISBN);
        fn_insertKey(&tablaTitulo,        l); remap(&tablaTitulo);
        fn_insertKey(&tablaAutor,         l); remap(&tablaAutor);
        fn_insertKey(&tablaFecha,         l); remap(&tablaFecha);
        fn_insertKey(&tablaInicialTitulo, l); remap(&tablaInicialTitulo);
        fn_insertKey(&tablaInicialAutor,  l); remap(&tablaInicialAutor);
    }

    setvbuf(stdout, NULL, _IONBF, 0);
    fflush(stdout);


    do {
        printf("\n\n CIMACERVO MENU PRINCIPAL :)...\n");
        printf("\n\n Buscar por...\n");
        printf("\n 1. Buscar por ISBN");
        printf("\n 2. Buscar por Titulo");
        printf("\n 3. Buscar por Autor");
        printf("\n 4. Buscar por Fecha");
        printf("\n 5. Eliminar libro");
        printf("\n 0. Salir");
        printf("\n Opcion: ");
        fflush(stdout);
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            printf("  ISBN: ");
            scanf(" %19s", buf);
            strcpy(clave.isbn, buf);
            encontrado = fn_searchKey(&tablaISBN, &clave);
            if (encontrado) { printf("\n Encontrado:\n "); imprimirLibro(encontrado); }
            else              printf("\n ISBN no encontrado.");
            break;

        case 2:
            do {
                printf("\n titulo");
                printf("\n  1. Titulo exacto");
                printf("\n  2. Rango de iniciales");
                printf("\n  0. Volver");
                printf("\n  Opcion: ");
                scanf(" %d", &op2);

                if (op2 == 1)
                {
                    printf("  Titulo: ");
                    scanf(" %44[^\n]", buf);
                    strcpy(clave.titulo, buf);
                    encontrado = fn_searchKey(&tablaTitulo, &clave);
                    if (encontrado) { printf("\n Encontrado:\n "); imprimirLibro(encontrado); }
                    else              printf("\n Titulo no encontrado.");
                }
                else if (op2 == 2)
                {
                    printf("  Inicial inferior (ej. A): ");
                    scanf(" %3s", li);
                    printf("  Inicial superior (ej. M): ");
                    scanf(" %3s", ls);
                    linf_c = tolower((unsigned char)li[0]);
                    lsup_c = tolower((unsigned char)ls[0]);

                    resultado.raiz     = NULL;
                    resultado.cantidad = 0;
                    resultado.imprimir = imprimirLibro;
                    resultado.comparar = arbol_cmp_titulo;
                    resultado.liberar  = NULL;

                    for (clave.titulo[0] = linf_c;
                         clave.titulo[0] <= lsup_c;
                         clave.titulo[0]++)
                        if (fn_searchKey(&tablaInicialTitulo, &clave))
                            for (i = 0; i < acervo.cantidad; i++) {
                                char ini = tolower((unsigned char)acervo.libros[i].titulo[0]);
                                if (ini == (char)clave.titulo[0])
                                    insertarArbol(&resultado, acervo.libros + i);
                            }

                    printf("\n Titulos de '%c' a '%c':", toupper(linf_c), toupper(lsup_c));
                    imprimirOrden(resultado, ORDEN);
                    eliminarArbol(&resultado);
                }
            } while (op2 != 0);
            break;

        case 3:
            do {
                printf("\n autro ");
                printf("\n  1. Nombre exacto");
                printf("\n  2. Rango de iniciales");
                printf("\n  0. Volver");
                printf("\n  Opcion: ");
                scanf(" %d", &op2);

                if (op2 == 1)
                {
                    printf(" autor");
                    scanf(" %29[^\n]", buf);
                    strcpy(clave.autor, buf);
                    encontrado = fn_searchKey(&tablaAutor, &clave);
                    if (!encontrado) { printf("\n Autor no encontrado."); break; }

                    resultado.raiz     = NULL;
                    resultado.cantidad = 0;
                    resultado.imprimir = imprimirLibro;
                    resultado.comparar = arbol_cmp_fecha;
                    resultado.liberar  = NULL;

                    for (i = 0; i < acervo.cantidad; i++) {
                        strcpy(clave.autor, buf);
                        if (cmp_autor(acervo.libros + i, &clave) == 0)
                            insertarArbol(&resultado, acervo.libros + i);
                    }
                    printf("\n Libros de \"%s\" (por fecha):", buf);
                    imprimirOrden(resultado, ORDEN);
                    eliminarArbol(&resultado);
                }
                else if (op2 == 2)
                {
                    printf("  Inicial inferior autor (ej. A): ");
                    scanf(" %3s", li);
                    printf("  Inicial superior autor (ej. M): ");
                    scanf(" %3s", ls);
                    linf_c = tolower((unsigned char)li[0]);
                    lsup_c = tolower((unsigned char)ls[0]);

                    resultado.raiz     = NULL;
                    resultado.cantidad = 0;
                    resultado.imprimir = imprimirLibro;
                    resultado.comparar = arbol_cmp_ini_autor;
                    resultado.liberar  = NULL;

                    for (clave.autor[0] = linf_c;
                         clave.autor[0] <= lsup_c;
                         clave.autor[0]++)
                        if (fn_searchKey(&tablaInicialAutor, &clave))
                            for (i = 0; i < acervo.cantidad; i++) {
                                char ini = tolower((unsigned char)acervo.libros[i].autor[0]);
                                if (ini == (char)clave.autor[0])
                                    insertarArbol(&resultado, acervo.libros + i);
                            }

                    printf("\n Autores de '%c' a '%c':", toupper(linf_c), toupper(lsup_c));
                    imprimirOrden(resultado, ORDEN);
                    eliminarArbol(&resultado);
                }
            } while (op2 != 0);
            break;

        case 4:
            do {
                printf("\n fecha");
                printf("\n  1. Anio exacto");
                printf("\n  2. Rango de anios");
                printf("\n  0. Volver");
                printf("\n  Opcion: ");
                scanf(" %d", &op2);

                if (op2 == 1)
                {
                    printf("  anno ");
                    scanf(" %d", &anio);
                    clave.fecha = anio;
                    if (!fn_searchKey(&tablaFecha, &clave))
                        { printf("\n No hay libros de ese anio."); break; }

                    resultado.raiz     = NULL;
                    resultado.cantidad = 0;
                    resultado.imprimir = imprimirLibro;
                    resultado.comparar = arbol_cmp_titulo;
                    resultado.liberar  = NULL;

                    for (i = 0; i < acervo.cantidad; i++)
                        if (acervo.libros[i].fecha == anio)
                            insertarArbol(&resultado, acervo.libros + i);

                    printf("\n Libros del anio %d (por titulo):", anio);
                    imprimirOrden(resultado, ORDEN);
                    eliminarArbol(&resultado);
                }
                else if (op2 == 2)
                {
                    printf("  Anio inferior: ");
                    scanf(" %d", &linf_a);
                    printf("  Anio superior: ");
                    scanf(" %d", &lsup_a);

                    resultado.raiz     = NULL;
                    resultado.cantidad = 0;
                    resultado.imprimir = imprimirLibro;
                    resultado.comparar = arbol_cmp_fecha;
                    resultado.liberar  = NULL;

                    for (clave.fecha = linf_a; clave.fecha <= lsup_a; clave.fecha++)
                        if (fn_searchKey(&tablaFecha, &clave))
                            for (i = 0; i < acervo.cantidad; i++)
                                if (acervo.libros[i].fecha == clave.fecha)
                                    insertarArbol(&resultado, acervo.libros + i);

                    printf("\n Libros de %d a %d (por fecha y titulo):", linf_a, lsup_a);
                    imprimirOrden(resultado, ORDEN);
                    eliminarArbol(&resultado);
                }
            } while (op2 != 0);
            break;

        case 5:
            do {
                printf("\n eliminar...\n");
                printf("\n  1. Eliminar libro por ISBN");
                printf("\n  0. Volver");
                printf("\n  Opcion: ");
                scanf(" %d", &op2);

                if (op2 == 1)
                {
                    printf("  ISBN a eliminar: ");
                    scanf(" %19s", buf);
                    strcpy(clave.isbn, buf);
                    encontrado = fn_searchKey(&tablaISBN, &clave);
                    if (!encontrado) { printf("\n ISBN no encontrado."); break; }

                    printf("\n Eliminando:\n ");
                    imprimirLibro(encontrado);

                    fn_deleteKey(&tablaISBN,          encontrado); remap(&tablaISBN);
                    fn_deleteKey(&tablaTitulo,        encontrado); remap(&tablaTitulo);
                    fn_deleteKey(&tablaAutor,         encontrado); remap(&tablaAutor);
                    fn_deleteKey(&tablaFecha,         encontrado); remap(&tablaFecha);
                    fn_deleteKey(&tablaInicialTitulo, encontrado); remap(&tablaInicialTitulo);
                    fn_deleteKey(&tablaInicialAutor,  encontrado); remap(&tablaInicialAutor);

                    printf("\n Libro eliminado de las 6 tablas.");
                }
            } while (op2 != 0);
            break;
        }
    } while (op != 0);

    printf("\n\n FIN DE PROGRAMA\n");
    return 0;
}



static int ci_cmp(const char *a, const char *b)
{
    while (*a && *b) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d) return d;
        a++; b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

static int folding_isbn(void *v)
{
    const char *s = ((Libro*)v)->isbn;
    int key=0, sector=1, suma=0, cont=0;
    for (int i=0; s[i]; i++) {
        if (s[i]=='-') continue;
        suma += s[i]; cont++;
        if (cont%3==0) { key+=sector*suma; suma=0; sector++; }
    }
    return abs(key + sector*suma);
}

static int folding_titulo(void *v)
{
    const char *s = ((Libro*)v)->titulo;
    int key=0, sector=1, suma=0;
    for (int i=0; s[i]; i++) {
        suma += tolower((unsigned char)s[i]);
        if (i && (i+1)%3==0) { key+=sector*suma; suma=0; sector++; }
    }
    return abs(key + sector*suma);
}

static int folding_autor(void *v)
{
    const char *s = ((Libro*)v)->autor;
    int key=0, sector=1, suma=0;
    for (int i=0; s[i]; i++) {
        suma += tolower((unsigned char)s[i]);
        if (i && (i+1)%3==0) { key+=sector*suma; suma=0; sector++; }
    }
    return abs(key + sector*suma);
}

static int folding_fecha(void *v)
{
    return abs(((Libro*)v)->fecha);
}

static int folding_ini_titulo(void *v)
{
    return tolower((unsigned char)((Libro*)v)->titulo[0]);
}

static int folding_ini_autor(void *v)
{
    return tolower((unsigned char)((Libro*)v)->autor[0]);
}

static int cmp_isbn(void *a, void *b)
{
    return strcmp(((Libro*)a)->isbn, ((Libro*)b)->isbn);
}

static int cmp_titulo(void *a, void *b)
{
    return ci_cmp(((Libro*)a)->titulo, ((Libro*)b)->titulo);
}

static int cmp_autor(void *a, void *b)
{
    return ci_cmp(((Libro*)a)->autor, ((Libro*)b)->autor);
}

static int cmp_fecha(void *a, void *b)
{
    return ((Libro*)a)->fecha - ((Libro*)b)->fecha;
}

static int cmp_ini_titulo(void *a, void *b)
{
    return tolower((unsigned char)((Libro*)a)->titulo[0])
         - tolower((unsigned char)((Libro*)b)->titulo[0]);
}

static int cmp_ini_autor(void *a, void *b)
{
    return tolower((unsigned char)((Libro*)a)->autor[0])
         - tolower((unsigned char)((Libro*)b)->autor[0]);
}

static int arbol_cmp_titulo(void *a, void *b)
{
    return ci_cmp(((Libro*)a)->titulo, ((Libro*)b)->titulo);
}

static int arbol_cmp_fecha(void *a, void *b)
{
    int d = ((Libro*)a)->fecha - ((Libro*)b)->fecha;
    return d ? d : ci_cmp(((Libro*)a)->titulo, ((Libro*)b)->titulo);
}

static int arbol_cmp_ini_autor(void *a, void *b)
{
    int d = tolower((unsigned char)((Libro*)a)->autor[0])
          - tolower((unsigned char)((Libro*)b)->autor[0]);
    return d ? d : ci_cmp(((Libro*)a)->titulo, ((Libro*)b)->titulo);
}

static HashQTable crear_tabla(fn_folding fold, fn_comparar cmp)
{
    HashQTable t;
    t.table    = calloc(TAM_INICIAL, sizeof(void*));
    t.len      = TAM_INICIAL;
    t.cant     = 0;
    t.min      = FACTOR_MIN;
    t.max      = FACTOR_MAX;
    t.fixed    = FACTOR_FIJO;
    t.folding  = fold;
    t.comparar = cmp;
    t.imprimir = imprimirLibro;
    t.verbose  = 0;
    return t;
}

int folding(void *data)
{
    char *cadena = data;
    int key=0, sector=1, sumatoria=0;
    for (int i=0; cadena[i]!='\0'; i++) {
        sumatoria += cadena[i];
        if (i!=0 && (i+1)%3==0) { key+=sector*sumatoria; sumatoria=0; sector++; }
    }
    return key + sector*sumatoria;
}

void imprimir(void *data) { printf("%s", (char*)data); }

char** datos(void)
{
    static char *cadenas[] = {
    "alberto","goku","pepe","luna","sol","mar","rio","cielo","nube","viento",
    "fuego","tierra","roca","arena","bosque","hoja","flor","raiz","tronco","rama",
    "perro","gato","lobo","zorro","oso","tigre","leon","raton","conejo","ciervo",
    "pajaro","aguila","halcon","cuervo","paloma","pez","tiburon","delfin","ballena","pulpo",
    "rojo","azul","verde","amarillo","negro","blanco","gris","rosa","morado","naranja",
    "uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve","diez",
    "enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre",
    "noviembre","diciembre","lunes","martes","miercoles","jueves","viernes","sabado","domingo","hora",
    "minuto","segundo","tiempo","espacio","energia","luz","sombra","eco","sonido","silencio",
    "camino","ruta","sendero","via","puente","puerta","ventana","techo","pared","suelo",
    "mesa","silla","cama","sofa","puerta","llave","candado","caja","bolsa","mochila",
    "lapiz","pluma","cuaderno","libro","hoja","papel","tinta","color","regla","borrador",
    "codigo","programa","dato","variable","funcion","bucle","arreglo","puntero","memoria","proceso",
    "nodo","lista","arbol","grafo","pila","cola","byte","bit","kernel","sistema",
    "usuario","clave","red","servidor","cliente","puerto","ip","socket","paquete","protocolo",
    "html","css","java","python","csharp","ruby","swift","kotlin","go","rust",
    "linux","windows","macos","android","ios","ubuntu","debian","fedora","arch","mint",
    "intel","amd","nvidia","cpu","gpu","ram","ssd","hdd","placa","fuente",
    "monitor","teclado","raton","pantalla","audio","video","imagen","foto","pixel","vector",
    "algoritmo","logica","calculo","numero","formula","ecuacion","teoria","modelo","simulacion","analisis",
    "salud","mente","cuerpo","vida","amor","odio","paz","guerra","fuerza","valor"
    };
    return cadenas;
}
