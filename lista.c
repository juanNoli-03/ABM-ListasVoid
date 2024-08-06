#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "string.h"

///INCLUIMOS NUESTRO ARCHIVO.H
#include "lista.h"

///INICIALIZAMOS LA ESTRUCTURA DE LA LISTA Y DEL NODO
struct NodoE {

    NodoP proximo;

    void * item; //Puntero a cualquier cosa (Void)
};

struct ListaE {

    NodoP inicio;

    int tamDato; //Debemos guardar el tamaño del dato en bytes!

    int tam; //Tamaño de la lista
};
///---------------------------------------------------------------------------------------

///IMPLEMENTACIONES DE LAS PRIMITIVAS

///1- Construccion de la lista y del nodo
///-----------------------------------------------------------------------------------------
ListaP crearlista (int tamDato) {  //Recibe el "sizeof (dato)" para determinar que tipo de dato vamos a alojar en nuestra lista

    ListaP lista = malloc (sizeof(struct ListaE));

    lista->inicio = NULL; //El nodo del inicio apunta a NULL.

    lista->tam = 0; //El tamaño de la lista lo inicializamos en 0.

    lista->tamDato = tamDato; //Nuevo! Le asignamos el tamaño en bytes del dato que vamos a alojar en nuestra lista.

    return lista;
}

NodoP crearNodo (ListaP lista, NodoP proximo, void * item) { //Dato del tipo void ya que no sabemos de que tipo va a ser ese dato. El puntero apunta a cualquier cosa.

    NodoP node = malloc (sizeof(struct NodoE));

    node->item = malloc (lista->tamDato); //Reservamos memoria para el dato que vamos a guardar. Todavia no sabemos que tipo de dato es.

    //Una vez que reservamos memoria, guardamos el item en el item del nodo: node->item = item. Debemos realizar el casteo.

    memcpy (node->item, item, lista->tamDato); //("Donde vamos a guadar el item", "Item que vamos a guardar", "Tamaño de del item").

    node->proximo = proximo; //Apuntamos al proximo nodo.

    return node;
}
///-----------------------------------------------------------------------------------------

///2- Inserccion de nodos (inicio - pos - final)
///-----------------------------------------------------------------------------------------
int insertarInicio (ListaP lista, void * item) {

    if (lista == NULL) {

        return ESTRUCTURA_NO_INICIALIZADA;
    }

    NodoP node = crearNodo (lista, lista->inicio, item); //Creamos el nodo para insertar al inicio de la lista.

     if (node == NULL) {

        return ESTRUCTURA_NO_INICIALIZADA;
    }

    lista->inicio = node; //Colocamos el nodo al inicio de la lista.

    lista->tam ++; //Aumentamos el tamaño de la lista.

    return OK;
}

int insertar (ListaP lista, void * item, int pos) {

    if (lista == NULL) {

        return ESTRUCTURA_NO_INICIALIZADA;
    }

    if (pos > lista->tam || pos < 0) {

        return INDICE_INVALIDO;
    }

    if (pos == 0) {

        return insertarInicio (lista, item);

    } else {

        NodoP aux; //Creamos un nodo auxiliar.

        aux = lista->inicio; //Nos paramos con el auxiliar en el inicio de la lista.

        for (int i = 0; i < pos - 1; i ++) {

            aux = aux->proximo; //Nos vamos moviendo de nodo en nodo hasta llegar al nodo en la posicion anterior en la cual queremos insertar.
        }

        NodoP node = crearNodo (lista, aux->proximo, item); //Creamos el nodo y lo enlazamos con el nodo que esta en la pos donde queremos insertar.

        if (node == NULL) {

            return ESTRUCTURA_NO_INICIALIZADA;
        }

        aux->proximo = node; //Agregamos al nodo en la posicion que nosotros queremos.

        lista->tam ++; //Aumentamos el tamaño de la lista.

        return OK;
    }
}

int insertarFinal (ListaP lista, void * item) {

    return insertar (lista, item, lista->tam);
}
///-----------------------------------------------------------------------------------------

///4- Remover nodos (inicio - pos - final)
///-----------------------------------------------------------------------------------------
int removerInicio (ListaP lista, void * itemEliminado) {

    if (lista == NULL) {

        return ESTRUCTURA_NO_INICIALIZADA;
    }

    NodoP aux = lista->inicio; //Creamos un nodo auxiliar y nos paramos en el inicio de la lista.

    lista->inicio = aux->proximo; //Hacemos que el inicio de la lista apunte al segundo nodo, el de la pos 1.

    if (itemEliminado != NULL) {

        memcpy (itemEliminado, aux->item, lista->tamDato); //Guardamos el item eliminado en el item que pasamos por parametro.
    }

    free (aux); //Liberamos el auxiliar.

    aux = NULL; //Lo igualamos a NULL.

    lista->tam --; //Disminuimos el tamaño de la lista.

    return OK;
}

