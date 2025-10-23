#include "TablaHashCerradaDominio.h"
#include <iostream>
#include <string>
using namespace std;

// ==========================
// Estructura de Recurso
// ==========================
struct Recurso {
    string dominio;
    string path;
    string titulo;
    int tiempo;
    int siguiente;       // índice al siguiente recurso del mismo dominio
    bool ocupado;
    bool borrado;

    Recurso() {
        dominio = "";
        path = "";
        titulo = "";
        tiempo = 0;
        siguiente = -1;
        ocupado = false;
        borrado = false;
    }
};

// ==========================
// Tabla Hash Cerrada de Recursos
// ==========================
class TablaHashCerradaRecursos {
private:
    Recurso* tabla;
    int tamanio;
    int cantidad;
    TablaHashCerradaDominio* dominios; // referencia a la tabla de dominios

    // ========== HASH doble ==========
    int fnHash1(const string& clave) {
        unsigned int h = 0;
        for (int i = 0; i < clave.length(); i++)
            h = (h * 37 + clave[i]) % tamanio;
        return (int)h;
    }

    int fnHash2(const string& clave) {
        int h2 = (int)(clave.length() % (tamanio - 1));
        return (h2 == 0) ? 1 : h2;
    }

    int posicionTentativa(int intento, const string& clave) {
        return (fnHash1(clave) + intento * fnHash2(clave)) % tamanio;
    }

    string claveCompuesta(const string& dominio, const string& path) {
        return dominio + "|" + path;
    }

public:
    TablaHashCerradaRecursos(TablaHashCerradaDominio* refDom, int tam = 1009) {
        tamanio = tam;
        cantidad = 0;
        dominios = refDom;
        tabla = new Recurso[tamanio];
    }

    ~TablaHashCerradaRecursos() {
        delete[] tabla;
    }

    // ================================
    // PUT dominio path titulo tiempo
    // ================================
    void put(const string& dominio, const string& path, const string& titulo, int tiempo) {
        string clave = claveCompuesta(dominio, path);
        int intento = 0;
        int firstDeleted = -1;

        while (intento < tamanio) {
            int pos = posicionTentativa(intento, clave);
            Recurso& celda = tabla[pos];

            if (!celda.ocupado) {
                if (!celda.borrado) {
                    // Libre de verdad → insertar
                    int insertPos = (firstDeleted != -1) ? firstDeleted : pos;
                    tabla[insertPos].dominio = dominio;
                    tabla[insertPos].path = path;
                    tabla[insertPos].titulo = titulo;
                    tabla[insertPos].tiempo = tiempo;
                    tabla[insertPos].ocupado = true;
                    tabla[insertPos].borrado = false;
                    tabla[insertPos].siguiente = -1;
                    cantidad++;

                    // Aseguramos el dominio
                    int idxDom = dominios->asegurarDominio(dominio);
                    int oldHead = dominios->obtenerInicio(dominio);

                    // Insertamos este recurso al inicio de la lista del dominio
                    tabla[insertPos].siguiente = oldHead;
                    dominios->establecerInicio(dominio, insertPos);
                    dominios->incrementarCount(dominio);

                    return;
                } else if (firstDeleted == -1) {
                    firstDeleted = pos; // recordamos primer borrado
                }
            } else {
                // Celda ocupada
                if (tabla[pos].dominio == dominio && tabla[pos].path == path) {
                    // Ya existe → actualizar
                    tabla[pos].titulo = titulo;
                    tabla[pos].tiempo = tiempo;

                    // Mover a cabeza del dominio (más reciente)
                    int inicio = dominios->obtenerInicio(dominio);
                    if (inicio != pos) {
                        // buscar el anterior para desenganchar
                        int prev = -1, actual = inicio;
                        while (actual != -1 && actual != pos) {
                            prev = actual;
                            actual = tabla[actual].siguiente;
                        }
                        if (prev != -1)
                            tabla[prev].siguiente = tabla[pos].siguiente;

                        tabla[pos].siguiente = inicio;
                        dominios->establecerInicio(dominio, pos);
                    }
                    return;
                }
            }
            intento++;
        }

        // Si salimos y hay un borrado disponible
        if (firstDeleted != -1) {
            int pos = firstDeleted;
            tabla[pos].dominio = dominio;
            tabla[pos].path = path;
            tabla[pos].titulo = titulo;
            tabla[pos].tiempo = tiempo;
            tabla[pos].ocupado = true;
            tabla[pos].borrado = false;
            tabla[pos].siguiente = -1;
            cantidad++;

            int idxDom = dominios->asegurarDominio(dominio);
            int oldHead = dominios->obtenerInicio(dominio);
            tabla[pos].siguiente = oldHead;
            dominios->establecerInicio(dominio, pos);
            dominios->incrementarCount(dominio);
        }
    }

