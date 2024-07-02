#ifndef NODOLISTADOBLE_H
#define NODOLISTADOBLE_H

#include <string>

class NodoListaDoble {
public:
    std::string nombre;
    std::string nacionalidad;
    std::string numeroPasaporte;
    std::string vuelo;
    std::string asiento;
    std::string destino;
    std::string origen;
    int equipajeFacturado;
    NodoListaDoble* siguiente;
    NodoListaDoble* anterior;

    NodoListaDoble(std::string nom, std::string nac, std::string numPas, std::string vuel,
                std::string asien, std::string dest, std::string orig, int equiFact)
    : nombre(nom), nacionalidad(nac), numeroPasaporte(numPas), vuelo(vuel),
    asiento(asien), destino(dest), origen(orig), equipajeFacturado(equiFact),
    siguiente(nullptr), anterior(nullptr) {}
};

#endif // NODOLISTADOBLE_H
