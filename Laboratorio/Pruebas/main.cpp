//#include "TablaHash.h"

    /*
        TablaHash tabla(18);

    tabla.Insertar("P98775432");
    tabla.Insertar("P98765432");
    tabla.Insertar("P23456789");
    tabla.Insertar("P34567890");
    tabla.Insertar("P00243590");
    tabla.Insertar("P24688642");
    tabla.Insertar("P13579753");
    tabla.Insertar("P12345688");
    tabla.Insertar("P12345678");
    tabla.Insertar("P11345678");

    tabla.imprimirTabla(); // Para verificar en la consola

    tabla.generarArchivoDot("tabla_hash");
    tabla.generarArchivoDot("tabla_hash");


    --------------------------------------------------------------------------


        ArbolB t(3); // Un árbol B con grado mínimo 3

    t.insertar(10);
    t.insertar(20);
    t.insertar(5);
    t.insertar(6);
    t.insertar(12);
    t.insertar(30);
    t.insertar(7);
    t.insertar(17);

    std::cout << "Traversing the constructed tree\n";
    t.recorrer();
    std::cout << std::endl;

    
    */
#include <iostream>
#include "ArbolB.h"

int main() {
    ArbolB arbol;

    // Inserción manual de datos
    arbol.insertar("N70001");
    arbol.insertar("N70002");
    arbol.insertar("N70003");
    arbol.insertar("N70004");
    arbol.insertar("N70005");
    arbol.insertar("N70006");
    arbol.insertar("N70007");
    arbol.insertar("N70008");
    arbol.insertar("N70009");
    arbol.insertar("N70010");
    arbol.insertar("N70011");
    arbol.insertar("N70012");
    arbol.insertar("N50013");
    arbol.insertar("N70014");

    std::cout << "\nLlaves en el árbol B:\n";
    arbol.imprimir();

    arbol.generarReporteDot("arbolB.dot");
    std::cout << "Reporte generado: arbolB.dot" << std::endl;
    system("dot -Tpng arbolB.dot -o arbolB.png");
    std::cout << "Imagen generada: arbolB.png" << std::endl;

    return 0;
}
