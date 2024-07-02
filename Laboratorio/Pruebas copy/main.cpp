#include <iostream>
using namespace std;
#include "Matriz.h"

int main()
{
    /* code */
    Matriz miMatriz;
    miMatriz.insertar("P12345678","V700","Girona");
    miMatriz.insertar("P98765432","V701","Girona");
    miMatriz.insertar("P24688642","V702","Girona");
    miMatriz.insertar("P13579753","V701","Barcelona");
    miMatriz.insertar("P00243590","V701","Madrid");
    miMatriz.insertar("P23456789","V702","Madrid");
    miMatriz.insertar("P67834509","V702","Bilbao");

    miMatriz.mostrar(); 
    miMatriz.generarDot("matriz.dot"); // Generamos el archivo .dot

    // Generamos la imagen usando Graphviz (comando externo)
    system("dot -Tpng matriz.dot -o matriz.png");
    return 0;
}