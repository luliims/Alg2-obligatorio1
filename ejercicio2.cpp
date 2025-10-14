#include <iostream>
#include <string>
using namespace std;

#include "tads/TablaHashCerradaDominio.h"
#include "tads/TablaHashCerradaPath.cpp"   // Es la tabla de recursos

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    TablaHashCerradaDominio dominios;
    TablaHashCerradaRecursos recursos(&dominios);

    int N;           // cantidad de operaciones
    cin >> N;

    string comando;

    for (int i = 0; i < N; i++) {
        cin >> comando;
    
        if (comando == "PUT") {
            string dominio, path, titulo;
            int tiempo;
            cin >> dominio >> path >> titulo >> tiempo;
            recursos.put(dominio, path, titulo, tiempo);
        }

        else if (comando == "GET") {
            string dominio, path;
            cin >> dominio >> path;
            recursos.get(dominio, path);
        }

        else if (comando == "REMOVE") {
            string dominio, path;
            cin >> dominio >> path;
            recursos.remove(dominio, path);
        }

        else if (comando == "CONTAINS") {
            string dominio, path;
            cin >> dominio >> path;
            bool existe = recursos.contains(dominio, path);
            cout << (existe ? "true" : "false") << endl;
        }

        else if (comando == "COUNT_DOMAIN") {
            string dominio;
            cin >> dominio;
            cout << dominios.count_Domain(dominio) << endl;
        }

        else if (comando == "LIST_DOMAIN") {
            string dominio;
            cin >> dominio;
            recursos.list_Domain(dominio);
        }

        else if (comando == "CLEAR_DOMAIN") {
            string dominio;
            cin >> dominio;
            recursos.clear_Domain(dominio);
        }

        else if (comando == "SIZE") {
            cout << recursos.size() << endl;
        }

        else if (comando == "CLEAR") {
            recursos.clear();
            dominios.clear();
        }        
    }

    return 0;
}
