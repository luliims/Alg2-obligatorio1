#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "funciones/kruskal/kruskal.cpp"


using namespace std;

int main() {
    int V, E;
    cin >> V >> E;

    GrafoLista* g = new GrafoLista(V, false, true);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // ajustamos índices si la entrada es de 0..V-1
        g->agregarArista(u + 1, v + 1, w);
    }

    GrafoLista* ACM = kruskal(g);

    int pesoTotal = 0;
    for (int i = 1; i <= V; i++) {
        Arista* ady = ACM->adyacentes(i);
        while (ady) {
            if (i < ady->destino)  // sumar solo una vez cada arista
                pesoTotal += ady->peso;
            ady = ady->sig;
        }
    }

    cout << pesoTotal << endl;

    return 0;
}
