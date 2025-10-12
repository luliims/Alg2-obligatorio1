#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/TablaHashAbierto.cpp"

using namespace std;

int main()
{
    int n;
    cin >> n;
    while(n<1 || n>1000){
        cout << "Debe de ser un valor entre 1 y 10^6 \n";
        cin >> n;
    }
    TablaHashAbierta_Agenda cache(n);
    void PUT(string dominio, string path, string titulo, int tiempo){
        if (cache.buscar(dominio)== -1){
            cache.insertar(dominio, fnHash(path));
        }
    }
}