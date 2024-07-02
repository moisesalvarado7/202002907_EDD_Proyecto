#include <iostream>
using namespace std;
int main(){
    int num=7;
    int n;
    int *puntero;
    cout << puntero << endl;
    puntero=&num; //La direccion de num se almacena en la variable puntero 
    cout << puntero<< endl;
    cout << &num; // Si se pone el signo "&" imprime el espacio en memoria
    return 0;
}