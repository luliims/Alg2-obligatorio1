#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>

// ==== Tipos para el Ejercicio 1 (Ranking) ====

// Jugador: id único, nombre (sin espacios) y puntaje
struct Jugador {
    int id;
    std::string nombre;
    int puntaje;
};

// Nodo para el AVL por ID único
struct NodoAVLId {
    Jugador* jugador;
    int altura;
    NodoAVLId* izq;
    NodoAVLId* der;
};

// Nodo para el AVL por Puntaje
struct NodoAVLPuntaje {
    int puntaje;             // clave
    int cantJug;             // cantidad de jugadores que tienen EXACTAMENTE este puntaje
    int minId;               // menor ID con este puntaje (en caso de empate)
    int cantSub;             // cantidad total de jugadores en todo el subárbol (es decir: cantJug + izquierdo.cantSub + derecho.cantSub)
    int altura;
    NodoAVLPuntaje* izq;
    NodoAVLPuntaje* der;
};


#endif
