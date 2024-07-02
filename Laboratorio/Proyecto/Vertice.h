#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
using namespace std;

class Vertice
{
private:
    string nombre;
    int numVertice;

public:
    Vertice() {}
    Vertice(string nombre, int n) : nombre(nombre), numVertice(n) {}

    string getNombre() {
        return this->nombre;
    }
    void setNombre(string nombre) {
        this->nombre = nombre;
    }
    bool esIgual(string nombre) {
        return this->nombre == nombre;
    }
    int getNumVertice() const {
        return numVertice;
    }
    void setNumVertice(int n) {
        numVertice = n;
    }
};

#endif
