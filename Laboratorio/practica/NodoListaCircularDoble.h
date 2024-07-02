#ifndef NODOLISTACIRCULARDOBLE_H
#define NODOLISTACIRCULARDOBLE_H

#include <string>
class NodoListaCircularDoble {
public:
    std::string vuelo;
    std::string numeroRegistro;
    std::string modelo;
    std::string fabricante;
    int anoFabricacion;
    int capacidad;
    int pesoMaxDespegue;
    std::string aerolinea;
    std::string estado;
    NodoListaCircularDoble* siguiente;
    NodoListaCircularDoble* anterior;

    NodoListaCircularDoble(std::string vl, std::string numReg, std::string mod, std::string fab, int anoFab,
                    int cap, int pesoMax, std::string aerol, std::string est)
    : vuelo(vl), numeroRegistro(numReg), modelo(mod), fabricante(fab), anoFabricacion(anoFab),
    capacidad(cap), pesoMaxDespegue(pesoMax), aerolinea(aerol), estado(est), siguiente(this), anterior(this) {}
};

#endif
