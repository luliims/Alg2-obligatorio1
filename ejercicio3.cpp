#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/TablaHashAbierto.cpp"
#include <sstream>

using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(); 
    TablaHashAbierta_Agenda cache(n);

    string linea;
    while (getline(cin, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string comando;
        ss >> comando;

        // pasar a minúsculas
        for (auto &c : comando) c = tolower(c);

        if (comando == "put") {
            string dominio, path, titulo;
            int tiempo;
            ss >> dominio >> path >> titulo >> tiempo;
            cache.insertar(dominio, cache.fnHash(path), dominio, path, titulo, tiempo);
        }
        else if (comando == "get") {
            string dominio, path;
            ss >> dominio >> path;
            NodoLista* nodo = cache.buscarNodo(dominio, path);
            if (nodo != nullptr && nodo->path == path)
                cout << nodo->title << " " << nodo->time << endl;
            else
                cout << "recurso_no_encontrado" << endl;
        }
        else if (comando == "contains") {
            string dominio, path;
            ss >> dominio >> path;
            NodoLista* nodo = cache.buscarNodo(dominio, path);
            bool existe = (nodo != nullptr && nodo->path == path);
            /*cout << (existe ? "true" : "false") << endl;*/
            if (existe){
                cout << "true" << endl;
            }
            else{
                cout << "false" << endl;
            }
        }
        else if (comando == "size") {
            cout << cache.getSize() << endl;
        }
        else if (comando == "count_domain") {
            string dominio;
            ss >> dominio;
            cout << cache.contarDominio(dominio) << endl;
        }
        else if (comando == "list_domain") {
            string dominio;
            ss >> dominio;
            cout << cache.listarDominio(dominio) << endl;
        }
        else if (comando == "clear_domain") {
            string dominio;
            ss >> dominio;
            cache.limpiarDominio(dominio);
        }
        else if (comando == "clear") {
           cache.limpiarTotal();
        }
    }
}