#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "ListaSimple.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>  // para system()

class TablaHash {
private:
    int tamTabla;  
    std::vector<ListaSimple> tabla;

public:
    TablaHash(int tam = 18) : tamTabla(tam), tabla(tamTabla) {}

    int Clave(const std::string& valor) {
        int hash = static_cast<int>(valor[0]);  // Usa el código ASCII del primer carácter como base del hash
        for (int i = 1; i < valor.length(); i++) { 
            hash += (valor[i] - '0');  // Suma la diferencia entre cada carácter y '0' (opcionalmente ajusta esta parte)
        }
        return hash % tamTabla;  // Usa el módulo tamTabla para obtener el índice
    }

    void Insertar(const std::string& valor) {
        int indice = Clave(valor);
        tabla[indice].insertarInicio(valor); 
    }

    void imprimirTabla() {
        for (int i = 0; i < tamTabla; i++) {
            std::cout << i << " -> " << tabla[i].visualizarLista() << std::endl;
        }
    }

    void generarArchivoDot(const std::string& filename) {
        std::ofstream out(filename + ".dot");
        out << "digraph TablaHash {" << std::endl;
        out << "    rankdir=LR;" << std::endl;
        out << "    node [shape=record];" << std::endl;

        for (int i = tamTabla - 1; i >= 0; i--) {
            std::string listaContent = tabla[i].visualizarLista();
            if (listaContent == "Vacio") {
                out << "    " << i << " -> \"La posicion " << i << " esta vacio\";" << std::endl;
            } else {
                Nodo* actual = tabla[i].getPrimero();
                bool firstNode = true;
                while (actual != nullptr) {
                    if (firstNode) {
                        out << "    " << i << " -> " << actual->getDato() << ";" << std::endl;
                        firstNode = false;
                    }
                    if (actual->getSiguiente() != nullptr) {
                        out << "    " << actual->getDato() << " -> " << actual->getSiguiente()->getDato() << ";" << std::endl;
                    }
                    actual = actual->getSiguiente();
                }
            }
        }

        out << "}" << std::endl;
        out.close();

        // Comando para convertir el archivo DOT a PNG usando Graphviz
        std::string command = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
        system(command.c_str());
    }
};

#endif
