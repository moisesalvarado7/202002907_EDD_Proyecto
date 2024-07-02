#include <iostream>
#include <string>
#include <fstream>
#include "Nodo.h"
#include <iomanip> // Para formatear la salida
#include <vector>

using namespace std;

class Matriz {
private:
    Nodo* root;

public:
    Matriz();
    ~Matriz();
    void insertar(string dato, string fila, string columna);
    Nodo* buscarFila(string fila, Nodo* inicio);
    Nodo* buscarColumna(string columna, Nodo* inicio);
    Nodo* crearFila(string fila);
    Nodo* crearColumna(string columna);
    void imprimirMatriz();
    void generarGraphviz();


};

Matriz::Matriz() {
    root = new Nodo("Root", "root", "root"); // Nodo raíz con identificadores de tipo string
}

Nodo* Matriz::buscarFila(string fila, Nodo* inicio) {
    for (Nodo* aux = inicio; aux != nullptr; aux = aux->getAbajo()) {
        if (aux->getFila() == fila) {
            return aux;
        }
    }
    return nullptr;
}

Nodo* Matriz::buscarColumna(string columna, Nodo* inicio) {
    for (Nodo* aux = inicio; aux != nullptr; aux = aux->getSiguiente()) {
        if (aux->getColumna() == columna) {
            return aux;
        }
    }
    return nullptr;
}

Nodo* Matriz::crearFila(string fila) {
    Nodo* f = new Nodo("Fila", fila, "");
    Nodo* aux = root;
    while (aux->getAbajo() != nullptr) {
        aux = aux->getAbajo();
    }
    aux->setAbajo(f);
    f->setArriba(aux);
    return f;
}

Nodo* Matriz::crearColumna(string columna) {
    Nodo* c = new Nodo("Columna", "", columna);
    Nodo* aux = root;
    while (aux->getSiguiente() != nullptr) {
        aux = aux->getSiguiente();
    }
    aux->setSiguiente(c);
    c->setAnterior(aux);
    return c;
}

void Matriz::insertar(string dato, string fila, string columna) {
    Nodo* nodoDato = new Nodo(dato, fila, columna);
    Nodo* nodoFila = buscarFila(fila, root);
    Nodo* nodoColumna = buscarColumna(columna, root);


    nodoFila = buscarFila(fila, root);
    nodoColumna = buscarColumna(columna, root);

    //REVISAMOS SI EXISTEN LOS ENCABEZADOS
    /*if (nodoFila == nullptr)
    {
        nodoFila = crearFila(fila);
    }
    if (nodoColumna == nullptr)
    {
        nodoColumna = crearColumna(columna);
    }*/

   if (nodoFila == nullptr && nodoColumna == nullptr) //Caso 1
    {
        nodoFila = crearFila(fila);
        nodoColumna = crearColumna(columna);
    }
   else if (nodoFila != nullptr && nodoColumna == nullptr) //Caso 2
    {
        nodoColumna = crearColumna(columna);
    }
    else if (nodoFila == nullptr && nodoColumna != nullptr)
    {
        nodoFila = crearFila(fila);
    }

    
    //INSERTAR NODODATO EN LAS CABECERAS
    /*if (nodoFila->getSiguiente() == nullptr)
    {
        nodoFila->setSiguiente(nodoDato);
        nodoDato->setAnterior(nodoFila);
    }

    if (nodoColumna->getAbajo() == nullptr)
    {
        nodoColumna->setAbajo(nodoDato);
        nodoDato->setArriba(nodoColumna);
    }*/

   //Insertando nodoDato en la cabecera fila
    Nodo* auxFila = nodoFila;
    while (auxFila != nullptr)
    {
        if (auxFila->getSiguiente() == nullptr) //Encontre el último nodo (puede ser la misma cabecera)
        {
            //Hacemos los enlaces correspondientes
            auxFila->setSiguiente(nodoDato);
            nodoDato->setAnterior(auxFila);
            break;
        }
        auxFila = auxFila->getSiguiente();
    }

   //Insertando nodoDato en la cabecera columna
    Nodo* auxColumna = nodoColumna;
    while (auxColumna != nullptr)
    {
        if (auxColumna->getAbajo() == nullptr) //Encontre el último nodo (puede ser la misma cabecera)
        {
            //Hacemos los enlaces correspondientes
            auxColumna->setAbajo(nodoDato);
            nodoDato->setArriba(auxColumna);
            break;
        }
        auxColumna = auxColumna->getAbajo();  
    }
}

void Matriz::imprimirMatriz() {
    cout << "Matriz dispersa:" << endl;
    Nodo* filaAux = root;
    while (filaAux != nullptr) {
        Nodo* colAux = filaAux;
        while (colAux != nullptr) {
            cout << setw(15) << colAux->getDato() << " ";
            colAux = colAux->getSiguiente();
        }
        cout << endl;
        filaAux = filaAux->getAbajo();
    }
}

Matriz::~Matriz() {
    // Liberar memoria adecuadamente
}
