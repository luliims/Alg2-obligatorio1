#include <iostream>
//#include "utils.cpp"  ======= DIO PROBLEMAS EN COMPLIACION
#include "utils.h" // Jugador y NodoAVLId
using namespace std;

// Contador global para COUNT  - SE CAMBIO A VARIABLE ESTATICA DENTRO DE LA CLASE
//static int g_totalJugadores = 0;
 

// AVL por ID: inserta jugador si el ID no existe
class AVLId {
private:
    NodoAVLId* raiz;
    int totalJugadores;   // contador


    int max2(int a, int b) { return (a > b) ? a : b; }

    int altura(NodoAVLId* n) { 
        return n ? n->altura : 0; 
    }

    int balance(NodoAVLId* n) {
        if (!n) return 0;
        return altura(n->izq) - altura(n->der);
    }

    void rotacionHoraria(NodoAVLId*& B){
        NodoAVLId* A = B->izq;
        NodoAVLId* T2 = A->der;
        B->izq = T2;
        A->der = B;
        B->altura = 1 + max2(altura(B->izq), altura(B->der));
        A->altura = 1 + max2(altura(A->izq), altura(A->der));
        B = A;
    }

    void rotacionAntiHoraria(NodoAVLId*& A){
        NodoAVLId* B = A->der;
        NodoAVLId* T2 = B->izq;
        A->der = T2;
        B->izq = A;
        A->altura = 1 + max2(altura(A->izq), altura(A->der));
        B->altura = 1 + max2(altura(B->izq), altura(B->der));
        A = B;
    }

    // ADD --> Inserta por ID; si existe, NO inserta
    bool insertarAux(NodoAVLId*& nodo, Jugador* jugador) {
        if (!nodo){
            nodo = new NodoAVLId;
            nodo->jugador = jugador;
            nodo->altura = 1;
            nodo->izq = nodo->der = NULL;
            return true;
        } 
        if (jugador->id < nodo->jugador->id) {
            if (!insertarAux(nodo->izq, jugador)) return false;
        } else if (jugador->id > nodo->jugador->id) {
            if (!insertarAux(nodo->der, jugador)) return false;
        } else {
            // ID duplicado
            return false;
        }

        nodo->altura = 1 + max2(altura(nodo->izq), altura(nodo->der));

        int bal = balance(nodo);
        bool izq = bal > 1;
        bool der = bal < -1;

        // Izq-Izq
        if (izq && jugador->id < nodo->izq->jugador->id) {
            rotacionHoraria(nodo);
        }
        // Izq-Der
        else if (izq && jugador->id > nodo->izq->jugador->id) {
            rotacionAntiHoraria(nodo->izq);
            rotacionHoraria(nodo);
        }
        // Der-Izq
        else if (der && jugador->id < nodo->der->jugador->id){
            rotacionHoraria(nodo->der);
            rotacionAntiHoraria(nodo);
        }
        // Der-Der
        else if (der && jugador->id > nodo->der->jugador->id){
            rotacionAntiHoraria(nodo);
        }

        return true;
    }

    void destruir(NodoAVLId*& nodo){
        if(!nodo) return;
        destruir(nodo->der);
        destruir(nodo->izq);
        delete nodo->jugador;
        delete nodo;
        nodo = NULL;
    }

    // Solo para depurar local ----------------- REVISAR SI DEJAR ESTO
    void inOrdenAux(NodoAVLId* nodo){
        if (!nodo) return;
        inOrdenAux(nodo->izq);
        cout << nodo->jugador->id << " " << nodo->jugador->nombre << " " << nodo->jugador->puntaje << "\n";
        inOrdenAux(nodo->der);
    }

    // FIND --> Búsqueda recursiva por ID (no modifica el árbol)
    const NodoAVLId* buscarNodo(const NodoAVLId* nodo, int id) const {
        if (!nodo) return NULL;
        if (id == nodo->jugador->id) return nodo;
        if (id < nodo->jugador->id)  return buscarNodo(nodo->izq, id);
        else                         return buscarNodo(nodo->der, id);
    }


public:
    AVLId() : raiz(NULL), totalJugadores(0) {}
    ~AVLId() { destruir(raiz); }

    bool insertarJugador(int id, const std::string& nombre, int puntaje) {
        Jugador* j = new Jugador{ id, nombre, puntaje };
        bool ok = insertarAux(raiz, j);
        if (ok) totalJugadores++;
        else    delete j;
        return ok;
    }

    void clear() {
        destruir(raiz);
        raiz = NULL;
        totalJugadores = 0;
    }

    // COUNT --> Devuelve la cantidad total de jugadores
    int getTotalJugadores() const { 
        return totalJugadores; 
    }

    // FIND --> Devuelve puntero const al Jugador si existe; NULL si no existe
    const Jugador* findId(int id) const {
        const NodoAVLId* n = buscarNodo(raiz, id);
        return n ? n->jugador : NULL;
    }


};
