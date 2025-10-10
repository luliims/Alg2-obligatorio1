#ifndef MINHEAP
#define MINHEAP

struct Nodo {
    int valor;
    int listaId;
    int pos;
};

class minHeapNodos {
private:
    Nodo * vec;
    int capacidad;
    int primeroLibre;

    bool estaLleno();
    int padre(int pos);
    int izq(int pos);
    int der(int pos);
    int funcionComparadora(Nodo a, Nodo b);
    void intercambiar(int i, int j);
    void flotar(int pos);
    void hundir(int pos);

public:
    minHeapNodos(int capacidad);
    ~minHeapNodos();

    void insertar(Nodo dato);
    void eliminar();
    Nodo tope();
    bool estaVacio();
};

#endif
