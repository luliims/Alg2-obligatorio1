#ifndef TABLA_HASH_ABIERTA // Evitan que el header se incluya dos veces en la misma TU (traduction unit). Si ya está definido TABLA_HASH, no se vuelve a compilar este archivo.
#define TABLA_HASH_ABIERTA
#include <string>
#include <iostream>
using namespace std;

struct NodoLista
{
	string clave;
	int valor;
	NodoLista *sig;
	NodoLista(string unaClave, int unValor) : clave(unaClave), valor(unValor), sig(0){};
	NodoLista(string unaClave, int unValor, NodoLista *unSig) : clave(unaClave), valor(unValor), sig(unSig){};
};

typedef NodoLista *Lista;

class TablaHashAbierta_Agenda
{
private:
	// typedef NodoLista *Lista;
	Lista *arrList;
	int tamanio;
	int cantidadDeElementos;

	void rehash()
	{
		// TODO: Implementar rehash
	}

	float factorDeCarga()
	{
		return (float)this->cantidadDeElementos / this->tamanio;
	}

	// Retorna true si la clave ya existe
	bool insertarRecusrivo(string unaClave, int unValor, NodoLista *&ptr)
	{
		if (ptr == NULL)
		{
			ptr = new NodoLista(unaClave, unValor);
			return false;
		}
		else
		{
			if (ptr->clave == unaClave)
			{
				ptr->valor = unValor;
				return true;
			}
			else return insertarRecusrivo(unaClave, unValor, ptr->sig);
		}
	}

public:
	TablaHashAbierta_Agenda(int tamaniInicial)
	{
		this->tamanio = tamaniInicial;
		this->cantidadDeElementos = 0;
		arrList = new Lista[this->tamanio]();
	}

	int fnHash(string clave)
	{
		int sum = 0;
		for (int pos = 0; pos < clave.length(); pos++)
			sum = sum + int(clave[pos]);
		return sum;
	}

	void insertar(string unaClave, int unValor)
	{
		int pos = abs(this->fnHash(unaClave)) % this->tamanio;
		if (!this->insertarRecusrivo(unaClave, unValor, arrList[pos])) this->cantidadDeElementos++;
		if (this->factorDeCarga() > 0.7) this->rehash();
	}

	void imprimir()
	{
		for (int i = 0; i < this->tamanio; i++)
		{
			cout << "[ ] ->";
			Lista nodo = this->arrList[i];
			while (nodo != NULL)
			{
				cout << " " << nodo->clave << "/" << nodo->valor << " ->";
				nodo = nodo->sig;
			}
			cout << " null" << endl;
		}
	}

	~TablaHashAbierta_Agenda()
	{
		// TODO: Implementar destructor
	}

	void eliminar(string unaClave)
	{
		// TODO: Implementar eliminar
	}

	int buscar(string unaClave)
	{
		// TODO: Implementar buscar
		return 0;	
	}
};

#endif