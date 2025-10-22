#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/TablaHashAbierto.cpp"

using namespace std;

void PUT(TablaHashAbierta_Agenda &cache, string dominio, string path, string titulo, int tiempo){
    cache.insertar(dominio, cache.fnHash(path), titulo, tiempo);
}

int main()
{
    int n;
    cin >> n;
    while(n<1 || n>1000){
        cout << "Debe de ser un valor entre 1 y 10^6 \n";
        cin >> n;
    }
    TablaHashAbierta_Agenda cache(n);

    string op;
    cin >> op;

    for (auto& x : op) { //pasa op a minúsculas por si no lo escribieron bien
        x = tolower(x);
    }

    if (op == "put"){
            string dominio, path, titulo;
            int tiempo;
            cin >> dominio;
            cin >> path;
            cin >> titulo;
            cin >> tiempo;
            PUT(cache, dominio, path, titulo, tiempo);
        }   
    return 0;
}



