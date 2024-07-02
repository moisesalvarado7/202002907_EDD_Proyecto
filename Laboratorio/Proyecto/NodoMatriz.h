#ifndef NODOMATRIZ_H
#define NODOMATRIZ_H

#include <string>

using namespace std;

class NodoMatriz {
public:
    string dato;
    string fila;
    string columna;
    NodoMatriz* arriba;
    NodoMatriz* abajo;
    NodoMatriz* anterior;
    NodoMatriz* siguiente;

    NodoMatriz(string dato, string fila, string columna) {
        this->dato = dato;
        this->fila = fila;
        this->columna = columna;
        arriba = abajo = anterior = siguiente = nullptr;
    }
};

#endif // NODOMATRIZ_H

