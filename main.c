#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "time.h"

///INCLUIMOS NUESTRO ARCHIVO.H
#include "lista.h"

///FUNCIONES AUXILIARES
//Estas funciones deben ser implementadas si o si en el main ya que para realizarlas necesitamos saber de que tipo es del dato con el que vamos a
//trabajar, no se pueden hacer de manera generica.
///--------------------------------------------------------------
void imprimirLista (ListaP lista) {

    int tam;

    getSizeLista (lista, &tam);

    printf ("\n---IMPRESION DE LA LISTA CREADA---\n");

    printf ("\n[");

    for (int i = 0; i < tam; i ++) {

        int item = *((int *) getElemento (lista, i));

        printf (" %d ", item);
    }

    printf ("]\n");
}

void ordenarLista (ListaP lista) {

    int aux1;

    int aux2;

    int tam;

    getSizeLista (lista, &tam);

    for (int j = 0; j < tam; j ++) {

        for (int i = 0; i < tam - 1; i ++) {

            if (*((int *)getElemento (lista, i)) > *((int *) getElemento (lista, i + 1))) {

                aux1 = *((int *)getElemento (lista, i)); //Obtengo el elemento de la pos i

                aux2 = *((int *)getElemento (lista, i + 1)); //Obtengo el elemento de la pos i + 1

                setElemento (lista, &aux1, i + 1); //Seteo el elemento de la pos i en la pos i + 1

                setElemento (lista, &aux2, i);

            }

        }
    }
}

int busquedaElemento (ListaP lista, void * item) {

    int pos = -1;

    int tam;

    getSizeLista (lista, &tam);

    for (int i = 0; i < tam; i ++) {

        if (*((int *) getElemento (lista, i)) == *((int *) item)) {

            pos = i;

            i = i + tam;
        }

    }

    return pos;
}

void chequearBusqueda (ListaP lista, void * item) {

    int pos = busquedaElemento (lista, item);

    if (pos != -1) {

        printf ("\n\nEl item %d se encontro en tu lista y esta en la posicion %d\n", *((int *)item), pos);

    } else {

        printf ("\nTu item %d no se encontro en tu lista\n", *((int *)item));
    }
}
///--------------------------------------------------------------

int main()
{
    ///0- Creacion de ambas listas. Como vamos a guardar enteros, les pasamos el tamaño de una variable INT.
    ///--------------------------------------------------------------
    ListaP lista1 = crearlista (sizeof(int));
    ListaP lista2 = crearlista (sizeof(int));
    ///--------------------------------------------------------------


    ///1- Insertamos items a la Lista1 y la mostramos.
    ///--------------------------------------------------------------
    printf ("\n1- INSERTAMOS ITEMS A LA LISTA1 Y LA MOSTRAMOS\n");
    printf ("--------------------------------------------------------------\n");
    int item; //Definimos un item de tipo int.

    item = 90;
    insertarInicio (lista1, &item); //Lo insertamos al inicio.

    item = 30;
    insertar (lista1, &item, 1); //Lo insertamos en la posicion que deseemos.

    item = 50;
    insertarFinal (lista1, &item); //Lo insertamos al final.

    item = 20;
    insertarFinal (lista1, &item); //Lo insertamos al final.

    item = 75;
    insertarFinal (lista1, &item); //Lo insertamos al final.

    imprimirLista (lista1); //Mostramos la lista.

    printf ("\n--------------------------------------------------------------\n");
    ///--------------------------------------------------------------

    ///2- Ordenamos la Lista1 y la mostramos.
    ///--------------------------------------------------------------
    printf ("\n2- ORDENAMOS LA LISTA1 Y LA MOSTRAMOS\n");
    printf ("--------------------------------------------------------------\n");

    ordenarLista (lista1); //Ordenamos.

    imprimirLista (lista1); //Mostramos.

    printf ("\n--------------------------------------------------------------\n");
    ///--------------------------------------------------------------

    ///3- DUPLICAMOS LA LISTA1 EN LA LISTA2 Y LA MOSTRAMOS
    ///--------------------------------------------------------------
    printf ("\n3- DUPLICAMOS LA LISTA1 EN LA LISTA 2 Y LA MOSTRAMOS\n");
    printf ("--------------------------------------------------------------\n");

    duplicarLista (lista1, lista2); //Duplicamos la lista.

    printf ("\n---LISTA DUPLICADA---\n");

    imprimirLista (lista2); //Mostramos la lista duplicada

    printf ("\n--------------------------------------------------------------\n");
    ///--------------------------------------------------------------

    ///4- BUSCAMOS UN ELEMENTO DETERMINADO EN LA LISTA
    ///--------------------------------------------------------------
    printf ("\n4- BUSCAMOS UN ITEM DE LA LISTA\n");
    printf ("--------------------------------------------------------------\n");

    item = 20; //Definimos el item a buscar.

    chequearBusqueda (lista1, &item); //Lo buscamos

    printf ("\n--------------------------------------------------------------\n");
    ///--------------------------------------------------------------

    ///5- OBTENEMOS ELEMENTOS DE LA LISTA
    ///--------------------------------------------------------------
    printf ("\n5- OBTENEMOS ELEMENTOS DE LA LISTA\n");
    printf ("--------------------------------------------------------------\n");

    imprimirLista(lista1);

    int itemGet;

    itemGet = *((int *) getElementoInicio(lista1));

    printf ("\n- PRIMER ELEMENTO DE LA LISTA: %d\n", itemGet);

    itemGet = *((int *) getElemento(lista1, 2));

    printf ("\n- TERCER ELEMENTO DE LA LISTA: %d\n", itemGet);

    itemGet = *((int *) getElementoFinal(lista1));

    printf ("\n- ULTIMO ELEMENTO DE LA LISTA: %d\n", itemGet);

    printf ("\n--------------------------------------------------------------\n");
    ///--------------------------------------------------------------

    ///6- ELIMINACION DE ITEMS DE LA LISTA
    ///--------------------------------------------------------------
    printf ("\n6- ELIMINAMOS ITEMS DE LA LISTA\n");
    printf ("--------------------------------------------------------------\n");

    int itemEliminado; //Definimos un item donde vamos a guardar los items que vamos eliminando.

    removerInicio (lista1, &itemEliminado);

    printf ("\n\n---ELIMINACION DE ITEM DEL INICIO---\n");

    printf ("\nSe elimino el item %d\n", itemEliminado);

    imprimirLista (lista1);

     printf ("\n\n---ELIMINACION DE ITEM EN LA POS ELEGIDA---\n");

    remover (lista1, &itemEliminado, 2);

    printf ("\nSe elimino el item %d\n", itemEliminado);

    imprimirLista (lista1);

    printf ("\n\n---ELIMINACION DE ITEM DEL FINAL---\n");

    removerFinal (lista1, &itemEliminado);

    printf ("\nSe elimino el item %d\n", itemEliminado);

    imprimirLista (lista1);

    printf ("\n--------------------------------------------------------------\n");
    ///--------------------------------------------------------------

    printf ("\n\n");

    ///7- UNA VEZ FINALIZADO EL TRABAJO, LIBERAMOS LA MEMORIA DE AMBAS LISTAS!!!
    ///--------------------------------------------------------------
    printf ("\n7- LIBERAMOS LA MEMORIA DE AMBAS LISTAS!\n");
    printf ("--------------------------------------------------------------\n");

    liberarLista (lista1);

    liberarLista (lista2);

    printf ("\n--------------------------------------------------------------\n");
    ///--------------------------------------------------------------

    return 0;
}
