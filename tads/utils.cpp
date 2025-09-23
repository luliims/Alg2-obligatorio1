#include <iostream>

struct NodoAVL {
    int dato;
    NodoAVL *izq, *der;
    int altura;
    // NodoAVL(int d) : dato(d), izq(NULL), der(NULL), altura(1) {}
};
