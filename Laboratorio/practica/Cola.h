
#include <fstream>
#include "NodoCola.h"
#include <iostream>
#include <cstdlib>
class Cola {
private:
    NodoCola* frente;
    NodoCola* fin;

public:
    Cola() : frente(nullptr), fin(nullptr) {}

    void insertar(NodoCola* nuevo) {
    if (fin == nullptr) {  // La cola está vacía
        frente = fin = nuevo;  // El nuevo nodo es ahora el frente y el fin
    } else {
        fin->siguiente = nuevo;  // Añadir nuevo al final
        fin = nuevo;  // Mover el fin a nuevo
    }
}


    bool estaVacia() const {
        return frente == nullptr;
    }

    NodoCola* eliminar() {
        if (estaVacia()) {
            std::cout << "La cola está vacía." << std::endl;
            return nullptr;
        }
        NodoCola* temp = frente;
        frente = frente->siguiente;
        if (frente == nullptr) {
            fin = nullptr;
        }
        temp->siguiente = nullptr; // Desconectar el nodo sacado de la cola
        return temp;
    }

    NodoCola* buscarPorPasaporte(std::string pasaporte) {
        NodoCola* actual = frente;
        while (actual != nullptr) {
            if (actual->numeroPasaporte == pasaporte) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    void imprimir() {
        std::ofstream archivo;
        archivo.open("Cola_Pasajeros.dot", std::ios::out);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo para escritura." << std::endl;
            return;
        }

        archivo << "digraph ColaPasajeros { rankdir=LR; node [shape=record];" << std::endl;

        NodoCola* actual = frente;
        while (actual != nullptr) {
            archivo << "\"" << actual << "\" [label=\"{" << actual->nombre << " | " << actual->numeroPasaporte << "}\"];\n";
            if (actual->siguiente != nullptr) {
                archivo << "\"" << actual << "\" -> \"" << actual->siguiente << "\";\n";
            }
            actual = actual->siguiente;
        }
        archivo << "}" << std::endl;
        archivo.close();

        system("dot -Tpng Cola_Pasajeros.dot -o Cola_Pasajeros.png");
        system("start Cola_Pasajeros.png");
    }
};
