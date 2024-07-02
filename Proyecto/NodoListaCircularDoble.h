#ifndef NODOLISTACIRCULARDOBLE_H
#define NODOLISTACIRCULARDOBLE_H

#include <string>
class NodoListaCircularDoble {
public:
    std::string vuelo;
    std::string numeroRegistro;
    std::string modelo;
    int capacidad;
    std::string aerolinea;
    std::string destino;
    std::string estado;

    NodoListaCircularDoble* siguiente;
    NodoListaCircularDoble* anterior;

    NodoListaCircularDoble(std::string vl, std::string numReg, std::string mod,
                    int cap,std::string aerol,std::string dest, std::string est)
    : vuelo(vl), numeroRegistro(numReg), modelo(mod),
    capacidad(cap), aerolinea(aerol),destino(dest), estado(est), siguiente(this), anterior(this) {}

    NodoListaCircularDoble(std::string numReg)
    : vuelo(""), numeroRegistro(numReg), modelo(""),
    capacidad(0), aerolinea(""), destino(""), estado("Mantenimiento"),
    siguiente(this), anterior(this) {}

};

#endif
