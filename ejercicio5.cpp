#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "funciones/kruskal/grafoListaAdy.cpp"
#include "funciones/kruskal/kruskal.cpp"


using namespace std;

int main() {
    int V, E;
    cin >> V >> E;

    GrafoLista* g = new GrafoLista(V, false, true);
    int i = 0;
    while(i < E){
        int u, v, w;
        cin >> u >> v >> w;
        g->agregarArista(u + 1, v + 1, w);
        i++;
    }

    GrafoLista* mst = kruskal(g);

    int pesoTotal = 0;
    int j = 1; 
    while (j <= V){
        Arista* ady = mst->adyacentes(j);
        while (ady){
            if (i < mst->getDestino(ady)){
                pesoTotal += mst->getPeso(ady);
            }
            ady = mst->getSig(ady);
        }
        j++;
    }
    cout << pesoTotal << endl;
    return 0;
}
