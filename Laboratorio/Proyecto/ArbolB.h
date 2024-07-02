#ifndef ARBOLB_H
#define ARBOLB_H

#include "Pagina.h"
#include <fstream>
#include <functional>
#include <string>
#include <sstream>

class ArbolB {
private:
    Pagina* raiz;
    int orden;

public:
    ArbolB(int orden);
    void insertar(const std::string& clave);
    void imprimir();
    void generarReporte();

    bool estaVacio() {
        return raiz == nullptr;
    }

    void dividirHijo(Pagina* x, int i, Pagina* y);
};

ArbolB::ArbolB(int orden) {
    this->orden = orden;
    raiz = nullptr;
}

void ArbolB::insertar(const std::string& clave) {
    if (raiz == nullptr) {
        raiz = new Pagina(orden, true);
        raiz->getClaves()[0] = clave;
        raiz->setCuenta(1);
    } else {
        if (raiz->esLleno()) {
            Pagina* s = new Pagina(orden, false);
            s->getHijos()[0] = raiz;
            dividirHijo(s, 0, raiz);
            int i = 0;
            if (s->getClaves()[0] < clave) {
                i++;
            }
            s->getHijos()[i]->insertarNoLleno(clave);
            raiz = s;
        } else {
            raiz->insertarNoLleno(clave);
        }
    }
}

void ArbolB::dividirHijo(Pagina* x, int i, Pagina* y) {
    Pagina* z = new Pagina(y->getOrden(), y->esHoja());
    z->setCuenta(orden - 1);

    for (int j = 0; j < orden-1; j++) {
        z->getClaves()[j] = y->getClaves()[j+orden];
    }

    if (!y->esHoja()) {
        for (int j = 0; j < orden; j++) {
            z->getHijos()[j] = y->getHijos()[j+orden];
        }
    }

    y->setCuenta(orden - 1);

    for (int j = x->getCuenta(); j >= i+1; j--) {
        x->getHijos()[j+1] = x->getHijos()[j];
    }
    x->getHijos()[i+1] = z;

    for (int j = x->getCuenta()-1; j >= i; j--) {
        x->getClaves()[j+1] = x->getClaves()[j];
    }
    x->getClaves()[i] = y->getClaves()[orden-1];

    x->setCuenta(x->getCuenta() + 1);
}

void ArbolB::imprimir() {
    if (raiz != nullptr) {
        raiz->imprimir();
    }
}

void ArbolB::generarReporte() {
    if (raiz == nullptr) return;

    std::ofstream archivo("arbol_b.dot");
    archivo << "digraph ArbolB {\n";
    archivo << "node [shape=record];\n";
    std::function<void(Pagina*, std::ofstream&, int&)> imprimirDot = [&](Pagina* nodo, std::ofstream& archivo, int& id) {
        std::stringstream ss;
        ss << "node" << id;
        std::string nodoId = ss.str();
        archivo << nodoId << " [label=\"";
        for (int i = 0; i < nodo->getCuenta(); i++) {
            if (i > 0) {
                archivo << "|";
            }
            archivo << "<f" << i << "> " << nodo->getClaves()[i];
        }
        archivo << "\"];\n";

        int nodoActualId = id;
        for (int i = 0; i <= nodo->getCuenta(); i++) {
            if (nodo->getHijos()[i] != nullptr) {
                id++;
                ss.str("");
                ss << "node" << id;
                std::string hijoId = ss.str();
                archivo << nodoId << ":f" << i << " -> " << hijoId << ";\n";
                imprimirDot(nodo->getHijos()[i], archivo, id);
            }
        }
    };

    int id = 0;
    imprimirDot(raiz, archivo, id);
    archivo << "}\n";
    archivo.close();
    system("dot -Tpng arbol_b.dot -o arbol_b.png");
    system("start arbol_b.png");
}

#endif
