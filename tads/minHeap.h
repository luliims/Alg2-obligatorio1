#ifndef MINHEAPNODOS
#define MINHEAPNODOS

struct Nodo {
    int valor;
    int listaId;
    int pos;
};

class minHeap{
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
    minHeap(int capacidad);
    ~minHeap();

    void insertar(Nodo dato);
    void eliminar();
    Nodo tope();
    bool estaVacio();
};

#endif
