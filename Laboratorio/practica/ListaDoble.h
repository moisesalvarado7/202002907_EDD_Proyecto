#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "NodoListaDoble.h"
#include <iostream>

class ListaDoble {
private:
    NodoListaDoble* cabeza;
    NodoListaDoble* cola;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr) {}


    bool estaVacia() {
        return cabeza == nullptr;
    }


    void insertarOrdenado(NodoListaDoble* nuevo) {
        if (cabeza == nullptr) {  // Lista vacía
            cabeza = cola = nuevo;
        } else {
            NodoListaDoble* actual = cabeza;
            while (actual != nullptr && (actual->vuelo < nuevo->vuelo || 
                (actual->vuelo == nuevo->vuelo && actual->asiento < nuevo->asiento))) {
                actual = actual->siguiente;
            }
            if (actual == cabeza) {  // Insertar al principio
                nuevo->siguiente = cabeza;
                cabeza->anterior = nuevo;
                cabeza = nuevo;
            } else if (actual == nullptr) {  // Insertar al final
                cola->siguiente = nuevo;
                nuevo->anterior = cola;
                cola = nuevo;
            } else {  // Insertar en medio
                nuevo->siguiente = actual;
                nuevo->anterior = actual->anterior;
                actual->anterior->siguiente = nuevo;
                actual->anterior = nuevo;
            }
        }
    }

    void mostrar() {
        NodoListaDoble* actual = cabeza;
        while (actual != nullptr) {
            std::cout << "Pasaporte: " << actual->numeroPasaporte << ", Nombre: " << actual->nombre << std::endl;
            actual = actual->siguiente;
        }
    }
    
    NodoListaDoble* buscarPorPasaporte(std::string pasaporte) {
        NodoListaDoble* actual = cabeza;
        while (actual != nullptr) {
            if (actual->numeroPasaporte == pasaporte) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    void imprimir() {
    if (cabeza == nullptr) {
        std::cout << "La lista doblemente enlazada está vacía, no hay nada que imprimir." << std::endl;
        return;
    }
        std::ofstream archivo;
        archivo.open("ListaDoble_Pasajeros.dot", std::ios::out);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo para escritura." << std::endl;
            return;
        }

        archivo << "digraph ListaDoblePasajeros { rankdir=LR; node [shape=record];" << std::endl;

        NodoListaDoble* actual = cabeza;
        while (actual != nullptr) {
            archivo << "\"" << actual << "\" [label=\"{" << actual->vuelo << " | " << actual->asiento
                    << " | " << actual->nombre << " | " << actual->numeroPasaporte << "}\"];\n";
            if (actual->siguiente != nullptr) {
                archivo << "\"" << actual << "\" -> \"" << actual->siguiente << "\";\n";
                archivo << "\"" << actual->siguiente << "\" -> \"" << actual << "\" [dir=back];\n";
            }
            actual = actual->siguiente;
        }
        archivo << "}" << std::endl;
        archivo.close();

        system("dot -Tpng ListaDoble_Pasajeros.dot -o ListaDoble_Pasajeros.png");
        system("start ListaDoble_Pasajeros.png");
    }

};

#endif // LISTADOBLE_H
