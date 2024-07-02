#include <iostream>
#include <string>
using namespace std;

class Nodo
{
private:
    /* data */
    string dato;
    string fila, columna;
    Nodo* anterior;
    Nodo* siguiente;
    Nodo* arriba;
    Nodo* abajo;
    
public:
    Nodo(/* args */);
    Nodo(string dato, string fila, string columna);

    string getDato();
    void setDato(string dato);
    string getFila();
    void setFila(string fila);
    string getColumna();
    void setColumna(string columna);

    Nodo* getAnterior();
    void setAnterior(Nodo* anterior);
    Nodo* getSiguiente();
    void setSiguiente(Nodo* siguiente);
    Nodo* getArriba();
    void setArriba(Nodo* arriba);
    Nodo* getAbajo();
    void setAbajo(Nodo* abajo);
    ~Nodo();
};

Nodo::Nodo(/* args */)
{

}

Nodo::Nodo(string dato, string fila, string columna)
{
    this->dato = dato;
    this->fila = fila;
    this->columna = columna;
    anterior = siguiente = arriba = abajo = nullptr;
}

Nodo* Nodo::getAnterior()
{
    return anterior;
}

void Nodo::setAnterior(Nodo* anterior)
{
    this->anterior = anterior;
}


Nodo* Nodo::getSiguiente()
{
    return siguiente;
}

void Nodo::setSiguiente(Nodo* siguiente)
{
    this->siguiente = siguiente;
}



Nodo* Nodo::getArriba()
{
    return arriba;
}

void Nodo::setArriba(Nodo* arriba)
{
    this->arriba = arriba;
}


Nodo* Nodo::getAbajo()
{
    return abajo;
}

void Nodo::setAbajo(Nodo* abajo)
{
    this->abajo = abajo;
}

string Nodo::getFila(){
    return fila;
}

void Nodo::setFila(string fila)
{
    this->fila = fila;
}

string Nodo::getColumna()
{
    return columna;
}

void Nodo::setColumna(string columna)
{
    this->columna = columna;
}

string Nodo::getDato(){
    return dato;
}

void Nodo::setDato(string dato)
{
    this->dato = dato;
}

Nodo::~Nodo()
{
}
