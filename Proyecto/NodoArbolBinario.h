#ifndef NODOARBOLBINARIO_H
#define NODOARBOLBINARIO_H

#include <string>

class NodoArbolBinario {
public:
    std::string nombre;
    std::string nacionalidad;
    std::string numero_de_id;
    std::string vuelo;
    int horas_de_vuelo;
    std::string tipo_de_licencia;

    NodoArbolBinario *izquierda;
    NodoArbolBinario *derecha;

    NodoArbolBinario(std::string nombre, std::string nacionalidad, std::string numero_de_id,
                    std::string vuelo, int horas_de_vuelo, std::string tipo_de_licencia) :
                    nombre(nombre), nacionalidad(nacionalidad), numero_de_id(numero_de_id),
                    vuelo(vuelo), horas_de_vuelo(horas_de_vuelo), tipo_de_licencia(tipo_de_licencia),
                    izquierda(nullptr), derecha(nullptr) {}
};

#endif
