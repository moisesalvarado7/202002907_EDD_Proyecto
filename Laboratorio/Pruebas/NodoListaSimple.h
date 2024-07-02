#ifndef NODOLISTASIMPLE_H
#define NODOLISTASIMPLE_H

#include <iostream>
#include <string>

class Nodo {
private:
    std::string dato; 
    Nodo* siguiente;

public:
    Nodo(std::string dato) : dato(dato), siguiente(nullptr) {} 

    Nodo* getSiguiente() const {
        return siguiente;
    }

    void setSiguiente(Nodo* sig) {
        siguiente = sig;
    }

    std::string getDato() const {
        return dato;
    }

    void setDato(std::string dat) {
        dato = dat;
    }

    ~Nodo() {}
};

#endif 
