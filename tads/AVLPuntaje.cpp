#include <iostream>
//#include "utils.cpp" ======== DIO PROBLEMAS EN COMPLIACION
#include "utils.h"

using namespace std;

class AVLPuntaje {
private:
    NodoAVLPuntaje* raiz;
    NodoAVLPuntaje* maxNode; // nodo con mayor puntaje

    int max2(int a, int b) { return (a > b) ? a : b; }
    int altura(NodoAVLPuntaje* n) { return n ? n->altura : 0; }
    int balanceo(NodoAVLPuntaje* n) {
        if (!n) return 0;
        return altura(n->izq) - altura(n->der);
    }
    int cantSub(NodoAVLPuntaje* n) { return n ? n->cantSub : 0; }

    void actualizarNodo(NodoAVLPuntaje* n) {
        if (!n) return;
        n->altura = 1 + max2(altura(n->izq), altura(n->der));
        n->cantSub = cantSub(n->izq) + n->cantJug + cantSub(n->der);
    }

    void rotacionHoraria(NodoAVLPuntaje*& B){
        NodoAVLPuntaje* A = B->izq;
        NodoAVLPuntaje* T2 = A->der;
        B->izq = T2;
        A->der = B;
        actualizarNodo(B);
        actualizarNodo(A);
        B = A;
    }

    void rotacionAntiHoraria(NodoAVLPuntaje*& A){
        NodoAVLPuntaje* B = A->der;
        NodoAVLPuntaje* T2 = B->izq;
        A->der = T2;
        B->izq = A;
        actualizarNodo(A);
        actualizarNodo(B);
        A = B;
    }

    bool insertarAux(NodoAVLPuntaje*& nodo, int puntaje, int id) {
        if (!nodo) {
            nodo = new NodoAVLPuntaje;
            nodo->puntaje = puntaje;
            nodo->cantJug = 1;
            nodo->minId   = id;
            nodo->cantSub = 1;
            nodo->altura  = 1;
            nodo->izq = nodo->der = NULL;
            
            // actualizar maxNode
            if (!maxNode || puntaje > maxNode->puntaje) {
                maxNode = nodo;
            } else if (maxNode && puntaje == maxNode->puntaje) {
                if (id < maxNode->minId) maxNode->minId = id;
            }
            return true;
        }

        bool creado = false;
        if (puntaje < nodo->puntaje) {
            creado = insertarAux(nodo->izq, puntaje, id);
        } else if (puntaje > nodo->puntaje) {
            creado = insertarAux(nodo->der, puntaje, id);
        } else {
            nodo->cantJug += 1;
            if (id < nodo->minId) nodo->minId = id;
            if (maxNode && nodo == maxNode && id < maxNode->minId) {
                maxNode->minId = id;
            }
            actualizarNodo(nodo);
            return false;
        }

        actualizarNodo(nodo);
        int bal = balanceo(nodo);

        if (bal > 1 && puntaje < nodo->izq->puntaje) rotacionHoraria(nodo);
        else if (bal > 1 && puntaje > nodo->izq->puntaje) {
            rotacionAntiHoraria(nodo->izq);
            rotacionHoraria(nodo);
        }
        else if (bal < -1 && puntaje < nodo->der->puntaje) {
            rotacionHoraria(nodo->der);
            rotacionAntiHoraria(nodo);
        }
        else if (bal < -1 && puntaje > nodo->der->puntaje) rotacionAntiHoraria(nodo);

        return creado;
    }

public:
    AVLPuntaje(): raiz(NULL), maxNode(NULL) {}

    void insertarPuntaje(int puntaje, int id) {
        insertarAux(raiz, puntaje, id);
    }

    bool vacio() const { return raiz == NULL; }

    bool top1(int& mejorId, int& mejorPuntaje) const {
        if (!maxNode) return false;
        mejorId = maxNode->minId;
        mejorPuntaje = maxNode->puntaje;
        return true;
    }
};
