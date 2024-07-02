#include <fstream>
#include <iostream>
#include "json.hpp"
#include "ListaCircularDoble.h"
#include <sstream>
#include <string>
#include "ArbolBinario.h"
#include "TablaHash.h"
#include "ListaSimple.h"
#include "Grafo.h"
#include "Vertice.h"
#include "ArbolB.h"
#include "Matriz.h"


using namespace std;

ArbolBinario arbol;
ListaCircularDoble listaMantenimiento;
TablaHash tablaPilotos;
Matriz miMatriz;
Grafo grafo(100);
ArbolB arbolB(5);

using json = nlohmann::json;

void cargarAviones() {
    std::ifstream archivo("aviones.json");
    json j;
    archivo >> j;

    for (auto& elem : j) {
        if (elem["estado"] == "Mantenimiento") {
            NodoListaCircularDoble* nuevo = new NodoListaCircularDoble(
                elem["vuelo"],
                elem["numero_de_registro"],
                elem["modelo"],
                elem["capacidad"],
                elem["aerolinea"],
                elem["ciudad_destino"],
                elem["estado"]
            );
            listaMantenimiento.insertar(nuevo);
        }
    }

    for (auto& elem : j) {
        if (elem["estado"] == "Disponible") {
            std::string numeroDeRegistro = elem["numero_de_registro"].get<std::string>();
            arbolB.insertar(numeroDeRegistro);
        }
    }

    std::cout << "Aviones cargados con éxito." << std::endl;
}



void cargarPilotos() {
    std::ifstream archivo("pilotos.json");
    json pilotos;
    archivo >> pilotos;

    for (auto& piloto : pilotos) {
        arbol.insertar(piloto["nombre"], piloto["nacionalidad"], piloto["numero_de_id"],
                    piloto["vuelo"], piloto["horas_de_vuelo"], piloto["tipo_de_licencia"]);
        
    }
    for (auto& piloto : pilotos) {
        string id = piloto["numero_de_id"];
        tablaPilotos.Insertar(id); 
        
    }


    std::cout << "Pilotos cargados con éxito." << std::endl;
}

void cargarDatos() {
    std::ifstream archivoAviones("aviones.json");
    std::ifstream archivoPilotos("pilotos.json");

    json aviones, pilotos;
    archivoAviones >> aviones;
    archivoPilotos >> pilotos;

    // Inserción en la matriz dispersa desde aviones.json y pilotos.json
    for (auto& avion : aviones) {
        std::string vuelo = avion["vuelo"].get<std::string>();
        std::string ciudadDestino = avion["ciudad_destino"].get<std::string>();
        std::string numeroDeId = "";

        // Buscar el número de ID del piloto correspondiente al vuelo
        for (auto& piloto : pilotos) {
            if (piloto["vuelo"].get<std::string>() == vuelo) {
                numeroDeId = piloto["numero_de_id"].get<std::string>();
                break;
            }
        }

        miMatriz.insertar(numeroDeId, vuelo, ciudadDestino);  // Inserta vuelo, ciudad destino y número de ID del piloto
    }
}

void cargarRutas() {
    std::ifstream archivo("rutas.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de rutas." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        string origen, destino, distanciaStr;

        getline(ss, origen, '/');
        getline(ss, destino, '/');
        getline(ss, distanciaStr, ';');

        int distancia = stoi(distanciaStr);

        grafo.nuevoVertice(origen);
        grafo.nuevoVertice(destino);
        grafo.nuevoArco(origen, destino, distancia);
    }

    archivo.close();
    std::cout << "" << std::endl;
    std::cout << "Rutas cargadas con éxito." << std::endl;
}

void cargarMovimientos() {
    ifstream archivo("movimientos.txt");
    string linea;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de movimientos." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        if (linea.back() == ';') linea.pop_back();
        stringstream ss(linea);
        string comando, estado, dato;

        getline(ss, comando, '(');
        getline(ss, estado, ')');

        if (comando == "Ingreso") {
            // Crear un nuevo nodo y añadirlo a la lista
            NodoListaCircularDoble* nuevo = new NodoListaCircularDoble(estado);
            listaMantenimiento.insertar(nuevo);
        } else if (comando == "Salida") {
            // Eliminar el nodo de la lista
            listaMantenimiento.eliminar(estado);
        } else if (comando == "DarDeBaja") {
            // Eliminar el dato de la matriz dispersa
            string vuelo, ciudad;
            bool encontrado = false;

            NodoMatriz* filaActual = miMatriz.root->abajo;
            while (filaActual != nullptr && !encontrado) {
                NodoMatriz* columnaActual = filaActual->siguiente;
                while (columnaActual != nullptr) {
                    if (columnaActual->dato == estado) {
                        vuelo = filaActual->fila;
                        ciudad = columnaActual->columna;
                        encontrado = true;
                        break;
                    }
                    columnaActual = columnaActual->siguiente;
                }
                filaActual = filaActual->abajo;
            }

            if (encontrado) {
                miMatriz.eliminar(vuelo, ciudad);
            } else {
                cout << "Dato no encontrado en la matriz dispersa." << endl;
            }
            arbol.eliminarPorID(estado);
        }
    }
    archivo.close();
    cout << "" << endl;
    cout << "Movimientos cargados con éxito." << endl;
}



