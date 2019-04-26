/*
 * fgetword_normalizada: lee una palabra en español de un archivo, la normaliza
 * (saca tildes y eñes y las convierte en vocales y enes)
 *
 */

#include <locale.h>
#include <wctype.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

static
char
normalizar(wchar_t wc)  // devuelve la vocal no acentuada, o convierte eñe en ene (min y may)
{
    static wchar_t *a_convertir = L"áéíóúÁÉÍÓÚüÜñÑ";
    static char *convertido = "aeiouAEIOUuUnN";

    size_t i;

    for (i=0; a_convertir[i] != L'\0'; i++) {
        if (wc == a_convertir[i]) {
            return convertido[i];
        }
    }
    return (char) wc;
}


static
wchar_t *
wcfgetword (FILE *fp, wchar_t *word, int maxword)	// carga una palabra nueva en word, retorna word o NULL
{
	enum { FUERA, DENTRO };		// fuera o dentro de palabra
	int estado = FUERA;
	wint_t c;
	wchar_t *s = word;

    static char *loc = NULL;

	if (loc == NULL) {          // ejecuta solamente una vez
        if ( (loc = setlocale(LC_CTYPE, "")) == NULL) { 
            perror("setlocale");
            exit(1);
        }
    }

	for (;;) {
		if ((s - word) >= (maxword - 1)) {	// chequeo lugar en word
			break;	// no hay lugar, igual doy la palabra por terminada
		}
		if ( (c=fgetwc(fp)) == WEOF) {		// fin de archivo, idem
			if (s == word) return NULL;	// no hay palabra para leer
			else break;			// si no hay \n antes de EOF igual lo acepto
		}
		if (estado == DENTRO && !iswalpha(c)) {	// fin de palabra
			estado=FUERA;
			break;
		} else if (estado == DENTRO && iswalpha(c)) {	// sigue palabra
			*s++ = (wchar_t) c;
		} else if (estado == FUERA && iswalpha(c)) {	// arranca palabra
			*s++ = (wchar_t) c;
			estado=DENTRO;
		}	// la otra alternativa es FUERA y !isalpha, salteo ese caracter
	}
	*s=(wchar_t)0;
	return word;
}


char *
fgetword_normalizada (FILE *fp, char *word, int maxword)
{
    char *s;
	wchar_t *wc, wcword[maxword];

    if (wcfgetword (fp, wcword, maxword) == (wchar_t)0) // carga la palabra de widechar
        return NULL;

    for (wc = wcword, s=word; *wc != L'\0'; wc++, s++) { // convierte carácter a carácter
        *s = normalizar(*wc);
    }
    *s = '\0';
    return word;
}
