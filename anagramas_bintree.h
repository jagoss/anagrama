extern char * fgetword_normalizada (FILE *fp, char *word, int maxword);

struct listnode {	// representa un nodo de una lista simple, ordenada alfabéticamente
	char *pal;	// una palabra
	struct listnode *sig; // el siguiente nodo en la lista; NULL si no hay
};

typedef struct listnode LN; // un sinónimo para no tener que escribir "struct xxx"

struct treenode {	// representa un nodo de árbol binario ordenado por clave
	char *clave;	// la clave de las palabras que tienen el mismo anagrama
    int cantpal; // la cantidad de palabras que hay en la lista
	struct listnode *palabras;	// la lista de palabras
	struct treenode *izq;		// puntero a subárbol izquierdo
	struct treenode *der;		// puntero a subárbol derecho
};

typedef struct treenode TN; // un sinónimo para no tener que escribir "struct xxx"


/*
 * FUNCIONES A DESARROLLAR POR LOS ALUMNOS
 */

void generar_clave(char *clave, char *pal, int maxpal);
    /*  Genera la clave para la palabra (los anagramas deben tener la misma clave)
        El argumento clave es un puntero a un string, que debe tener alocado mínimo maxpal bytes
            A partir de la palabra, se genera una clave que se alojará en ese string
        El argumento pal es un puntero a un string, que debe tener alocado mínimo maxpal bytes
            Aloja la palabra
        El argumento maxpal es la cantidad de caracteres de clave y maxpal
        Es responsabilidad del invocador que clave y pal tengan ese espacio reservado
        La función transforma la palabra pal y genera la clave
    */


LN * list_agregar_pal(LN *lista, char *pal);
    /*  Agrega una palabra a una lista. Devuelve el puntero a la lista (eventualmente modificado)
        El argumento lista es el cabezal a la lista existente, o NULL si aún no hay lista
        El argumento pal es la palabra a insertar.
        Recordar crear memoria para insertar tanto el nodo como la palabra.
    */

TN * tree_agregar_pal(TN *raiz, char *pal);
    /*  Agrega un nodo al árbol. Devuelve el puntero a la raíz (eventualmente modificado)
        El argumento raiz es la raiz del árbol existente, o NULL si aún no hay árbol
        El argumento pal es la palabra a insertar (debe calcularse la clave)
        Recordar crear memoria para insertar tanto el nodo como la palabra.
    */

TN * tree_buscar_pal(TN *raiz, char *pal);
    /*  Busca la palabra en el árbol, retorna puntero si la encuentra, NULL si no lo hace
        El argumento raiz es la raiz del árbol existente, o NULL si aún no hay árbol
        El argumento pal es la palabra a buscar (debe calcularse la clave)
    */