void consultarHora() {
    int tipoRecorrido;
    cout << "" << endl;
    cout << "Seleccione el tipo de recorrido para visualizar las horas de vuelo:" << endl;
    cout << "" << endl;
    cout << "1. Preorden" << endl;
    cout << "2. Inorden" << endl;
    cout << "3. Postorden" << endl;
    cout << "Ingrese su elección: ";
    cin >> tipoRecorrido;

    switch(tipoRecorrido) {
        case 1:
            cout << "" << endl;
            arbol.preorden();
            break;
        case 2:
            cout << "" << endl;
            arbol.inorden();
            break;
        case 3:
            cout << "" << endl;
            arbol.postorden();
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
    }
}

void recomendarRuta() {
    grafo.recomendarRuta();
}


void visualizarReportes() {
    int opcionReporte;
    do {
        cout << "" << endl;
        cout << "--------MENU DE REPORTES--------" << endl;
        cout << "1. Arbol B con aviones disponibles" << endl;
        cout << "2. Lista de aviones en mantenimiento" << endl;
        cout << "3. Árbol binario de busqueda con las horas de vuelo de cada piloto" << endl;
        cout << "4. Tabla hash de pilotos" << endl;
        cout << "5. Grafo dirigido con las rutas" << endl;
        cout << "6. Matriz dispersa de vuelos y ciudades" << endl;
        cout << "7. Volver al menú principal" << endl;
        cout << endl;
        cout << "Seleccione un reporte para visualizar: ";
        cin >> opcionReporte;

        switch(opcionReporte) {
            case 1:
                arbolB.generarReporte();// Logica para mostrar reporte del arbol B
                break;
            case 2:
                listaMantenimiento.mostrar("Aviones_Mantenimiento");
                break;
            case 3:
                arbol.generarReporte();
                break;
            case 4:
                //tablaPilotos.imprimirTabla(); // Para verificar en la consola

                tablaPilotos.generarArchivoDot("tabla_hash");

                break;
            case 5:
                //grafo.imprimirMatriz();
                grafo.generarReporte();// Logica para mostrar reporte del grafo dirigido de rutas
                break;
            case 6:
                //miMatriz.mostrar();
                miMatriz.generarDot("matriz.dot");
                system("dot -Tpng matriz.dot -o matriz.png");// Logica para mostrar reporte de la matriz dispersa
                break;
            case 7:
                cout << "" << endl;
                cout << "Volviendo al menú principal..." << endl;
                break;
            default:
                cout << "" << endl;
                cout << "Opción no válida. Intente nuevamente." << endl;
        }
        cout << endl;
    } while(opcionReporte != 7);
}

int main() {
    int opcion;
    do {
        cout << "" << endl;
        cout << "----------MENU---------" << endl;
        cout << "1. Carga de aviones" << endl;
        cout << "2. Carga de pilotos" << endl;
        cout << "3. Carga de rutas" << endl;
        cout << "4. Carga de movimientos" << endl;
        cout << "5. Consulta de horas de vuelo (pilotos)" << endl;
        cout << "6. Recomendar ruta" << endl;
        cout << "7. Visualizar reportes" << endl;
        cout << "8. Salir" << endl;
        cout << "" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarAviones();
                break;
            case 2:
                cargarPilotos();
                cargarDatos();
                break;
            case 3:
                cargarRutas();
                break;
            case 4:
                cargarMovimientos();
                break;
            case 5:
                consultarHora();
                break;
            case 6:
                recomendarRuta();
                break;
            case 7:
                visualizarReportes();
                break;
            case 8:
                cout << "" << endl;
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "" << endl;
                cout << "Opción no válida. Intente nuevamente." << endl;
        }

        cout << endl;
    } while (opcion != 8);

    return 0;
}
