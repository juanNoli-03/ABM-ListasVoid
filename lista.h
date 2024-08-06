#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

///ENUMS (ESTADOS)

enum ESTADOS {OK = 1, ESTRUCTURA_NO_INICIALIZADA, ESTRUCTURA_VACIA, INDICE_INVALIDO, TRUE = 1, FALSE = 0};

///CREAMOS LOS TIPOS DE DATO DE LA LISTA Y EL NODO
///---------------------------------------------------------------------------------------
struct ListaE;

typedef struct ListaE * ListaP;

struct NodoE;

typedef struct NodoE * NodoP;
///---------------------------------------------------------------------------------------

///FUNCIONES (PRIMITIVAS)
///---------------------------------------------------------------------------------------

///1- Construccion de la lista
ListaP crearlista (int tamDato); //Recibe el "sizeof (dato)" para determinar que tipo de dato vamos a alojar en nuestra lista

///2- Construccion del nodo
NodoP crearNodo (ListaP lista, NodoP proximo, void * item); //Dato del tipo void ya que no sabemos de que tipo va a ser ese dato. El puntero apunta a cualquier dato.

///3- Inserccion de nodos (inicio - pos - final)
int insertarInicio (ListaP lista, void * item);
int insertar (ListaP lista, void * item, int pos);
int insertarFinal (ListaP lista, void * item);

///4- Remover nodos (inicio - pos - final)
int removerInicio (ListaP lista, void * itemEliminado);
int remover (ListaP lista, void * itemEliminado, int pos);
int removerFinal (ListaP lista, void * itemEliminado);

///5- Getters
void * getElementoInicio (ListaP lista);
void * getElementoFinal (ListaP lista);
void * getElemento (ListaP lista, int pos);
int getSizeLista (ListaP lista, int * tam);

///6- Setters
void setElemento (ListaP lista, void * item, int pos);

///7- Duplicar Lista
void duplicarLista (ListaP lista1, ListaP lista2);

///8- Funciones Auxiliares
int estaVacia (ListaP lista);
void liberarLista (ListaP lista);
///---------------------------------------------------------------------------------------


#endif // LISTA_H_INCLUDED
