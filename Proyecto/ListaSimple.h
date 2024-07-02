#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include "NodoListaSimple.h"
#include <iostream>
#include <string>
#include <sstream>

class ListaSimple {
private:
    Nodo* primero; 

public:
    ListaSimple() : primero(nullptr) {}  

    bool estaVacia() const {
        return primero == nullptr;
    }

    Nodo* getPrimero() const {
        return primero;
    }

    void insertarInicio(const std::string& dato) {
        Nodo* nuevo = new Nodo(dato); 
        nuevo->setSiguiente(primero);  
        primero = nuevo; 
    }

    void insertarFinal(const std::string& dato) {
        Nodo* nuevo = new Nodo(dato);  
        if (estaVacia()) {
            primero = nuevo;
        } else {
            Nodo* actual = primero;
            while (actual->getSiguiente() != nullptr) {  
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevo);
        }
    }

    void eliminarInicio() {
        if (!estaVacia()) {
            Nodo* temp = primero; 
            primero = primero->getSiguiente();  
            delete temp;  
        }
    }

    std::string visualizarLista() const {
        if (!primero) {
            return "Vacio";
        }

        std::stringstream ss;
        Nodo* actual = primero;
        while (actual) {
            ss << actual->getDato();
            if (actual->getSiguiente()) {
                ss << " -> ";
            }
            actual = actual->getSiguiente();
        }
        return ss.str();
    }
};

#endif // LISTASIMPLE_H
