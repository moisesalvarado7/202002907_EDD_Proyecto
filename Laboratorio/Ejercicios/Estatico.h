#include <iostream>
using namespace std;

class Estatico
{
private:
    int datos;
public:
    static int cuenta; //Variables estatica: se accede a la variable global, es una variable propia de la clase
    int valor;
    Estatico();
    Estatico(int n);
    ~Estatico();

};
int Estatico::cuenta=0;


Estatico::Estatico(/* args */)
{
    datos=0;
    valor=10;
    cuenta++;
}
Estatico::Estatico(int x){
    datos=x;
    valor=x;
    cuenta++;
}


Estatico::~Estatico()
{
    cuenta--;
}
