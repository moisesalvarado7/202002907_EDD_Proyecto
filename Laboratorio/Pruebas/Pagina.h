#ifndef PAGINA_H
#define PAGINA_H

#include <iostream>
#include <vector>
#include <string>

const int N = 2;
const int M = 4;
const int M1 = 5;

class Pagina {
public:
    int cont;
    std::vector<std::string> info;
    Pagina* apunt[M1];

    Pagina() {
        cont = 0;
        info.resize(M);
        for (int i = 0; i < M1; ++i)
            apunt[i] = nullptr;
    }
};

#endif // PAGINA_H
