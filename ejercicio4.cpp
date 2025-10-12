#include <iostream>
#include "tads/minHeap.cpp"
#include "tads/ListImp.cpp"
using namespace std;

int main() {
    int K;
    cin >> K;

    // Crear K listas
    ListImp<int> *listas = new ListImp<int>[K];

    // Leer cada lista
    for (int i = 0; i < K; i++) {
        int N;
        cin >> N;
        for (int j = 0; j < N; j++) {
            int valor;
            cin >> valor;
            listas[i].insert(valor);
        }
    }

    // Crear minHeap con capacidad K
    minHeap heap(K);

    // Insertar el primer elemento de cada lista
    for (int i = 0; i < K; i++) {
        if (!listas[i].isEmpty()) {
            Nodo n;
            n.valor = listas[i].get(0);  // primer elemento
            n.listaId = i;               // de qué lista viene
            n.pos = 0;                   // posición dentro de esa lista
            heap.insertar(n);
        }
    }

    // Fusionar
    while (!heap.estaVacio()) {
        Nodo min = heap.tope();
        cout << min.valor << "\n"; // imprimir el menor
        heap.eliminar();

        int listaId = min.listaId;
        int siguientePos = min.pos + 1;

        // Si hay un siguiente elemento en esa lista
        if (siguientePos < listas[listaId].getSize()) {
            Nodo nuevo;
            nuevo.valor = listas[listaId].get(siguientePos);
            nuevo.listaId = listaId;
            nuevo.pos = siguientePos;
            heap.insertar(nuevo);
        }
    }

    delete[] listas;
    return 0;
}