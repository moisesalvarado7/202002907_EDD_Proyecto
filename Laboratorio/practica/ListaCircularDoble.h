#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include "NodoListaCircularDoble.h"
#include <iostream>
#include <fstream>

class ListaCircularDoble {
private:
    NodoListaCircularDoble* cabeza;
    int count;

public:
    ListaCircularDoble() : cabeza(nullptr), count(0) {}

    void insertar(NodoListaCircularDoble* nuevo) {
        if (cabeza == nullptr) {
            cabeza = nuevo;
            nuevo->siguiente = nuevo;
            nuevo->anterior = nuevo;
        } else {
            NodoListaCircularDoble* ultimo = cabeza->anterior;
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
        }
        count++;
    }

    void mostrar(std::string titulo) {
        std::ofstream archivo;
        archivo.open(titulo + ".dot", std::ios::out);
        archivo << "digraph G { rankdir=LR; node [shape=record];" << std::endl;

        NodoListaCircularDoble* actual = cabeza;
        if (actual != nullptr) {
            do {
                archivo << "\"" << actual << "\" [label=\"{" << actual->numeroRegistro << " | " << actual->estado << "}\"];\n";
                archivo << "\"" << actual->anterior << "\" -> \"" << actual << "\" [dir=back];\n";
                archivo << "\"" << actual << "\" -> \"" << actual->siguiente << "\";\n";
                actual = actual->siguiente;
            } while (actual != cabeza);
        }

        archivo << "}" << std::endl;
        archivo.close();

        system(("dot -Tpng " + titulo + ".dot -o " + titulo + ".png").c_str());
        system(("start " + titulo + ".png").c_str());  // Adjust as necessary for different OS
    }
};

#endif // LISTACIRCULARDOBLE_H
