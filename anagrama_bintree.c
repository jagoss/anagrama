#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "anagramas_bintree.h"

#define MAXWORD 32

extern char *fgetword_normalizada(FILE *fp, char *word, int maxword);

/*
  HECHO POR: VICTORIA TEJERA, JUAN JOSE REGENT Y JUAN ANDRES GOSSWEILER
 */

void generar_clave(char *clave, char *pal, int maxpal) {
    int aux = 0;
    char ax;
    strcpy(clave, pal);
    for (int i = 1; i < strlen(clave); i++) {
        aux = i;
        while (aux > 0) {
            if (clave[aux] > clave[aux - 1]) {
                ax = clave[aux];
                clave[aux] = clave[aux - 1];
                clave[aux - 1] = ax;
                aux--;
            } else {
                aux--;
            }
        }
    }
}

/*  Genera la clave para la palabra (los anagramas deben tener la misma clave)
    El argumento clave es un puntero a un string, que debe tener alocado mínimo maxpal bytes
        A partir de la palabra, se genera una clave que se alojará en ese string
    El argumento pal es un puntero a un string, que debe tener alocado mínimo maxpal bytes
        Aloja la palabra
    El argumento maxpal es la cantidad de caracteres de clave y maxpal
    Es responsabilidad del invocador que clave y pal tengan ese espacio reservado
    La función transforma la palabra pal y genera la clave
*/


LN *list_agregar_pal(LN *lista, char *pal) {

    LN *nuevo = malloc(sizeof(LN));
    nuevo->pal = strdup(pal);
    nuevo->sig = lista;
    return nuevo;
}

/*  Agrega una palabra a una lista. Devuelve el puntero a la lista (eventualmente modificado)
        El argumento lista es el cabezal a la lista existente, o NULL si aún no hay lista
        El argumento pal es la palabra a insertar.
        Recordar crear memoria para insertar tanto el nodo como la palabra.
    */

TN *tree_agregar_pal(TN *p, char *w) {

    int cond;

    char clave[MAXWORD];
    generar_clave(clave, w, MAXWORD);

    if (p == NULL) {                    /* a new word has arrived */
        p = malloc(sizeof(TN)); /* make a new node */
        p->clave = strdup(clave);
        p->palabras = list_agregar_pal(p->palabras, w);
        p->cantpal = 1;

    } else if ((cond = strcmp(clave, p->clave)) == 0) {

        p->palabras = list_agregar_pal(p->palabras, w);               /* repeated word */
        p->cantpal = ++(p->cantpal);

    } else if (cond < 0) {              /* less than into left subtree */
        p->izq = tree_agregar_pal(p->izq, w);
    } else {                            /* greater than into right subtree */
        p->der = tree_agregar_pal(p->der, w);
    }

    return p;
}

/*  Agrega un nodo al árbol. Devuelve el puntero a la raíz (eventualmente modificado)
    El argumento raiz es la raiz del árbol existente, o NULL si aún no hay árbol
    El argumento pal es la palabra a insertar (debe calcularse la clave)
    Recordar crear memoria para insertar tanto el nodo como la palabra.
*/

TN *tree_buscar_pal(TN *raiz, char *pal) {

    int cond;
    TN *devuelve;

    char clave[MAXWORD];
    generar_clave(clave, pal, MAXWORD);

    if (raiz == NULL) {
        printf("NO EXISTE ARBOL \n");
        return NULL;

    } else if ((cond = strcmp(clave, raiz->clave)) == 0) {

        devuelve = raiz;

    } else if (cond < 0) {
        devuelve = tree_buscar_pal(raiz->izq, pal);
    } else {
        devuelve = tree_buscar_pal(raiz->der, pal);
    }

    return devuelve;
}

/*  Busca la palabra en el árbol, retorna puntero si la encuentra, NULL si no lo hace
    El argumento raiz es la raiz del árbol existente, o NULL si aún no hay árbol
    El argumento pal es la palabra a buscar (debe calcularse la clave)
*/

TN *crear_arbol_dic(char *nombrearchivo) {

    FILE *fp = fopen(nombrearchivo, "r");

    if (fp == NULL) {
        printf("ERROR ARCHIVO VACIO \n");
        return NULL;
    }

    TN *arboldic;
    char word[MAXWORD];

    while (fgetword_normalizada(fp, word, MAXWORD) != NULL) {
        arboldic = tree_agregar_pal(arboldic, word);
    }

    return arboldic;
}


int main(int argc, char *argv[]) {

    TN *miarbol = crear_arbol_dic("/home/juan/Documents/facultad/s5/tic2/anagrama/dir/spanish");

    for (int i = 1; i < argc; i++) {
        *argv++;

        TN *resultado = tree_buscar_pal(miarbol, *argv);

        LN *palabras = resultado->palabras;

        printf("%s: \n", *argv);

        while (palabras != NULL) {
            printf("\t%s\n", palabras->pal);
            palabras = palabras->sig;
        }
    }
    return 0;
}