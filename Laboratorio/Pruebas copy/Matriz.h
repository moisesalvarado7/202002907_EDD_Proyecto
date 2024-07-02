#include <iostream>
#include <string>

#include <fstream>

using namespace std;
#include "Nodo.h"

class Matriz
{
private:
    /* data */
public:
    Nodo* root;
    Matriz(/* args */);
    Nodo* buscarFila(string fila, Nodo* inicio);
    Nodo* buscarColumna(string columna, Nodo* inicio);
    Nodo* crearFila(string fila);
    Nodo* crearColumna(string columna);
    void insertar(string dato, string fila, string columna);
    void mostrar();
    void generarDot(string nombreArchivo);
    void generarDot();
    ~Matriz();
};


Matriz::Matriz(/* args */)
{
    root = new Nodo("Root", "-1", "-1"); // "-1" y "-1" para encabezado root
}

Nodo* Matriz::buscarFila(string fila, Nodo* inicio)
{
    Nodo* aux = inicio; // inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getFila() == fila)
        {
            return aux; // Si se encuentra la cabecera fila, la retorno
        }
        aux = aux->getAbajo();
    }
    return nullptr; // Si no la encuentra quiere decir que no existe la cabecera fila
}

Nodo* Matriz::buscarColumna(string columna, Nodo* inicio)
{
    Nodo* aux = inicio; // inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getColumna() == columna)
        {
            return aux; // Si se encuentra la cabecera columna, la retorno
        }
        aux = aux->getSiguiente();
    }
    return nullptr; // Si no la encuentra quiere decir que no existe la cabecera columna
}

Nodo* Matriz::crearFila(string fila)
{
    Nodo* f = new Nodo("Fila", fila, "-1");
    Nodo* aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
    }
    aux->setAbajo(f);
    f->setArriba(aux);
    return f;
}

Nodo* Matriz::crearColumna(string columna)
{
    Nodo* c = new Nodo("Columna", "-1", columna);
    Nodo* aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
    }
    aux->setSiguiente(c);
    c->setAnterior(aux);
    return c;
}

void Matriz::insertar(string dato, string fila, string columna)
{
    Nodo* nodoDato = new Nodo(dato, fila, columna);
    Nodo* nodoFila; // Para saber en qué fila insertar
    Nodo* nodoColumna; // Para saber en qué columna insertar

    nodoFila = buscarFila(fila, root);
    nodoColumna = buscarColumna(columna, root);

    // REVISAMOS SI EXISTEN LOS ENCABEZADOS
    if (nodoFila == nullptr && nodoColumna == nullptr) // Caso 1
    {
        nodoFila = crearFila(fila);
        nodoColumna = crearColumna(columna);
    }
    else if (nodoFila != nullptr && nodoColumna == nullptr) // Caso 2
    {
        nodoColumna = crearColumna(columna);
    }
    else if (nodoFila == nullptr && nodoColumna != nullptr)
    {
        nodoFila = crearFila(fila);
    }

    // Insertando nodoDato en la cabecera fila
    Nodo* auxFila = nodoFila;
    while (auxFila != nullptr)
    {
        if (auxFila->getSiguiente() == nullptr) // Encontré el último nodo (puede ser la misma cabecera)
        {
            // Hacemos los enlaces correspondientes
            auxFila->setSiguiente(nodoDato);
            nodoDato->setAnterior(auxFila);
            break;
        }
        auxFila = auxFila->getSiguiente();
    }

    // Insertando nodoDato en la cabecera columna
    Nodo* auxColumna = nodoColumna;
    while (auxColumna != nullptr)
    {
        if (auxColumna->getAbajo() == nullptr) // Encontré el último nodo (puede ser la misma cabecera)
        {
            // Hacemos los enlaces correspondientes
            auxColumna->setAbajo(nodoDato);
            nodoDato->setArriba(auxColumna);
            break;
        }
        auxColumna = auxColumna->getAbajo();
    }
}

void Matriz::mostrar()
{
    Nodo* filaActual = root->getAbajo(); // Empezamos desde la primera fila

    while (filaActual != nullptr)
    {
        Nodo* columnaActual = filaActual->getSiguiente(); // Empezamos desde el primer nodo de la fila actual

        while (columnaActual != nullptr)
        {
            cout << "Dato: " << columnaActual->getDato() << " en (" << columnaActual->getFila() << ", " << columnaActual->getColumna() << ")" << endl;
            columnaActual = columnaActual->getSiguiente();
        }

        filaActual = filaActual->getAbajo();
    }
}


