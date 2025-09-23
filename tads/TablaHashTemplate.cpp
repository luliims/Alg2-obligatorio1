#ifndef TABLA_HASH // Evitan que el header se incluya dos veces en la misma TU (traduction unit). Si ya está definido TABLA_HASH, no se vuelve a compilar este archivo.
#define TABLA_HASH
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

// Clase que "empareja" a la clave y al valor, similar a asociacion.
// Define una clase plantilla parametrizada por tipos K (clave) y V (valor). Cada instancia concreta (p. ej. ClaveValor<string,int>) genera código propio.
template <class K, class V>
class ClaveValor
{
private:
	K clave;
	V valor;

public:
	// Constructor con ambos datos, copia unaClave y unValor a los miembros.
	// Recibe referencias no const, lo que impide pasar temporales o literales (ej. "abc", 42).
	ClaveValor(K &unaClave, V &unValor) : clave(unaClave), valor(unValor) {} 

	 // Constructor con solo la clave. No inicializa valor si V es tipo primitivo (ej. int), queda indeterminado. Riesgo de uso de basura.
	ClaveValor(K &unaClave) : clave(unaClave) {}			

	// Getters y Setters										
	K getClave() { return this->clave; }
	V getValor() { return this->valor; }
	void setClave(K nuevaClave) { this->clave = nuevaClave; }
	void setValor(V nuevoValor) { this->valor = nuevoValor; }

	//Comparación entre dos objetos ClaveValor:
	/*
	Define cómo comparar dos objetos de tipo ClaveValor. 
	Dos objetos ClaveValor se consideran iguales si y solo si sus claves son iguales. 
	*/
	bool operator==(ClaveValor otraCV) { return this->getClave() == otraCV.getClave(); } 

	// comparador entre ClaveValor y K
	/*
	Define cómo comparar un objeto ClaveValor con una clave de tipo K. 
	Un objeto ClaveValor se considera igual a una clave K si la clave del objeto ClaveValor es igual a la clave K proporcionada.
	*/
	bool operator==(K unaClave) { return this->getClave() == unaClave; }								 
};


// Plantilla de nodo lista simplemente encadenado
template <class T>
struct NodoLista
{
public:
	T dato; // guarda el dato en si dentro del nodo
	NodoLista<T> *sig;	// guarda la referencia al siguiente nodo
	NodoLista(T &unDato, NodoLista<T> *unSiguiente) : dato(unDato), sig(unSiguiente) {} // Constructor con ambos datos
	NodoLista(T &unDato) : dato(unDato), sig(0) {}	//Constructor con solo el dato, por defecto el sig es null
};


template <class K, class V>
class TablaHash
{
private:
	// La "Lista" en cada casillero sera un puntero a un NodoLista de ClaveValor
	typedef NodoLista<ClaveValor<K, V>> *NodoPtr;

	// Array principal de la estructura, cada casillero es un puntero a el nodo mencionado anteriormente
	NodoPtr *arrList;

	// Guardamos la funcion hash (ver constructor). Notar que la funcion recibe un K (clave) y retorna un int
	int (*fnHash)(K);

	// tamanio del array
	int tamanio;

	// funcion que dada un clave nos devuelve la posicion en el array donde se esta buscando/insertando/etc
	int posHash(K clave)
	{
		// usando la funcion fnHash y el tamanio del array se obtiene la posicion.
		// Nota: fnHash puede retornar un numero fuera del array por lo cual se aplica el modulo con el tamanio del array.
		int pos = abs(this->fnHash(clave)) % this->tamanio;
		return pos;
	}

	// funcion que me calcula el siguiente primo.
	int SiguientePrimo(int origen)
	{
		// TODO
		return origen;
	}

	// funcion recursiva una vez que se encuentra el casillero correspondiente. Observar: void Insertar(K clave,V el)
	void InsertarRecursivo(NodoPtr &nodo, K clave, V valor)
	{
		if (nodo == 0)
		{
			ClaveValor<K, V> aInsertar(clave, valor); // creo un nuevo ClaveValor, la variable se llama aInsertar
			nodo = new NodoLista<ClaveValor<K, V>>(aInsertar); // creo un nuevo nodo con el ClaveValor aInsertar
		}
		else if (nodo->dato == clave) 
		{
			// Si la clave ya se encuentra dentro de la tabla entonces la sustituyo por el nuevo valor
			nodo->dato.setValor(valor);
		}
		else
		{
			// Paso recursivo
			InsertarRecursivo(nodo->sig, clave, valor);
		}
	}

	// funcion recursiva para recuperar un valor
	V RecuperarRecursivo(NodoPtr nodo, K clave)
	{
		assert(nodo != 0); // si el nodo es null entonces hay un error, puede existir otro tipo de comportamiento dependiendo de la necesidad y el problema.
		if (nodo->dato == clave)
		{
			return nodo->dato.getValor(); // si la clave es igual a la que busco, retorno el valor
			// Nota: no se si es correcto retornar el valor por referencia, pero es un ejemplo. Puede permitir que desde afuera se modifique el valor.
		}
		else
		{
			// Paso recursivo
			return RecuperarRecursivo(nodo->sig, clave);
		}
	}

public:
	// IMPORTANTE: el constructor del hash recibe dos parametros, el primero es el tamanio y por ultimo la funcion hash.
	// En c++ se pueden pasar funciones como parametros. http://math.hws.edu/bridgeman/courses/331/f05/handouts/c-c++-notes.html
	// Al usar generics/templates no tenemos forma de obtener un int de un tipo K, ya que no sabemos nada de el, por lo cual,
	// pedimos una funcion hash para que sea guardada y ultizada dentro de la tabla de hash.
	TablaHash(int tamanio, int (*f)(K))
	{
		int nuevoTamanio = this->SiguientePrimo(tamanio);
		arrList = new NodoPtr[nuevoTamanio]; // instancio el array
		for (int i = 0; i < nuevoTamanio; i++)
		{
			arrList[i] = 0;
		} // inicializo el array
		this->tamanio = nuevoTamanio;
		this->fnHash = f; // IMPORTANTE: me guardo la funcion de hash para luego usar en el resto de las operaciones.
	}

	~TablaHash()
	{
		// TODO
	}

	void Insertar(K clave, V valor)
	{
		int casillero = this->posHash(clave); // Obtengo la posicion inicial, el "casillero"
		this->InsertarRecursivo(arrList[casillero], clave, valor);
	}

	void Eliminar(K clave)
	{
		// TODO
	}

	V Recuperar(K clave)
	{
		int casillero = this->posHash(clave); // Obtengo la posicion inicial, el "casillero"
		return RecuperarRecursivo(arrList[casillero], clave);
	}
};
#endif