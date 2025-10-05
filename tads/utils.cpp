//=============== NO SE ESTA USANDO ===============

// #include <iostream>
// #include <string>

// //struct NodoAVL {
// //    int dato;
// //    NodoAVL *izq, *der;
// //    int altura;
// //    // NodoAVL(int d) : dato(d), izq(NULL), der(NULL), altura(1) {}
// //};


// // ==== Tipos para el Ejercicio 1 (Ranking) ====

// // Jugador: id único, nombre (sin espacios) y puntaje
// struct Jugador {
//     int id;
//     //char nombre[51];   // hasta 50 chars + '\0'
//     std::string nombre;
//     int puntaje;
// };

// // Nodo para el AVL por ID único
// struct NodoAVLId {
//     Jugador* jugador;      // puntero para no copiar structs grandes
//     int altura;
//     NodoAVLId* izq;
//     NodoAVLId* der;
// };

// // Nodo para el AVL por Puntaje
// struct NodoAVLPuntaje {
//     int puntaje;             // clave
//     int cantJug;             // cantidad de jugadores que tienen  este puntaje
//     int minId;               // menor ID con este puntaje (en caso de empate)
//     int cantSub;             // cantidad total de jugadores en todo el subárbol
//     int altura;
//     NodoAVLPuntaje* izq;
//     NodoAVLPuntaje* der;
// };