void Matriz::generarDot(string nombreArchivo)
{
    ofstream archivo(nombreArchivo);
    if (archivo.is_open())
    {
        archivo << "digraph G {" << endl;
        archivo << "    node [shape=box];" << endl;

        // Crear nodos y enlaces para las cabeceras
        archivo << "    /*------------Cabeceras Horizontales------------*/" << endl;
        archivo << "    n0 [label=\"root\" group=1];" << endl;

        Nodo* filaActual = root->getAbajo();
        int grupo = 2;
        while (filaActual != nullptr)
        {
            archivo << "    n" << grupo << " [label=\"" << filaActual->getFila() << "\" group=1];" << endl;
            filaActual = filaActual->getAbajo();
            grupo++;
        }

        Nodo* columnaActual = root->getSiguiente();
        grupo = 2;
        while (columnaActual != nullptr)
        {
            archivo << "    " << grupo << " [label=\"" << columnaActual->getColumna() << "\" group=" << grupo << "];" << endl;
            columnaActual = columnaActual->getSiguiente();
            grupo++;
        }

        // Crear nodos y enlaces para los datos
        archivo << "    /*------------Datos------------*/" << endl;
        filaActual = root->getAbajo();
        while (filaActual != nullptr)
        {
            columnaActual = filaActual->getSiguiente();
            while (columnaActual != nullptr)
            {
                archivo << "    " << filaActual->getFila() << "_" << columnaActual->getColumna() << " [label=\"" << columnaActual->getDato() << "\" group=" << columnaActual->getColumna() << "];" << endl;
                columnaActual = columnaActual->getSiguiente();
            }
            filaActual = filaActual->getAbajo();
        }

        // Crear relaciones horizontales
        archivo << "    /*------------Relaciones Horizontales------------*/" << endl;
        archivo << "    n0";
        columnaActual = root->getSiguiente();
        string reverseHorizontal = "";
        while (columnaActual != nullptr)
        {
            archivo << " -> " << columnaActual->getColumna();
            reverseHorizontal = " -> " + columnaActual->getColumna() + reverseHorizontal;
            columnaActual = columnaActual->getSiguiente();
        }
        archivo << ";" << endl;
        archivo << "    " << reverseHorizontal.substr(4) << " -> n0;" << endl;

        filaActual = root->getAbajo();
        while (filaActual != nullptr)
        {
            columnaActual = filaActual->getSiguiente();
            archivo << "    " << filaActual->getFila();
            string reverseRow = "";
            while (columnaActual != nullptr)
            {
                archivo << " -> " << filaActual->getFila() << "_" << columnaActual->getColumna();
                reverseRow = " -> " + filaActual->getFila() + "_" + columnaActual->getColumna() + reverseRow;
                columnaActual = columnaActual->getSiguiente();
            }
            archivo << ";" << endl;
            archivo << "    " << reverseRow.substr(4) << " -> " << filaActual->getFila() << ";" << endl;
            filaActual = filaActual->getAbajo();
        }

        // Crear relaciones verticales
        archivo << "    /*------------Relaciones Verticales------------*/" << endl;
        archivo << "    n0";
        filaActual = root->getAbajo();
        string reverseVertical = "";
        while (filaActual != nullptr)
        {
            archivo << " -> " << filaActual->getFila();
            reverseVertical = " -> " + filaActual->getFila() + reverseVertical;
            filaActual = filaActual->getAbajo();
        }
        archivo << ";" << endl;
        archivo << "    " << reverseVertical.substr(4) << " -> n0;" << endl;

        columnaActual = root->getSiguiente();
        while (columnaActual != nullptr)
        {
            filaActual = columnaActual->getAbajo();
            archivo << "    " << columnaActual->getColumna();
            string reverseColumn = "";
            while (filaActual != nullptr)
            {
                archivo << " -> " << filaActual->getFila() << "_" << columnaActual->getColumna();
                reverseColumn = " -> " + filaActual->getFila() + "_" + columnaActual->getColumna() + reverseColumn;
                filaActual = filaActual->getAbajo();
            }
            archivo << ";" << endl;
            archivo << "    " << reverseColumn.substr(4) << " -> " << columnaActual->getColumna() << ";" << endl;
            columnaActual = columnaActual->getSiguiente();
        }

        // Crear encuadre
        archivo << "    /*------------Encuadre------------*/" << endl;
        archivo << "    { rank=same; n0";
        columnaActual = root->getSiguiente();
        while (columnaActual != nullptr)
        {
            archivo << "; " << columnaActual->getColumna();
            columnaActual = columnaActual->getSiguiente();
        }
        archivo << " }" << endl;

        filaActual = root->getAbajo();
        while (filaActual != nullptr)
        {
            archivo << "    { rank=same; " << filaActual->getFila();
            columnaActual = filaActual->getSiguiente();
            while (columnaActual != nullptr)
            {
                archivo << "; " << filaActual->getFila() << "_" << columnaActual->getColumna();
                columnaActual = columnaActual->getSiguiente();
            }
            archivo << " }" << endl;
            filaActual = filaActual->getAbajo();
        }

        archivo << "}" << endl;
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
}

Matriz::~Matriz()
{
}
