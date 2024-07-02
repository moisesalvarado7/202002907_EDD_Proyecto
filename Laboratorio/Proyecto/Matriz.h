#include <iostream>
#include <string>
#include <fstream>
#include "NodoMatriz.h"

using namespace std;

class Matriz {
public:
    NodoMatriz* root;

    Matriz() {
        root = new NodoMatriz("Root", "-1", "-1");
    }

    NodoMatriz* buscarFila(string fila) {
        NodoMatriz* aux = root->abajo;
        while (aux != nullptr) {
            if (aux->fila == fila) return aux;
            aux = aux->abajo;
        }
        return nullptr;
    }

    NodoMatriz* buscarColumna(string columna) {
        NodoMatriz* aux = root->siguiente;
        while (aux != nullptr) {
            if (aux->columna == columna) return aux;
            aux = aux->siguiente;
        }
        return nullptr;
    }

    int determinarGrupo(string columna) {
        NodoMatriz* aux = root->siguiente;
        int grupo = 2;
        while (aux != nullptr) {
            if (aux->columna == columna) {
                return grupo;
            }
            aux = aux->siguiente;
            grupo++;
        }
        return 1; // En caso de que no se encuentre, aunque no debería pasar.
    }

    void insertar(string dato, string fila, string columna) {
        NodoMatriz* nodoDato = new NodoMatriz(dato, fila, columna);
        NodoMatriz* nodoFila = buscarFila(fila);
        NodoMatriz* nodoColumna = buscarColumna(columna);

        if (nodoFila == nullptr) {
            nodoFila = new NodoMatriz(fila, fila, "-1");
            NodoMatriz* aux = root;
            while (aux->abajo != nullptr) aux = aux->abajo;
            aux->abajo = nodoFila;
            nodoFila->arriba = aux;
        }

        if (nodoColumna == nullptr) {
            nodoColumna = new NodoMatriz(columna, "-1", columna);
            NodoMatriz* aux = root;
            while (aux->siguiente != nullptr) aux = aux->siguiente;
            aux->siguiente = nodoColumna;
            nodoColumna->anterior = aux;
        }

        NodoMatriz* auxFila = nodoFila;
        while (auxFila->siguiente != nullptr) auxFila = auxFila->siguiente;
        auxFila->siguiente = nodoDato;
        nodoDato->anterior = auxFila;

        NodoMatriz* auxColumna = nodoColumna;
        while (auxColumna->abajo != nullptr) auxColumna = auxColumna->abajo;
        auxColumna->abajo = nodoDato;
        nodoDato->arriba = auxColumna;
    }

