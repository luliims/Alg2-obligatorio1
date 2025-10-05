// //=============== NO SE ESTA USANDO ===============


// #include <iostream>
// #include "utils.cpp"
// using namespace std;

// class AVL {
//     private:

//         NodoAVL *raiz;

//         int altura(NodoAVL *n) { 
//             return n ? n->altura : 0; 
//         }

//         int balance(NodoAVL *n) {
//             if (!n) return 0;
//             return altura(n->izq) - altura(n->der);
//         }

//         void rotacionHoraria(NodoAVL*& B){
//             cout << "rotando horario" << endl;
//             NodoAVL* A = B->izq;
//             NodoAVL* T2 = A->der;
//             B->izq = T2;
//             A->der = B;
//             B->altura = 1 + max(altura(B->izq), altura(B->der));
//             A->altura = 1 + max(altura(A->izq), altura(A->der));
//             B = A;
//         }

//         void rotacionAntiHoraria(NodoAVL*& A){
//             cout << "rotando antihorario" << endl;
//             NodoAVL * B = A->der;
//             NodoAVL* T2 = B->izq;
//             A->der = T2;
//             B->izq = A;
//             A->altura = 1 + max(altura(A->izq), altura(A->der));
//             B->altura = 1 + max(altura(B->izq), altura(B->der));
//             A = B;
//         }

//         void insertarAux(NodoAVL *& nodo, int dato) {
//             if (!nodo){
//                 // nodo = new NodoAVL(dato);
//                 nodo = new NodoAVL;
//                 nodo->altura = 1;
//                 nodo->dato = dato;
//                 nodo->izq = nodo->der = NULL;
//                 return;
//             } 
//             if (dato < nodo->dato)
//                 insertarAux(nodo->izq, dato);
//             else if (dato > nodo->dato)
//                 insertarAux(nodo->der, dato);
//             else
//                 return;

//             // Calcular altura
//             nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

//             // verificar el balance
//             int balanceo = balance(nodo);
//             bool desbalanceoIzq = balanceo > 1;
//             bool desbalanceoDer = balanceo < -1;

//             // Izq - Izq
//             if(desbalanceoIzq && nodo->izq->dato > dato) {
//                 rotacionHoraria(nodo);
//             }

//             // Izq - Der
//             if(desbalanceoIzq && nodo->izq->dato < dato) {
//                 rotacionAntiHoraria(nodo->izq); // Y
//                 rotacionHoraria(nodo); // Z
//             }

//             // Der - Izq
//             if(desbalanceoDer && nodo->der->dato > dato){
//                 rotacionHoraria(nodo->der); // Y
//                 rotacionAntiHoraria(nodo); // Z
//             }

//             // Der - Der
//             if(desbalanceoDer && nodo->der->dato < dato){
//                 rotacionAntiHoraria(nodo);
//             }
//         }

//         void destruir(NodoAVL*& nodo){
//             if(!nodo) return;
//             destruir(nodo->der);
//             destruir(nodo->izq);
//             delete nodo;
//             nodo = NULL;
//         }


//         void inOrdenAux(NodoAVL* nodo){
//             if (!nodo) return;
//             inOrdenAux(nodo->izq);
//             cout << nodo->dato << endl;
//             inOrdenAux(nodo->der);
//         }
//     public:
//     AVL() : raiz(NULL) {}
//     ~AVL() { 
//         cout << "destruyendo" << endl;
//         destruir(raiz); 
//     }

//     void insertar(int dato) {
//         cout << "Insertando " << dato << endl;
//         insertarAux(raiz, dato);
//     }

//     void inOrder() {
//         cout << "InOrder: ";
//         inOrdenAux(raiz);
//     }
// };