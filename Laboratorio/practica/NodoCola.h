#ifndef NODOCOLA_H
#define NODOCOLA_H

#include <string>

class NodoCola {
public:
    std::string nombre;
    std::string nacionalidad;
    std::string numeroPasaporte;
    std::string vuelo;
    std::string asiento;
    std::string destino;
    std::string origen;
    int equipajeFacturado;
    NodoCola* siguiente;

    NodoCola(std::string nom, std::string nac, std::string numPas, std::string vuel,
            std::string asien, std::string dest, std::string orig, int equiFact)
    : nombre(nom), nacionalidad(nac), numeroPasaporte(numPas), vuelo(vuel),
    asiento(asien), destino(dest), origen(orig), equipajeFacturado(equiFact), siguiente(nullptr) {}
};

#endif 
