#include <iostream>
#include <string.h>
#include "Nodo.h"
using namespace std;

class Matrizqwe
{
private:
    /* data */
public:
    Nodo* root;
    Matriz(/* args */);
    Nodo* buscarFila(int fila, Nodo* inicio);
    Nodo* buscarColumna(int columna, Nodo* inicio);
    Nodo* crearFila(int fila);
    Nodo* crearColumna(int columna);
    void insertar(string dato, int fila, int columna);
    ~Matriz();
};

Matriz::Matriz(/* args */)
{
    root=new Nodo("Root", -1, -1); //-1 y -1 encabezado del root para la fila y columna
}
// Para fila
Nodo* Matriz::buscarFila(int fila, Nodo* inicio)
{
    Nodo* aux = inicio; //Inicio puede ser el root
    while (aux!=nullptr)
    {
        if (aux->getFila()==fila)
        {
            return aux; //Si se encuentra la cabecera fila la retorna
        }
        aux=aux->getAbajo();
    }
    return nullptr; // Si no lo encuentra, no existe la cabecera fila
    
}
// Para columna
Nodo* Matriz::buscarColumna(int columna, Nodo* inicio)
{
    Nodo* aux = inicio; //Inicio puede ser el root
    while (aux!=nullptr)
    {
        if (aux->getColumna()==columna)
        {
            return aux; //Si se encuentra la cabecera fila la retorna
        }
        aux=aux->getSiguiente();
    }
    return nullptr; // Si no lo encuentra, no existe la cabecera columna
    
}

Nodo* Matriz::crearFila(int fila)
{
    Nodo* f = new Nodo("Fila", fila, -1);
    Nodo* aux=root;
    while (aux->getAbajo()!=nullptr)
    {
        aux=aux->getAbajo();
    }
    aux->setAbajo(f);
    f->setArriba(aux);
    return f;
}

Nodo* Matriz::crearColumna(int columna)
{
    Nodo* c = new Nodo("Columna", -1, columna);
    Nodo* aux=root;
    while (aux->getSiguiente()!=nullptr)
    {
        aux=aux->getSiguiente();
    }
    aux->setSiguiente(c);
    c->setAnterior(aux);
    return c;
}

void Matriz::insertar(string dato, int fila, int columna)
{
    Nodo* nodoDato = new Nodo(dato, fila, columna);
    Nodo* nodoFila; //Pra saber en que fila insertar
    Nodo* nodoColumna; //Pra saber en que columna insertar

    nodoFila=buscarFila(fila, root);
    nodoColumna=buscarColumna(columna, root);
//REVISAMOS SI EXISTEN LOS ENCABEZADOS
    if (nodoFila==nullptr)
    {
        nodoFila=crearFila(fila);
    }
    if (nodoColumna==nullptr)
    {
        nodoColumna=crearColumna(columna);
    }
    
    // insertar el nodo dato en las cabeceras
    if (nodoFila->getSiguiente()==nullptr)
    {
        nodoFila->setSiguiente(nodoDato);
        nodoDato->setAnterior(nodoFila);
    }
    if (nodoColumna->getAbajo()==nullptr)
    {
        nodoColumna->setAbajo(nodoDato);
        nodoDato->setArriba(nodoColumna);
    }    
}

Matriz::~Matriz()
{
}
