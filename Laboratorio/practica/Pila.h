#ifndef PILA_H
#define PILA_H

#include "NodoPila.h"
#include <iostream>

class Pila {
private:
    NodoPila* tope;

public:
    Pila() : tope(nullptr) {}

    bool estaVacia() {
        return tope == nullptr;
    }


    void push(int equipaje, std::string numPasaporte) {
        NodoPila* nuevo = new NodoPila(equipaje, numPasaporte);
        nuevo->siguiente = tope;  
        tope = nuevo; 
    }


    void pop() {
        if (tope != nullptr) {
            NodoPila* temp = tope;
            tope = tope->siguiente;
            delete temp;
        }
    }

    void mostrar() {
        NodoPila* actual = tope;
        while (actual != nullptr) {
            std::cout << "Pasaporte: " << actual->numeroPasaporte << ", Equipaje: " << actual->equipajeFacturado << std::endl;
            actual = actual->siguiente;
        }
    }


    void imprimir() {
        if (estaVacia()) {
            std::cout << "La pila está vacía, no hay nada que imprimir." << std::endl;
            return;
        }
        std::ofstream archivo;
        archivo.open("Pila_Equipaje.dot", std::ios::out);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo para escritura." << std::endl;
            return;
        }

        archivo << "digraph PilaEquipaje { rankdir=TB; node [shape=record];" << std::endl;

        NodoPila* actual = tope;
        while (actual != nullptr) {
            archivo << "\"" << actual << "\" [label=\"{Pasaporte: " << actual->numeroPasaporte
                    << " | Equipaje: " << actual->equipajeFacturado << "}\"];\n";
            if (actual->siguiente != nullptr) {
                archivo << "\"" << actual << "\" -> \"" << actual->siguiente << "\";\n";
            }
            actual = actual->siguiente;
        }
        archivo << "}" << std::endl;
        archivo.close();

        system("dot -Tpng Pila_Equipaje.dot -o Pila_Equipaje.png");
        system("start Pila_Equipaje.png");
    }


};

#endif // PILA_H