    void eliminar(string fila, string columna) {
        NodoMatriz* nodoFila = buscarFila(fila);
        NodoMatriz* nodoColumna = buscarColumna(columna);

        if (nodoFila == nullptr || nodoColumna == nullptr) {
            cout << "Fila o columna no encontrada." << endl;
            return;
        }

        NodoMatriz* aux = nodoFila->siguiente;
        while (aux != nullptr && aux->columna != columna) aux = aux->siguiente;

        if (aux == nullptr) {
            cout << "Dato no encontrado." << endl;
            return;
        }

        if (aux->anterior != nullptr) aux->anterior->siguiente = aux->siguiente;
        if (aux->siguiente != nullptr) aux->siguiente->anterior = aux->anterior;

        if (aux->arriba != nullptr) aux->arriba->abajo = aux->abajo;
        if (aux->abajo != nullptr) aux->abajo->arriba = aux->arriba;

        delete aux;

        if (nodoFila->siguiente == nullptr) {
            if (nodoFila->arriba != nullptr) nodoFila->arriba->abajo = nodoFila->abajo;
            if (nodoFila->abajo != nullptr) nodoFila->abajo->arriba = nodoFila->arriba;
            delete nodoFila;
        }

        if (nodoColumna->abajo == nullptr) {
            if (nodoColumna->anterior != nullptr) nodoColumna->anterior->siguiente = nodoColumna->siguiente;
            if (nodoColumna->siguiente != nullptr) nodoColumna->siguiente->anterior = nodoColumna->anterior;
            delete nodoColumna;
        }
    }

void generarDot(string nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivo << "digraph G {" << endl;
            archivo << "    node [shape=box];" << endl;

            archivo << "    /*------------Cabeceras Horizontales------------*/" << endl;
            archivo << "    n0 [label=\"root\" group=1];" << endl;

            NodoMatriz* columnaActual = root->siguiente;
            int grupo = 2;
            while (columnaActual != nullptr) {
                archivo << "    " << columnaActual->columna << " [label=\"" << columnaActual->columna << "\" group=" << grupo << "];" << endl;
                columnaActual = columnaActual->siguiente;
                grupo++;
            }

            archivo << "    /*------------Cabeceras Verticales------------*/" << endl;
            NodoMatriz* filaActual = root->abajo;
            while (filaActual != nullptr) {
                archivo << "    " << filaActual->fila << " [label=\"" << filaActual->fila << "\" group=1];" << endl;
                filaActual = filaActual->abajo;
            }

            archivo << "    /*------------Datos------------*/" << endl;
            filaActual = root->abajo;
            while (filaActual != nullptr) {
                columnaActual = filaActual->siguiente;
                while (columnaActual != nullptr) {
                    int grupo = determinarGrupo(columnaActual->columna);
                    archivo << "    " << filaActual->fila << "_" << columnaActual->columna << " [label=\"" << columnaActual->dato << "\" group=" << grupo << "];" << endl;
                    columnaActual = columnaActual->siguiente;
                }
                filaActual = filaActual->abajo;
            }

            archivo << "    /*------------Relaciones Horizontales------------*/" << endl;
            archivo << "    n0";
            columnaActual = root->siguiente;
            string reverseHorizontal = "";
            while (columnaActual != nullptr) {
                archivo << " -> " << columnaActual->columna;
                reverseHorizontal = " -> " + columnaActual->columna + reverseHorizontal;
                columnaActual = columnaActual->siguiente;
            }
            archivo << ";" << endl;
            archivo << "    " << reverseHorizontal.substr(4) << " -> n0;" << endl;

            filaActual = root->abajo;
            while (filaActual != nullptr) {
                columnaActual = filaActual->siguiente;
                archivo << "    " << filaActual->fila;
                string reverseRow = "";
                while (columnaActual != nullptr) {
                    archivo << " -> " << filaActual->fila << "_" << columnaActual->columna;
                    reverseRow = " -> " + filaActual->fila + "_" + columnaActual->columna + reverseRow;
                    columnaActual = columnaActual->siguiente;
                }
                archivo << ";" << endl;
                archivo << "    " << reverseRow.substr(4) << " -> " << filaActual->fila << ";" << endl;
                filaActual = filaActual->abajo;
            }

            archivo << "    /*------------Relaciones Verticales------------*/" << endl;
            archivo << "    n0";
            filaActual = root->abajo;
            string reverseVertical = "";
            while (filaActual != nullptr) {
                archivo << " -> " << filaActual->fila;
                reverseVertical = " -> " + filaActual->fila + reverseVertical;
                filaActual = filaActual->abajo;
            }
            archivo << ";" << endl;
            archivo << "    " << reverseVertical.substr(4) << " -> n0;" << endl;

            columnaActual = root->siguiente;
            while (columnaActual != nullptr) {
                filaActual = columnaActual->abajo;
                archivo << "    " << columnaActual->columna;
                string reverseColumn = "";
                while (filaActual != nullptr) {
                    archivo << " -> " << filaActual->fila << "_" << columnaActual->columna;
                    reverseColumn = " -> " + filaActual->fila + "_" + columnaActual->columna + reverseColumn;
                    filaActual = filaActual->abajo;
                }
                archivo << ";" << endl;
                archivo << "    " << reverseColumn.substr(4) << " -> " << columnaActual->columna << ";" << endl;
                columnaActual = columnaActual->siguiente;
            }

            archivo << "    /*------------Encuadre------------*/" << endl;
            archivo << "    { rank=same; n0";
            columnaActual = root->siguiente;
            while (columnaActual != nullptr) {
                archivo << "; " << columnaActual->columna;
                columnaActual = columnaActual->siguiente;
            }
            archivo << " }" << endl;

            filaActual = root->abajo;
            while (filaActual != nullptr) {
                archivo << "    { rank=same; " << filaActual->fila;
                columnaActual = filaActual->siguiente;
                while (columnaActual != nullptr) {
                    archivo << "; " << filaActual->fila << "_" << columnaActual->columna;
                    columnaActual = columnaActual->siguiente;
                }
                archivo << " }" << endl;
                filaActual = filaActual->abajo;
            }

            archivo << "}" << endl;
            archivo.close();
        } else {
            cout << "No se pudo abrir el archivo" << endl;
        }
    }
};

