#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <climits> // Para usar INT_MAX
#include <algorithm> // Para usar std::reverse
#include "Vertice.h"
using namespace std;

class Grafo
{
private:
    int numVertices;
    int maxVertices;
    vector<Vertice> vertices;
    vector<vector<int>> matrizAdy;

public:
    Grafo(int max) : numVertices(0), maxVertices(max), matrizAdy(max, vector<int>(max, 0)) {}

    int getNumVertices() {
        return this->numVertices;
    }

    void nuevoVertice(string nombre) {
        if (existeVertice(nombre) == -1) {
            vertices.push_back(Vertice(nombre, numVertices));
            numVertices++;
        }
    }

    int existeVertice(string nombre) {
        for (int i = 0; i < numVertices; i++) {
            if (vertices[i].esIgual(nombre)) {
                return i;
            }
        }
        return -1;
    }

    void nuevoArco(string nom1, string nom2, int distancia) {
        int vertice1 = existeVertice(nom1);
        int vertice2 = existeVertice(nom2);
        if (vertice1 >= 0 && vertice2 >= 0) {
            matrizAdy[vertice1][vertice2] = distancia;
        } else {
            cout << "Error, uno de los vértices no existe\n";
        }
    }

    void imprimirMatriz() {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << matrizAdy[i][j] << " ";
            }
            cout << endl;
        }
    }

    void generarReporte() {
        ofstream archivo("grafo.dot");
        archivo << "digraph G { " << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (matrizAdy[i][j] > 0) {
                    archivo << vertices[i].getNombre() << " -> " << vertices[j].getNombre()
                            << " [label=\"" << matrizAdy[i][j] << "\"];" << endl;
                }
            }
        }
        archivo << "}" << endl;
        archivo.close();
        system("dot -Tpng grafo.dot -o grafo.png");
        system("start grafo.png");
    }

    // Método para recomendar la ruta más corta entre dos ciudades
    void recomendarRuta() {
        string ciudadOrigen, ciudadDestino;
        cout << "Ingrese la ciudad de origen: ";
        cin >> ciudadOrigen;
        cout << "Ingrese la ciudad de destino: ";
        cin >> ciudadDestino;

        int verticeOrigen = existeVertice(ciudadOrigen);
        int verticeDestino = existeVertice(ciudadDestino);

        if (verticeOrigen == -1 || verticeDestino == -1) {
            cout << "Error, una de las ciudades no existe en el grafo\n";
            return;
        }

        vector<int> distancias(numVertices, INT_MAX);
        vector<int> predecesores(numVertices, -1);
        vector<bool> visitado(numVertices, false);

        distancias[verticeOrigen] = 0;

        for (int i = 0; i < numVertices; i++) {
            int u = -1;

            for (int j = 0; j < numVertices; j++) {
                if (!visitado[j] && (u == -1 || distancias[j] < distancias[u])) {
                    u = j;
                }
            }

            if (distancias[u] == INT_MAX) break;

            visitado[u] = true;

            for (int v = 0; v < numVertices; v++) {
                if (!visitado[v] && matrizAdy[u][v] > 0 && distancias[u] + matrizAdy[u][v] < distancias[v]) {
                    distancias[v] = distancias[u] + matrizAdy[u][v];
                    predecesores[v] = u;
                }
            }
        }

        if (distancias[verticeDestino] == INT_MAX) {
            cout << "No hay ruta disponible entre " << ciudadOrigen << " y " << ciudadDestino << "\n";
        } else {
            cout << "La ruta más corta de " << ciudadOrigen << " a " << ciudadDestino << " es: \n";
            vector<int> ruta;
            for (int v = verticeDestino; v != -1; v = predecesores[v]) {
                ruta.push_back(v);
            }
            reverse(ruta.begin(), ruta.end());
            for (int i = 0; i < ruta.size(); i++) {
                cout << vertices[ruta[i]].getNombre();
                if (i != ruta.size() - 1) cout << " -> ";
            }
            cout << "\nDistancia total: " << distancias[verticeDestino] << "\n";
        }
    }
};

#endif
