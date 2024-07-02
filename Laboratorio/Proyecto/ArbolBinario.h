#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include "NodoArbolBinario.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class ArbolBinario {
private:

    NodoArbolBinario *raiz;

    void insertarRec(NodoArbolBinario *&nodo, NodoArbolBinario *nuevoNodo) {
        if (!nodo) {
            nodo = nuevoNodo;
        } else if (nuevoNodo->horas_de_vuelo < nodo->horas_de_vuelo) {
            insertarRec(nodo->izquierda, nuevoNodo);
        } else {
            insertarRec(nodo->derecha, nuevoNodo);
        }
    }

    NodoArbolBinario* eliminarRec(NodoArbolBinario *nodo, int horas_de_vuelo) {
        if (!nodo) return nodo;

        if (horas_de_vuelo < nodo->horas_de_vuelo) {
            nodo->izquierda = eliminarRec(nodo->izquierda, horas_de_vuelo);
        } else if (horas_de_vuelo > nodo->horas_de_vuelo) {
            nodo->derecha = eliminarRec(nodo->derecha, horas_de_vuelo);
        } else {
            if (!nodo->izquierda) {
                NodoArbolBinario *temp = nodo->derecha;
                delete nodo;
                return temp;
            } else if (!nodo->derecha) {
                NodoArbolBinario *temp = nodo->izquierda;
                delete nodo;
                return temp;
            }
            NodoArbolBinario *temp = minValorNodo(nodo->derecha);
            nodo->horas_de_vuelo = temp->horas_de_vuelo;
            nodo->nombre = temp->nombre;
            nodo->nacionalidad = temp->nacionalidad;
            nodo->numero_de_id = temp->numero_de_id;
            nodo->vuelo = temp->vuelo;
            nodo->tipo_de_licencia = temp->tipo_de_licencia;
            nodo->derecha = eliminarRec(nodo->derecha, temp->horas_de_vuelo);
        }
        return nodo;
    }

    NodoArbolBinario* minValorNodo(NodoArbolBinario *nodo) {
        NodoArbolBinario *actual = nodo;
        while (actual && actual->izquierda != nullptr)
            actual = actual->izquierda;
        return actual;
    }

    NodoArbolBinario* buscarPorIDRec(NodoArbolBinario *nodo, const std::string &id) {
        if (!nodo || nodo->numero_de_id == id) {
            return nodo;
        }
        if (id < nodo->numero_de_id) {
            return buscarPorIDRec(nodo->izquierda, id);
        } else {
            return buscarPorIDRec(nodo->derecha, id);
        }
    }

    void imprimirPreorden(NodoArbolBinario *nodo) {
        if (nodo) {
            std::cout << nodo->nombre << " - " << nodo->horas_de_vuelo << " horas\n";
            imprimirPreorden(nodo->izquierda);
            imprimirPreorden(nodo->derecha);
        }
    }

    void imprimirInorden(NodoArbolBinario *nodo) {
        if (nodo) {
            imprimirInorden(nodo->izquierda);
            std::cout << nodo->nombre << " - " << nodo->horas_de_vuelo << " horas\n";
            imprimirInorden(nodo->derecha);
        }
    }

    void imprimirPostorden(NodoArbolBinario *nodo) {
        if (nodo) {
            imprimirPostorden(nodo->izquierda);
            imprimirPostorden(nodo->derecha);
            std::cout << nodo->nombre << " - " << nodo->horas_de_vuelo << " horas\n";
        }
    }

    void imprimirNodo(NodoArbolBinario *nodo, std::ofstream &archivo) {
        if (!nodo) return;

        archivo << "\"" << nodo->numero_de_id << "\" [label=\"" << nodo->nombre << "\\n" << nodo->horas_de_vuelo << " horas\"];\n";

        if (nodo->izquierda) {
            archivo << "\"" << nodo->numero_de_id << "\" -> \"" << nodo->izquierda->numero_de_id << "\";\n";
            imprimirNodo(nodo->izquierda, archivo);
        }
        if (nodo->derecha) {
            archivo << "\"" << nodo->numero_de_id << "\" -> \"" << nodo->derecha->numero_de_id << "\";\n";
            imprimirNodo(nodo->derecha, archivo);
        }
    }

public:

    ArbolBinario() : raiz(nullptr) {}

    void insertar(std::string nombre, std::string nacionalidad, std::string numero_de_id,
                std::string vuelo, int horas_de_vuelo, std::string tipo_de_licencia) {
        NodoArbolBinario *nuevoNodo = new NodoArbolBinario(nombre, nacionalidad, numero_de_id, vuelo, horas_de_vuelo, tipo_de_licencia);
        insertarRec(raiz, nuevoNodo);
    }

    bool estaVacio() const {
        return raiz == nullptr;
    }

    void eliminar(int horas_de_vuelo) {
        raiz = eliminarRec(raiz, horas_de_vuelo);
    }

    void eliminarPorID(const std::string &id) {
        NodoArbolBinario *nodo = buscarPorID(id);
        if (nodo) {
            eliminar(nodo->horas_de_vuelo);
        } else {
            std::cout << "Nodo con ID " << id << " no encontrado." << std::endl;
        }
    }

    NodoArbolBinario* buscarPorID(const std::string &id) {
        return buscarPorIDRec(raiz, id);
    }

    void generarReporte() {
        if (estaVacio()) {
            std::cout << "El árbol está vacío." << std::endl;
        } else {
            std::ofstream archivo("Arbol_Binario.dot", std::ios::out);
            archivo << "digraph G { " << std::endl;
            imprimirNodo(raiz, archivo);
            archivo << " }";
            archivo.close();
            system("dot -Tpng Arbol_Binario.dot -o Arbol_Binario.png");
            system("start Arbol_Binario.png");
        }
    }

    void preorden() {
        imprimirPreorden(raiz);
    }

    void inorden() {
        imprimirInorden(raiz);
    }

    void postorden() {
        imprimirPostorden(raiz);
    }
};

#endif