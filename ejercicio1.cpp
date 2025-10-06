//#include <cassert>
//#include <limits>
#include <iostream>
#include <string>
#include "tads/AVLId.cpp"        // árbol por ID
#include "tads/AVLPuntaje.cpp"   // árbol por puntaje
#include "tads/utils.h"


using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    AVLId avlId;
    AVLPuntaje avlPuntaje;

    for (int i = 0; i < N; ++i) {
        string op;
        cin >> op;

        if (op == "ADD") {
            int id, puntaje;
            string nombre;            
            cin >> id >> nombre >> puntaje;
            //Si se insertó en AVLId, entonces actualizar puntaje
            bool nuevo = avlId.insertarJugador(id, nombre, puntaje);
            if (nuevo) {
                 avlPuntaje.insertarPuntaje(puntaje, id);
            }

        } else {
            if (op == "FIND")  { 
                int id;
                cin >> id;
                const Jugador* j = avlId.findId(id);
                if (j) {
                    cout << j->nombre << " " << j->puntaje << "\n";
                } else {
                    cout << "jugador_no_encontrado\n";
                }
             }

            else if (op == "RANK") { 
                int p;
                cin >> p;
                cout << avlPuntaje.rank(p) << "\n";
            }
            
             else if (op == "TOP1") {
                int mejorId, mejorPuntaje;
                if (!avlPuntaje.vacio() && avlPuntaje.top1(mejorId, mejorPuntaje)) {
                    const Jugador* j = avlId.findId(mejorId);
                    if (j) {
                        cout << j->nombre << " " << j->puntaje << "\n";
                    } else {
                        // En caso que no haya jugadores se muestra sin_jugadores
                        cout << "sin_jugadores\n";
                    }
                } else {
                    cout << "sin_jugadores\n";
                }
            }

            else if (op == "COUNT")  { 
                cout << avlId.getTotalJugadores() << "\n";
            }
        }        
    }
   
    return 0;
}
