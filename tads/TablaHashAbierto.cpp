#ifndef TABLA_HASH_ABIERTA // Evitan que el header se incluya dos veces en la misma TU (traduction unit). Si ya está definido TABLA_HASH, no se vuelve a compilar este archivo.
#define TABLA_HASH_ABIERTA
#include <string>
#include <iostream>
using namespace std;

struct NodoLista
{
	string clave;
	int valor;
	string dom;
	string path;
	string title;
	int time;
	NodoLista *sig;
	NodoLista(string unaClave, int unValor, string aDom, string aPath, string aTitle, int aTime) : clave(unaClave), valor(unValor), dom(aDom), path(aPath), title(aTitle), time(aTime), sig(0){};
	NodoLista(string unaClave, int unValor, string aDom, string aPath, string aTitle, int aTime, NodoLista *unSig) : clave(unaClave), valor(unValor), title(aTitle), time(aTime), sig(unSig){};
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
		int nuevoTam = this->tamanio * 2;
		Lista* nuevoArr = new Lista[nuevoTam]();
		for (int i = 0; i < this->tamanio; i++){
			NodoLista* ptr = arrList[i];
			while (ptr != nullptr){
				NodoLista* sig = ptr->sig;
				int posNuevo = abs(this->fnHash(ptr->clave)) % nuevoTam;
				ptr->sig = nuevoArr[posNuevo];
				nuevoArr[posNuevo] = ptr;
				ptr = sig;
			}
		}
		delete[] arrList;
		arrList = nuevoArr;
		this->tamanio = nuevoTam;
	}

	float factorDeCarga()
	{
		return (float)this->cantidadDeElementos / this->tamanio;
	}

	// Retorna true si la clave ya existe
	bool insertarRecusrivo(string unaClave, int unValor, string dom, string path, string aTitle, int aTime, NodoLista *&ptr)
	{
		if (ptr == NULL)
		{
			ptr = new NodoLista(unaClave, unValor, dom, path, aTitle, aTime);
			return false;
		}
		else
		{
			if (ptr->dom == dom && ptr->path == path){ //falta que actualice el orden
				ptr->valor = unValor;
				ptr->title = aTitle;
				ptr->time = aTime;
				return true; 
			}
			else return insertarRecusrivo(unaClave, unValor, dom, path, aTitle, aTime, ptr->sig);
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

	void insertar(string unaClave, int unValor, string aDom, string aPath, string aTitle, int aTime)
	{
		int pos = abs(this->fnHash(unaClave)) % this->tamanio;
		if (!this->insertarRecusrivo(unaClave, unValor, aDom, aPath, aTitle, aTime, arrList[pos])) this->cantidadDeElementos++;
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
		for (int i = 0; i < this->tamanio; i++){
			NodoLista* ptr = arrList[i];
			while (ptr != nullptr)
			{
				NodoLista* aux = ptr;
				ptr = ptr->sig;
				delete aux;
			}
		}
		delete[] arrList;
	}

	void eliminar(string unaClave)
	{
		int pos = abs(this->fnHash(unaClave)) % this->tamanio;
		NodoLista* ptr = arrList[pos];
		NodoLista* prev = nullptr;

		while (ptr != nullptr){
			if (ptr->clave == unaClave){
				if (prev == nullptr){
					arrList[pos] = ptr->sig;
				}
				else{
					prev->sig = ptr->sig;
				}
				delete ptr;
				this->cantidadDeElementos--;
				return;
			}
			prev = ptr;
			ptr = ptr->sig;
    	}
	}

	int buscar(string unaClave)
	{
		int pos = abs(this->fnHash(unaClave)) % this->tamanio;
		NodoLista* ptr = arrList[pos];
		while (ptr != nullptr){
			if (ptr->clave == unaClave)
				return ptr->valor;
			ptr = ptr->sig;
		}
		return -1;
	}

	//retorna el nodo entero en lugar de solo el valor
	NodoLista* buscarNodo(string dominio, string path) {
		for (int i = 0; i < this->tamanio; i++) {
			NodoLista* nodo = arrList[i];
			while (nodo != nullptr) {
				if (nodo->dom == dominio && nodo->path == path)
					return nodo;
				nodo = nodo->sig;
			}
		}
		return nullptr;
	}

	string getTitle(NodoLista* nodo){
		return nodo->title;
	}

	int getTime(NodoLista* nodo){
		return nodo->time;
	}

	int getSize(){
		return this->cantidadDeElementos;
	}

	int contarDominio(string dominio){
		int cont = 0;
		for (int i = 0; i < tamanio; i++){
			NodoLista* nodo = arrList[i];
			while (nodo != nullptr){
				if (nodo->dom == dominio)
					cont++;
				nodo = nodo->sig;
			}
		}
		return cont;
	}

	void limpiarDominio(string dominio) {
		int i = 0;
		while(i < this->tamanio){
			NodoLista* nodo = arrList[i];
			NodoLista* prev = nullptr;
			while (nodo != nullptr) {
				if (nodo->dom == dominio){
					NodoLista* aBorrar = nodo;
					if (prev == nullptr){
						arrList[i] = nodo->sig;
					}
					else{
						prev->sig = nodo->sig;
					}
					nodo = nodo->sig;
					delete aBorrar;
					this->cantidadDeElementos--;
				} 
				else{
					prev = nodo;
					nodo = nodo->sig;
				}
			}
			i++;
		}
	}

	string listarDominio(string dominio) {
		string dev = "";
		for (int i = 0; i < this->tamanio; i++) {
			NodoLista* nodo = arrList[i];
			while (nodo != nullptr) {
				if (nodo->dom == dominio){
					dev =nodo->path + " " + dev;
				}
				nodo = nodo->sig;
			}
		}
		return dev;
	}


	void limpiarTotal(){
		int i = 0;
		while(i < this->tamanio){
			NodoLista* ptr = arrList[i];
			while (ptr != nullptr){
				NodoLista* aux = ptr;
				ptr = ptr->sig;
				delete aux;
			}
			arrList[i] = nullptr; 
			i++;
		}
		this->cantidadDeElementos = 0;
	}

};

#endif