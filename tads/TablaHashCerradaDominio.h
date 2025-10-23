#ifndef TABLA_HASH_CERRADA_DOMINIO_H
#define TABLA_HASH_CERRADA_DOMINIO_H

#include <string>
using namespace std;

struct DominioEntry {
    string dominio;
    int count;
    int headIndex;
    bool ocupado;
    bool borrado;

    DominioEntry();    
    
};

class TablaHashCerradaDominio {
private:
    DominioEntry* tabla;
    int tamanio;
    int cantidad;

    int fnHash1(const string& clave);    
    int fnHash2(const string& clave);
    int posicionTentativa(int intento, const string& clave);
    int buscarDominio(const string& dominio);

public:
    TablaHashCerradaDominio(int tam = 101);
    ~TablaHashCerradaDominio();

    int asegurarDominio(const string& dominio);
    int obtenerInicio(const string& dominio);
    void establecerInicio(const string& dominio, int head);
    void incrementarCount(const string& dominio);
    void decrementarCount(const string& dominio);
    int count_Domain(const string& dominio);
    void clear_Domain(const string& dominio);
    void clear();
};

#endif
