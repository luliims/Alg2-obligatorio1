#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/TablaHashAbierto.cpp"

using namespace std;

void PUT(TablaHashAbierta_Agenda &cache, string dominio, string path, string titulo, int tiempo){
    cache.insertar(dominio, cache.fnHash(path), dominio, path, titulo, tiempo);
}

string GET(TablaHashAbierta_Agenda cache, string dominio, string path){
    NodoLista* nodo = cache.buscarNodo(dominio);
    string dev = "";
    if (nodo == nullptr){
        dev = "recurso_no_encontrado";
    }
    else{
        dev = cache.getTitle(nodo) + " " + to_string(cache.getTime(nodo)); 
    }
    return dev;
}

bool CONTAINS(TablaHashAbierta_Agenda cache, string dominio, string path){
    if (cache.buscar(dominio) != -1 ){
        return true;
    }
    return false;
}

void REMOVE(TablaHashAbierta_Agenda &cache, string dominio, string path){
    cache.eliminar(dominio);
}

int COUNT_DOMAIN(TablaHashAbierta_Agenda cache, string dominio){
    return cache.contarDominio(dominio);
}

string LIST_DOMAIN(TablaHashAbierta_Agenda cache, string dominio){
    return cache.listarDominio(dominio);
}

void CLEAR_DOMAIN(TablaHashAbierta_Agenda &cache, string dominio){
    cache.limpiarDominio(dominio);
}

int SIZE(TablaHashAbierta_Agenda cache){
    return cache.getSize();
}

void CLEAR(TablaHashAbierta_Agenda &cache){
    cache.limpiarTotal();
}

#include <sstream>

int main() {
    int n;
    cin >> n;
    cin.ignore();
    while(n < 1 || n > 1000){
        cout << "Debe de ser un valor entre 1 y 1000\n";
        cin >> n;
        cin.ignore();
    }

    TablaHashAbierta_Agenda cache(n);
    string linea;

    while (getline(cin, linea)){
        if (linea.empty()){
            continue;
        }
        stringstream ss(linea);
        string op;
        ss >> op;
        // pasar a minúsculas
        for (auto& c : op) c = tolower(c);
        if (op == "put") {
            string dominio, path, titulo;
            int tiempo;
            ss >> dominio >> path >> titulo >> tiempo;
            PUT(cache, dominio, path, titulo, tiempo);
            cout << "OK\n";
        }
        else if (op == "get") {
            string dominio, path;
            ss >> dominio >> path;
            cout << GET(cache, dominio, path) << endl;
        }
        else if (op == "contains") {
            string dominio, path;
            ss >> dominio >> path;
            if (CONTAINS(cache, dominio, path)) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
        }
        else if (op == "remove") {
            string dominio, path;
            ss >> dominio >> path;
            REMOVE(cache, dominio, path);
        }
        else if (op == "count_domain") {
            string dominio;
            ss >> dominio;
            cout << COUNT_DOMAIN(cache, dominio) << endl;
        }
        else if (op == "list_domain") {
            string dominio;
            ss >> dominio;
            cout << LIST_DOMAIN(cache, dominio) << endl;
        }
        else if (op == "clear_domain") {
            string dominio;
            ss >> dominio;
            CLEAR_DOMAIN(cache, dominio);
        }
        else if (op == "size") {
            cout << SIZE(cache) << endl;
        }
        else if (op == "clear") {
            CLEAR(cache);
        }
        else {
            cout << "Operación desconocida: " << op << endl;
        }
    }
    return 0;
}