    // ================================
    // GET dominio path
    // ================================
    void get(const string& dominio, const string& path) {
        string clave = claveCompuesta(dominio, path);
        int intento = 0;

        while (intento < tamanio) {
            int pos = posicionTentativa(intento, clave);
            Recurso& celda = tabla[pos];
            if (!celda.ocupado && !celda.borrado) break;
            if (celda.ocupado && celda.dominio == dominio && celda.path == path) {
                cout << celda.titulo << " " << celda.tiempo << endl;
                return;
            }
            intento++;
        }
        cout << "recurso_no_encontrado" << endl;
    }

    // ================================
    // CONTAINS dominio path
    // ================================
    bool contains(const string& dominio, const string& path) {
        string clave = claveCompuesta(dominio, path);
        int intento = 0;

        while (intento < tamanio) {
            int pos = posicionTentativa(intento, clave);
            Recurso& celda = tabla[pos];
            if (!celda.ocupado && !celda.borrado) return false;
            if (celda.ocupado && celda.dominio == dominio && celda.path == path)
                return true;
            intento++;
        }
        return false;
    }

    // ================================
    // REMOVE dominio path
    // ================================
    void remove(const string& dominio, const string& path) {
        string clave = claveCompuesta(dominio, path);
        int intento = 0;

        while (intento < tamanio) {
            int pos = posicionTentativa(intento, clave);
            Recurso& celda = tabla[pos];
            if (!celda.ocupado && !celda.borrado) return;
            if (celda.ocupado && celda.dominio == dominio && celda.path == path) {
                // desenganchar de la lista
                int inicio = dominios->obtenerInicio(dominio);
                if (inicio == pos) {
                    dominios->establecerInicio(dominio, celda.siguiente);
                } else {
                    int prev = inicio;
                    while (prev != -1 && tabla[prev].siguiente != pos)
                        prev = tabla[prev].siguiente;
                    if (prev != -1)
                        tabla[prev].siguiente = celda.siguiente;
                }

                celda.ocupado = false;
                celda.borrado = true;
                dominios->decrementarCount(dominio);
                cantidad--;
                return;
            }
            intento++;
        }
    }

    // ================================
    // LIST_DOMAIN dominio
    // ================================
    void list_Domain(const string& dominio) {
    int inicio = dominios->obtenerInicio(dominio);
    if (inicio == -1) {
        cout << endl;
        return;
    }

    int actual = inicio;
    bool primero = true;

    while (actual != -1) {
        if (!primero) cout << " ";
        cout << tabla[actual].path;
        primero = false;
        actual = tabla[actual].siguiente;
    }
    cout << endl;
}


    // ================================
    // CLEAR_DOMAIN dominio
    // ================================
    void clear_Domain(const string& dominio) {
        int inicio = dominios->obtenerInicio(dominio);
        int actual = inicio;
        while (actual != -1) {
            tabla[actual].ocupado = false;
            tabla[actual].borrado = true;
            cantidad--;
            actual = tabla[actual].siguiente;
        }
        dominios->clear_Domain(dominio);
    }

    // ================================
    // SIZE
    // ================================
    int size() {
        return cantidad;
    }

    // ================================
    // CLEAR
    // ================================
    void clear() {
        for (int i = 0; i < tamanio; i++) {
            tabla[i].ocupado = false;
            tabla[i].borrado = false;
            tabla[i].siguiente = -1;
        }
        cantidad = 0;
    }
};
