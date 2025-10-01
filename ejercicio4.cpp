#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "minHeap.h"
#include <vector>

using namespace std;

int main(){
    int K;
    cin >> K;

    // Guardamos las listas en memoria
    vector<vector<int>> listas(K);

    for (int i = 0; i < K; i++) {
        int N;
        cin >> N;
        listas[i].resize(N);
        for (int j = 0; j < N; j++) {
            cin >> listas[i][j];
        }
    }

    // Creamos el heap con capacidad K (uno por lista)
    minHeap heap(K);

    // Insertamos el primer elemento de cada lista
    for (int i = 0; i < K; i++) {
        if (!listas[i].empty()) {
            heap.insertar({listas[i][0], i, 0});
        }
    }

    // Merge
    while (!heap.estaVacio()) {
        Nodo top = heap.tope();
        cout << top.valor << "\n";
        heap.eliminar();

        // Insertar siguiente elemento de la misma lista si existe
        if (top.pos + 1 < (int)listas[top.listaId].size()) {
            heap.insertar({listas[top.listaId][top.pos + 1], top.listaId, top.pos + 1});
        }
    }
}
