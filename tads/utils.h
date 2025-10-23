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
    int puntaje;        // clave
    int cantJug;        // [PARA RANK] cantidad de jugadores que tienen el puntaje EXACTO 
    int minId;          // [PARA TOP1] menor ID con este puntaje (en caso de empate) 
    int cantSub;        // [PARA RANK] cantidad de jugadores que hay en total en el subárbol (o sea: cantJug + izq->cantSub + der->cantSub)
    int altura;
    NodoAVLPuntaje* izq;
    NodoAVLPuntaje* der;
};


#endif
