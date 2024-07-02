#ifndef PAGINA_H
#define PAGINA_H

#include <iostream>
#include <vector>
#include <string>

class Pagina {
private:
    std::string* claves; // Arreglo de claves
    Pagina** hijos; // Arreglo de punteros a hijos
    int cuenta; // Número de claves en la página
    int orden; // Orden del árbol B
    bool hoja; // Verdadero si es una hoja

public:
    Pagina(int orden, bool hoja);

    bool esLleno();
    bool esSemiVacio();

    void insertarNoLleno(const std::string& clave);
    void dividirHijo(int i, Pagina* y);
    void imprimir();

    std::string* getClaves() { return claves; }
    Pagina** getHijos() { return hijos; }
    int getCuenta() { return cuenta; }
    void setCuenta(int cuenta) { this->cuenta = cuenta; }
    int getOrden() { return orden; }
    bool esHoja() { return hoja; }

    ~Pagina();
};

Pagina::Pagina(int orden, bool hoja) {
    this->orden = orden;
    this->hoja = hoja;
    claves = new std::string[2*orden-1];
    hijos = new Pagina*[2*orden];
    cuenta = 0;
}

bool Pagina::esLleno() {
    return cuenta == 2*orden-1;
}

bool Pagina::esSemiVacio() {
    return cuenta < orden-1;
}

void Pagina::insertarNoLleno(const std::string& clave) {
    int i = cuenta - 1;

    if (hoja) {
        while (i >= 0 && claves[i] > clave) {
            claves[i+1] = claves[i];
            i--;
        }
        claves[i+1] = clave;
        cuenta++;
    } else {
        while (i >= 0 && claves[i] > clave) {
            i--;
        }
        i++;
        if (hijos[i]->esLleno()) {
            dividirHijo(i, hijos[i]);
            if (claves[i] < clave) {
                i++;
            }
        }
        hijos[i]->insertarNoLleno(clave);
    }
}

void Pagina::dividirHijo(int i, Pagina* y) {
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

    for (int j = cuenta; j >= i+1; j--) {
        hijos[j+1] = hijos[j];
    }
    hijos[i+1] = z;

    for (int j = cuenta-1; j >= i; j--) {
        claves[j+1] = claves[j];
    }
    claves[i] = y->getClaves()[orden-1];

    cuenta++;
}

void Pagina::imprimir() {
    int i;
    for (i = 0; i < cuenta; i++) {
        if (!hoja) {
            hijos[i]->imprimir();
        }
        std::cout << " " << claves[i];
    }
    if (!hoja) {
        hijos[i]->imprimir();
    }
}

Pagina::~Pagina() {
    delete[] claves;
    delete[] hijos;
}

#endif
