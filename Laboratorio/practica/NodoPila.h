#ifndef NODOPILA_H
#define NODOPILA_H

#include <string>

class NodoPila {
public:
    int equipajeFacturado;
    std::string numeroPasaporte;
    NodoPila* siguiente;

    NodoPila(int equipaje, std::string numPasaporte)
    : equipajeFacturado(equipaje), numeroPasaporte(numPasaporte), siguiente(nullptr) {}
};

#endif // NODOPILA_H
