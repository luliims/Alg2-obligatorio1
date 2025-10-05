//#include <cassert>
//#include <limits>
#include <iostream>
#include <string>
#include "tads/AVLId.cpp"
#include "tads/AVLPuntaje.cpp"   // nuevo árbol por puntaje
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

            //avlId.insertarJugador(id, nombre, puntaje); ======= VIEJO

            //Si se insertó en AVLId, entonces actualizar puntaje
            bool nuevo = avlId.insertarJugador(id, nombre, puntaje);
            if (nuevo) {
                 avlPuntaje.insertarPuntaje(puntaje, id);
            }

        } else {
            // Consumimos parámetros para no romper el cursor de entrada --- REVISAR QUE ES ESTO BIEN
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

            else if (op == "RANK") { int dummy; cin >> dummy; }

            
             else if (op == "TOP1") {
                int mejorId, mejorPuntaje;
                if (!avlPuntaje.vacio() && avlPuntaje.top1(mejorId, mejorPuntaje)) {
                    const Jugador* j = avlId.findId(mejorId);
                    if (j) {
                        std::cout << j->nombre << " " << j->puntaje << "\n";
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
    //para probar luego borrar
    //#ifdef DEBUG
    //avlId.inOrder();     // Muestra "id nombre puntaje" en orden por ID
    //#endif
    //borrar hasta aca

    return 0;
}
