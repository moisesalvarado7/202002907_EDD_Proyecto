#ifndef ARBOLB_H
#define ARBOLB_H

#include "Pagina.h"
#include <fstream>
#include <sstream>
#include <iostream>

class ArbolB {
private:
    Pagina* raiz;

    void inicializar(Pagina* p) {
        p->cont = 0;
        for (int i = 0; i < M1; ++i)
            p->apunt[i] = nullptr;
    }

    void crearPagina(Pagina** p, const std::string& x) {
        *p = new Pagina();
        inicializar(*p);
        (*p)->cont = 1;
        (*p)->info[0] = x;
    }

    void buscar(Pagina* p, const std::string& x, int& posicion) {
        int i = 0;
        bool encontro = false;
        while (p && !encontro) {
            i = 0;
            while (i < p->cont && x > p->info[i])
                i++;
            if (i < p->cont && x == p->info[i]) {
                encontro = true;
                posicion = -1; // Ya existe la llave
            } else if (i == p->cont || x < p->info[i]) {
                p = p->apunt[i];
            } else {
                p = p->apunt[i + 1];
            }
        }
        if (!encontro)
            posicion = i;
    }

    void insertar(Pagina* p, const std::string& x, int& i) {
        if (p->cont) {
            if (x > p->info[i]) {
                i++;
            } else {
                for (int j = p->cont - 1; j >= i; j--)
                    p->info[j + 1] = p->info[j];
            }
        }
        p->info[i] = x;
        p->cont++;
    }

    int donde(Pagina* p, const std::string& x) {
        int i = 0;
        while (i < p->cont && x > p->info[i])
            i++;
        return i;
    }

    void romper(Pagina* p, Pagina* t, Pagina** q, const std::string& x, std::string& subir) {
        std::vector<std::string> a(M1);
        std::vector<Pagina*> b(M1 + 1);
        int i = 0, s = 0;

        while (i < M && !s) {
            if (p->info[i] < x) {
                a[i] = p->info[i];
                b[i] = p->apunt[i];
                p->apunt[i++] = nullptr;
            } else {
                s = 1;
            }
        }
        a[i] = x;
        b[i] = p->apunt[i];
        p->apunt[i] = nullptr;
        b[++i] = t;

        while (i <= M) {
            a[i] = p->info[i - 1];
            b[i + 1] = p->apunt[i];
            p->apunt[i++] = nullptr;
        }

        *q = new Pagina();
        inicializar(*q);
        p->cont = (*q)->cont = N;
        i = 0;

        while (i < N) {
            p->info[i] = a[i];
            p->apunt[i] = b[i];
            (*q)->info[i] = a[i + N + 1];
            (*q)->apunt[i] = b[i + N + 1];
            i++;
        }
        p->apunt[N] = b[N];
        (*q)->apunt[N] = b[M1];
        subir = a[N];
    }

    void cderechaApunt(Pagina* p, int i) {
        for (int j = p->cont; j > i; j--)
            p->apunt[j] = p->apunt[j - 1];
    }

    void listar(Pagina* p) {
        if (p) {
            for (int i = 0; i < p->cont; i++)
                std::cout << p->info[i] << " ";
            std::cout << std::endl;
            for (int i = 0; i <= p->cont; i++)
                listar(p->apunt[i]);
        }
    }

    void listarDot(std::ofstream& file, Pagina* p) {
        if (p) {
            file << "  \"" << p << "\" [label=\"";
            for (int i = 0; i < p->cont; i++) {
                file << "<f" << i << "> " << p->info[i];
                if (i < p->cont - 1)
                    file << " | ";
            }
            file << "\"];\n";
            for (int i = 0; i <= p->cont; i++) {
                if (p->apunt[i]) {
                    file << "  \"" << p << "\":f" << i << " -> \"" << p->apunt[i] << "\";\n";
                    listarDot(file, p->apunt[i]);
                }
            }
        }
    }

    void ins(Pagina** raiz, const std::string& x, int& s) {
        int posicion, i, terminar = 0, separar = 0;
        Pagina* nuevo;
        std::string subir;

        s = 0;
        if (*raiz == nullptr) {
            crearPagina(raiz, x);
        } else {
            buscar(*raiz, x, posicion);
            if (posicion == -1) {
                s = 1;
            } else {
                while (terminar == 0) {
                    if ((*raiz)->cont == M) {
                        if (separar == 0) {
                            romper(*raiz, nullptr, &nuevo, x, subir);
                            separar = 1;
                        } else {
                            Pagina* nuevo1;
                            romper(*raiz, nuevo, &nuevo1, subir, subir);
                            nuevo = nuevo1;
                        }
                    } else {
                        if (separar == 1) {
                            separar = 0;
                            i = donde(*raiz, subir);
                            insertar(*raiz, subir, i);
                            cderechaApunt(*raiz, i + 1);
                            (*raiz)->apunt[i + 1] = nuevo;
                        } else {
                            insertar(*raiz, x, posicion);
                        }
                        terminar = 1;
                    }
                }
                if (separar == 1 && terminar == 0) {
                    crearPagina(raiz, subir);
                    (*raiz)->apunt[0] = *raiz;
                    (*raiz)->apunt[1] = nuevo;
                }
            }
        }
    }

public:
    ArbolB() : raiz(nullptr) {}

    void insertar(const std::string& x) {
        int s;
        ins(&raiz, x, s);
        if (s == 1)
            std::cout << "La llave ya existe: " << x << std::endl;
    }

    void listar() {
        listar(raiz);
    }

    void generarReporteDot(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "digraph ArbolB {\n";
            file << "  node [shape=record];\n";
            listarDot(file, raiz);
            file << "}\n";
            file.close();
        }
    }

    void imprimirConsola(Pagina* p, int nivel) {
        if (p) {
            for (int i = 0; i < nivel; ++i)
                std::cout << "  ";
            for (int i = 0; i < p->cont; ++i)
                std::cout << p->info[i] << " ";
            std::cout << std::endl;
            for (int i = 0; i <= p->cont; ++i)
                imprimirConsola(p->apunt[i], nivel + 1);
        }
    }

    void imprimir() {
        imprimirConsola(raiz, 0);
    }
};

#endif // ARBOLB_H