int remover (ListaP lista, void * itemEliminado, int pos) {

    if (lista == NULL) {

        return ESTRUCTURA_NO_INICIALIZADA;
    }

    if (pos < 0 || pos >= lista->tam) {

        return INDICE_INVALIDO;
    }

    if (pos == 0) {

        return removerInicio (lista, itemEliminado);

    } else {

        NodoP actual; //Creamos un nodo auxiliar que va a apuntar a la posicion actual.

        NodoP anterior; //Creamos un nodo auxiliar que va a apuntar a la posicion anterior.

        actual = lista->inicio; //Apuntamos con el nodo actual al inicio de la lista.

         anterior = NULL; //Apuntamos con el nodo anterior a NULL ya que apunta a la posicion -1.

        for (int i = 0; i < pos; i ++) {

            anterior = actual; //El nodo anterior se para donde esta el actual.

            actual = actual->proximo; //Nos movemos de posicion con el nodo actual.

            //Resultado final: Nos tendria que quedar el nodo anterior parado en la pos - 1 y el nodo actual en la pos donde queremos eliminar.
        }

        anterior->proximo = actual->proximo; //Sobreescribimos los datos.


        if (itemEliminado != NULL) {

            memcpy (itemEliminado, actual->item, lista->tamDato); //Guardamos el item eliminado en el item que pasamos por parametro.
        }

        free (actual); //Liberamos el nodo actual.

        actual = NULL; //Lo igualamos a NULL.

        lista->tam --; //Disminuimos el tamaño de la lista.
    }

    return OK;
}

int removerFinal (ListaP lista, void * item) {

    return remover (lista, item, lista->tam - 1);
}
///-----------------------------------------------------------------------------------------

///5- Getters
///-----------------------------------------------------------------------------------------
int getSizeLista (ListaP lista, int * tam) {

    if (lista == NULL) {

        return ESTRUCTURA_NO_INICIALIZADA;
    }

    * tam = lista->tam;

    return OK;
}

void * getElementoInicio (ListaP lista) {

    if (lista == NULL) {

        return NULL;
    }

    NodoP aux; //Definimos un nodo auxiliar.

    aux = lista->inicio; //Nos paramos en el inicio de la lista.

    return aux->item; //Retornamos el elemento del inicio.
}

void * getElemento (ListaP lista, int pos) {

    if (lista == NULL) {

        return NULL;
    }

    if (pos < 0 || pos >= lista->tam) {

        return NULL;
    }

    NodoP aux; //Creamos un nodo auxiliar con el que vamos a ir recorriendo la lista.

    aux = lista->inicio; //Nos paramos en el inicio de la lista.

    for (int i = 0; i < pos; i ++) {

        aux = aux->proximo; //Nos vamos moviendo de nodo en nodo hasta llegar al que queremos obtener.
    }

    return aux->item; //Retornamos el item que queremos obtener.
}

void * getElementoFinal (ListaP lista) {

    if (lista == NULL) {

        return NULL;
    }

    return getElemento (lista, lista->tam - 1);
}
///-----------------------------------------------------------------------------------------

///6- Setters
///-----------------------------------------------------------------------------------------
void setElemento (ListaP lista, void * item, int pos) {

    NodoP aux = lista->inicio; //Nos paramos en el inicio de la lista.

    for (int i = 0; i < pos; i ++) {

        aux = aux->proximo; //Nos movemos hasta llegar al elemeto que queremos setear.
    }

    memcpy (aux->item, item, lista->tamDato); //Lo seteamos con el elemento pasado por parametro.
}
///-----------------------------------------------------------------------------------------

///7- DuplicarLista
///-----------------------------------------------------------------------------------------
void duplicarLista (ListaP lista1, ListaP lista2) {

    int tam;

    getSizeLista (lista1, &tam); //Obtenemos el tamaño de la lista.

    NodoP aux; //Definimos un nodo auxiliar.

    aux = lista1->inicio; //Nos paramos en el inicio de la lista1.

    for (int i = 0; i < tam; i ++) {

        insertarFinal (lista2, aux->item); //En la lista2, vamos insertando los elementos al final de la misma.

        aux = aux->proximo; //Nos movemos hacia el proximo elemento.
    }
}
///-----------------------------------------------------------------------------------------

///8- Funciones Auxiliares
///-----------------------------------------------------------------------------------------
int estaVacia (ListaP lista) {

    if (lista->inicio == NULL) {

        return TRUE;

    } else {

        return FALSE;
    }
}

void liberarLista (ListaP lista) {

    if (estaVacia(lista)) {

        printf ("\nLa lista no puede ser liberada ya que esta vacia\n");

        return;

    } else {

        int tam;

        getSizeLista (lista, &tam); //Obtenemos el tamaño de la lista.

        NodoP aux; //Definimos un nodo auxiliar.

        NodoP actual = lista->inicio; //Nos paramos en el nodo del inicio.

        for (int i = 0; i < tam; i ++) {

            aux =  actual; //El auxiliar toma la misma posicion que el actual.

            actual = actual->proximo; //El actual apunta al proximo nodo.

            free (aux->item); //Liberamos el auxiliar.

            aux = NULL; //Lo igualamos a NULL.
        }

        lista->inicio = NULL; //Igualamos el inicio de la lista a NULL.

        lista->tam = 0; //Reiniciamos su tamaño

        if (estaVacia(lista)) {

            printf ("\nLista liberada exitosamente\n");
        }
    }
}
///-----------------------------------------------------------------------------------------
