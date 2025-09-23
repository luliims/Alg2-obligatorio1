#include <string>
#include <iostream>
#include <math.h>
using namespace std;

struct Asociacion
{
	string clave;
	int valor;
	Asociacion(string unaClave, int unValor) : clave(unaClave), valor(unValor){};
};

class TablaHashCerrada_Agenda
{
private:
	Asociacion **array;
	int tamanio;
	int cantidadDeElementos;

	int siguientePrimo(int N)
	{
		// TODO: Implementar siguientePrimo
		return N;
	}

	float factorDeCarga()
	{
		return (float)this->cantidadDeElementos / this->tamanio;
	}

	int fnHash(string clave)
	{
		int sum = 0;
		for (int k = 0; k < clave.length(); k++)
			sum = sum + int(clave[k]);
		return sum;
	}

	// solo para doble hash
	int fnHash2(string clave)
	{
		return clave.length();
	}

	void rehash()
	{
		// TODO: Implementar rehash
	}

	void insertar(Asociacion **arr, int arrSize, string unaClave, int unValor)
	{
		int i = 0;
		int inserte = false;

		while (!inserte)
		{
			int hashValue = posicionTentativa(i, unaClave);
			unsigned int pos = normalizar(hashValue);
			// En una determinada posicion del arreglo, se almacena un puntero a una asociacion (clave, valor) y existen 3 posibles casos:
			// 1. La posicion esta vacia
			// 2. La posicion esta ocupada por una asociacion con la misma clave
			// 3. La posicion esta ocupada por una asociacion con una clave distinta
			if (arr[pos] == NULL) // 1. La posicion esta vacia
			{
				arr[pos] = new Asociacion(unaClave, unValor);
				this->cantidadDeElementos++;
				inserte = true;
			}
			else if (arr[pos]->clave.compare(unaClave) == 0) // 2. La posicion esta ocupada por una asociacion con la misma clave
			{
				arr[pos]->valor = unValor;
				inserte = true;
			}
			else // 3. La posicion esta ocupada por una asociacion con una clave distinta, se debe realizar otro intento
			{
				i++;
			}
		}
	}

	int normalizar(int hashValue){
		return hashValue % this->tamanio;
	}

	int posicionTentativa(int i, string clave)
	{
		//Lineal
		//return fnHash(unaClave) + i;

		//Cuadratico
		//return (int)(fnHash(unaClave) + pow(i, 2));

		//Doble Hash
		return (int)(this->fnHash(clave) + i*this->fnHash2(clave));
	}

public:
	TablaHashCerrada_Agenda(int tamaniInicial)
	{
		this->tamanio = this->siguientePrimo(tamaniInicial);
		this->cantidadDeElementos = 0;
		array = new Asociacion *[this->tamanio]();
	}

	void insertar(string unaClave, int unValor)
	{
		this->insertar(this->array, this->tamanio, unaClave, unValor);
		if (this->factorDeCarga() > 0.5) this->rehash();
	}

	void imprimir()
	{
		cout << endl;
		for (int i = 0; i < this->tamanio; i++)
		{
			cout << "[ ";
			Asociacion *aux = array[i];
			if (aux != NULL)
			{
				cout << aux->clave << "/" << aux->valor << " ";
			}
			cout << "]" << endl;
		}
		cout << endl
				 << "Factor de carga: " << this->factorDeCarga() << endl;
	}
};

