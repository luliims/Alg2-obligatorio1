#include "TablaHashCerradaDominio.h"
#include <iostream>
using namespace std;

// ==========================
// Constructor DominioEntry
// ==========================
DominioEntry::DominioEntry() {
    dominio = "";
    count = 0;
    headIndex = -1;
    ocupado = false;
    borrado = false;
}

// ==========================
// Implementación de TablaHashCerradaDominio
// ==========================

TablaHashCerradaDominio::TablaHashCerradaDominio(int tam) {
    tamanio = tam;
    cantidad = 0;
    tabla = new DominioEntry[tamanio];
}

TablaHashCerradaDominio::~TablaHashCerradaDominio() {
    delete[] tabla;
}

int TablaHashCerradaDominio::fnHash1(const string& clave) {
    unsigned int h = 0;
    for (char c : clave)
        h = (h * 37 + c) % tamanio;
    return (int)h;
}

int TablaHashCerradaDominio::fnHash2(const string& clave) {
    int h2 = (int)(clave.length() % (tamanio - 1));
    return (h2 == 0) ? 1 : h2;
}

int TablaHashCerradaDominio::posicionTentativa(int intento, const string& clave) {
    return (fnHash1(clave) + intento * fnHash2(clave)) % tamanio;
}

int TablaHashCerradaDominio::buscarDominio(const string& dominio) {
    int intento = 0;
    while (intento < tamanio) {
        int pos = posicionTentativa(intento, dominio);
        DominioEntry& celda = tabla[pos];
        if (!celda.ocupado && !celda.borrado) return -1;
        if (celda.ocupado && celda.dominio == dominio) return pos;
        intento++;
    }
    return -1;
}

int TablaHashCerradaDominio::asegurarDominio(const string& dominio) {
    int pos = buscarDominio(dominio);
    if (pos != -1) return pos;

    int intento = 0;
    int firstDeleted = -1;
    while (intento < tamanio) {
        int idx = posicionTentativa(intento, dominio);
        DominioEntry& celda = tabla[idx];
        if (!celda.ocupado) {
            if (!celda.borrado) {
                int insertPos = (firstDeleted != -1) ? firstDeleted : idx;
                tabla[insertPos].dominio = dominio;
                tabla[insertPos].ocupado = true;
                tabla[insertPos].borrado = false;
                tabla[insertPos].count = 0;
                tabla[insertPos].headIndex = -1;
                cantidad++;
                return insertPos;
            } else if (firstDeleted == -1) {
                firstDeleted = idx;
            }
        }
        intento++;
    }
    return -1;
}

int TablaHashCerradaDominio::obtenerInicio(const string& dominio) {
    int pos = buscarDominio(dominio);
    if (pos == -1) return -1;
    return tabla[pos].headIndex;
}

void TablaHashCerradaDominio::establecerInicio(const string& dominio, int head) {
    int pos = buscarDominio(dominio);
    if (pos != -1)
        tabla[pos].headIndex = head;
}

void TablaHashCerradaDominio::incrementarCount(const string& dominio) {
    int pos = buscarDominio(dominio);
    if (pos != -1)
        tabla[pos].count++;
}

void TablaHashCerradaDominio::decrementarCount(const string& dominio) {
    int pos = buscarDominio(dominio);
    if (pos != -1 && tabla[pos].count > 0)
        tabla[pos].count--;
}

int TablaHashCerradaDominio::count_Domain(const string& dominio) {
    int pos = buscarDominio(dominio);
    if (pos == -1) return 0;
    return tabla[pos].count;
}

void TablaHashCerradaDominio::clear_Domain(const string& dominio) {
    int pos = buscarDominio(dominio);
    if (pos != -1) {
        tabla[pos].count = 0;
        tabla[pos].headIndex = -1;
    }
}

void TablaHashCerradaDominio::clear() {
    for (int i = 0; i < tamanio; i++) {
        tabla[i].ocupado = false;
        tabla[i].borrado = false;
        tabla[i].count = 0;
        tabla[i].headIndex = -1;
    }
    cantidad = 0;
}

