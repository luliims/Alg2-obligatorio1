#include <iostream>
#include "grafoListaAdy.cpp"
#include "MFSet.cpp"

using namespace std;

Arista ** cargarAristas(GrafoLista * g){
    int A = g->cantidadAristas();
    int V = g->cantidadVertices();
    Arista ** aristas = new Arista*[A]();
    int pos = 0;
    for(int i = 1; i <= V; i++){
        Arista * ady = g->adyacentes(i);
        while(ady){
            aristas[pos] = new Arista();
            aristas[pos]-> origen = i;
            aristas[pos]->destino = ady->destino;
            aristas[pos]->peso = ady->peso;
            pos++;
            ady = ady->sig;
        }
    }
    return aristas;
}

int obtenerMenorAristaNoProcesada(Arista ** aristas, bool * procesados, int A){
    int menor = -1;
    for(int i = 0; i < A; i++){
        if(!procesados[i]){
            if(menor == -1 || aristas[i]->peso < aristas[menor]->peso) menor = i;
        }
    }
    return menor;
}

bool formaCiclo(Arista * arista, MFSet * mfSet){
    return mfSet->find(arista->origen) == mfSet->find(arista->destino);
}

GrafoLista * kruskal(GrafoLista* g){
    int A = g->cantidadAristas();
    int V = g->cantidadVertices();
    GrafoLista * ACM = new GrafoLista(V, false, true);
    MFSet * mfSet = new MFSet(V + 1);
    Arista ** aristas = cargarAristas(g);
    bool * procesados = new bool[A]();
    bool * aceptadas = new bool[A]();
    int cantAceptadas = 0;
    for (int i = 0; i < A /*|| cantAceptadas < V - 1*/; i++){
        int indexArista = obtenerMenorAristaNoProcesada(aristas, procesados, A);
        Arista * arista = aristas[indexArista];
        procesados[indexArista] = true;
        if(!formaCiclo(arista, mfSet)){
            int origen = arista->origen;
            int destino = arista->destino;
            int peso = arista->peso;
            mfSet->merge(origen, destino);
            aceptadas[i] = true;
            cantAceptadas++;
            ACM->agregarArista(origen, destino, peso);
            // ACM->agregarArista(destino, origen, peso);
        }
    }

    return ACM;
}
