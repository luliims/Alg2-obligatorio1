#include <iostream>
#include "tads/minHeap.cpp"
#include "tads/ListImp.cpp"
using namespace std;

int main() {
    int K;
    cin >> K;
    ListImp<int> *lists = new ListImp<int>[K];
    minHeap hp(K);
    for (int i = 0; i < K; i++) {
        int N;
        cin >> N;
        for (int j = 0; j < N; j++) {
            int val;
            cin >> val;
            lists[i].insert(val);
        }
    }
    for (int i = 0; i < K; i++) { //inserto primer nodo de cada lista
        if (!lists[i].isEmpty()) {
            Nodo n;
            n.valor = lists[i].get(0);
            n.listaId = i;
            n.pos = 0;
            hp.insertar(n);
        }
    }
    while (!hp.estaVacio()) { //fusiono las listas en el heap
        Nodo min = hp.tope();
        cout << min.valor << "\n";
        hp.eliminar();
        int iDList = min.listaId;
        int nextPos = min.pos + 1;
        if (nextPos < lists[iDList].getSize()) {
            Nodo nuevo;
            nuevo.valor = lists[iDList].get(nextPos);
            nuevo.listaId = iDList;
            nuevo.pos = nextPos;
            hp.insertar(nuevo);
        }
    }

    delete[] lists;
    return 0;
}