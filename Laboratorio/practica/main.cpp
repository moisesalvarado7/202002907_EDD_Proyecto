
#include <fstream>
#include <iostream>
#include "json.hpp"
#include "Cola.h"
#include "Pila.h"
#include "ListaCircularDoble.h"
#include "ListaDoble.h"
#include <sstream>
#include <string>
using namespace std;
using json = nlohmann::json;

Cola colaPasajeros;
ListaCircularDoble listaDisponibles;
ListaCircularDoble listaMantenimiento;
extern Pila pilaEquipaje;
extern ListaDoble listaPasajeros;
extern Cola colaPasajeros;
Pila pilaEquipaje;
ListaDoble listaPasajeros;
Pila listaPila;

void cargarAviones() {
    std::ifstream archivo("aviones.json");
    json j;
    archivo >> j;

    for (auto& elem : j) {
        NodoListaCircularDoble* nuevo = new NodoListaCircularDoble(
            elem["vuelo"],
            elem["numero_de_registro"],
            elem["modelo"],
            elem["fabricante"],
            elem["ano_fabricacion"],
            elem["capacidad"],
            elem["peso_max_despegue"],
            elem["aerolinea"],
            elem["estado"]
        );

        if (nuevo->estado == "Disponible") {
            listaDisponibles.insertar(nuevo);
        } else if (nuevo->estado == "Mantenimiento") {
            listaMantenimiento.insertar(nuevo);
        }
    }
}

void cargarPasajeros() {
    std::ifstream archivo("pasajeros.json");
    json j;
    archivo >> j;

    for (auto& elem : j) {
        NodoCola* nuevo = new NodoCola(
            elem["nombre"],
            elem["nacionalidad"],
            elem["numero_de_pasaporte"],
            elem["vuelo"],
            elem["asiento"],
            elem["destino"],
            elem["origen"],
            elem["equipaje_facturado"]
        );
        colaPasajeros.insertar(nuevo);
    }
}

void cargarMovimientos() {
    std::ifstream archivo("equipaje.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo equipaje.txt" << std::endl;
        return;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        if (linea == "IngresoEquipajes;") {
            // Procesar el ingreso de equipajes
            while (!colaPasajeros.estaVacia()) {
                NodoCola* pasajero = colaPasajeros.eliminar();
                if (pasajero->equipajeFacturado > 0) {
                    pilaEquipaje.push(pasajero->equipajeFacturado, pasajero->numeroPasaporte);
                }

                NodoListaDoble* nuevoNodo = new NodoListaDoble(pasajero->nombre, pasajero->nacionalidad, pasajero->numeroPasaporte,
                                            pasajero->vuelo, pasajero->asiento, pasajero->destino, pasajero->origen,
                                            pasajero->equipajeFacturado);
                listaPasajeros.insertarOrdenado(nuevoNodo);
                delete pasajero;
            }
        } else {
            
        }
    }
    archivo.close();
}

void consultarPasajero() {
    std::string pasaporte;
    std::cout << endl;
    std::cout << "Ingrese el número de pasaporte del pasajero a consultar: ";
    
    std::cin >> pasaporte;
    NodoListaDoble* pasajero = listaPasajeros.buscarPorPasaporte(pasaporte);
    if (pasajero) {
        std::cout << endl;
        std::cout << "Información del Pasajero:" << std::endl;
        std::cout << "Nombre: " << pasajero->nombre << std::endl;
        std::cout << "Nacionalidad: " << pasajero->nacionalidad << std::endl;
        std::cout << "Número de Pasaporte: " << pasajero->numeroPasaporte << std::endl;
        std::cout << "Vuelo: " << pasajero->vuelo << std::endl;
        std::cout << "Asiento: " << pasajero->asiento << std::endl;
        std::cout << "Destino: " << pasajero->destino << std::endl;
        std::cout << "Origen: " << pasajero->origen << std::endl;
        std::cout << "Equipaje Facturado: " << pasajero->equipajeFacturado << std::endl;
    } else {
        std::cout << "No se encontró pasajero con el número de pasaporte proporcionado." << std::endl;
    }
}

void visualizarReportes() {
    int opcionReporte;
    do {
        cout << endl;
        cout << "----MENU DE REPORTES----" << endl;
        cout << "1. Lista de aviones disponibles" << endl;
        cout << "2. Lista de aviones en mantenimiento" << endl;
        cout << "3. Cola de registro" << endl;
        cout << "4. Pila de equipaje" << endl;
        cout << "5. Lista de pasajeros" << endl;
        cout << "6. Volver al menú principal" << endl;
        cout << endl;
        cout << "Seleccione un reporte para visualizar: ";
        cin >> opcionReporte;

        switch(opcionReporte) {
            case 1:
                listaDisponibles.mostrar("Aviones_Disponibles");
                break;
            case 2:
                listaMantenimiento.mostrar("Aviones_Mantenimiento");
                break;
            case 3:
                colaPasajeros.imprimir();

                break;
            case 4:
                listaPila.imprimir();
                break;
            case 5:
                listaPasajeros.imprimir();
                break;
            case 6:
                cout << "Volviendo al menú principal..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
        }
        cout << endl;
    } while(opcionReporte != 6);
}


int main() {
    int opcion;
    do {
        cout << "----------MENU---------" << endl;
        cout << "1. Carga de aviones" << endl;
        cout << "2. Carga de pasajeros" << endl;
        cout << "3. Carga de movimientos" << endl;
        cout << "4. Consultar pasajero" << endl;
        cout << "5. Visualizar reportes" << endl;
        cout << "6. Salir" << endl;
        cout << "" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarAviones();
                break;
            case 2:
                cargarPasajeros();
                break;
            case 3:
                cargarMovimientos();
                break;
            case 4:
                consultarPasajero();
                break;
            case 5:
                visualizarReportes();
                break;
            case 6:
                cout << "" << endl;
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "" << endl;
                cout << "Opción no válida. Intente nuevamente." << endl;
        }

        cout << endl;
    } while (opcion != 6);

    return 0;
}
