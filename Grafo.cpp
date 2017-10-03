#include <vector>
#include <list>
#include "iostream"
#include "Grafo.h"

using namespace std;

	Grafo::Grafo(const int & v){		
		for (int i=0; i<v; i++)
			vertices.push_back(info);
	}

	Grafo::Grafo(const Grafo & otroGrafo){

	}

	Grafo::~Grafo(){

	}


	Grafo & Grafo::operator = (const Grafo & otroGrafo){


	}

	// Devuelve true si la cantidad de vértices es cero
	bool Grafo::esta_vacio() const{
		if (vertices.size() == 0)
			return true;
		else
			return false;
	}

	// Indica la cantidad de vértices del grafo
	int Grafo::devolver_longitud() const{
		return vertices.size();
	}


	bool Grafo::existe_vertice(int vertice) const{
		if ((vertices.size() - 1) >= vertice)
			return true;
		else
			return false;
	}

	bool Grafo::existe_arco(int origen, int destino) const{
		std::list<Arco> copia_lista; 
		copia_lista= vertices.at(origen).lista_arcos;
		list<Arco>::iterator un_iterador= copia_lista.begin();

		while (un_iterador != copia_lista.end() && (*un_iterador).Devolver_destino() != destino)
			un_iterador++;

		if ((*un_iterador).Devolver_destino() == destino)
			return true;
		else
			return false;
	}


	// PRE CONDICION: existe_arco(origen, destino)
	int Grafo::costo_arco(int origen, int destino) const{
		std::list<Arco> copia_lista= vertices.at(origen).lista_arcos;
		
		if (this-> existe_arco(origen, destino)){
			list<Arco>::iterator un_iterador= copia_lista.begin();
			while (un_iterador != copia_lista.end() && (*un_iterador).Devolver_destino() != destino)
				un_iterador++;
			return (*un_iterador).Devolver_costo();
		}else{
			return 0;  	// PREGUNTAR si la precondicion no se evalua en el MAIN???
						// porque asi devuelve 0 como costo!!!
		}
		

	}


	void Grafo::devolver_vertices(list<int> & listado_vertices) const{
		listado_vertices.clear();
		int longitud= vertices.size();
		for (int i=0; i<longitud; i++)
			listado_vertices.push_back(i);

	}

	void Grafo::devolver_adyacentes(int origen, list<Arco> & adyacentes) const{
		adyacentes.clear();
		adyacentes= vertices.at(origen).lista_arcos;
	}

	void Grafo::agregar_vertice(int vertice){
		// si quisiera algun nombre en especia deberia
		// llevar aparte un arreglito con los nombres y listo
		// por defecto se agrega un vertice al final:
		lista_arcos.clear();
		vertices.push_back(info);

	}

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void Grafo::eliminar_vertice(int vertice){
		//en 2 partes:

		// elimina los arcos que tienen como destino ese vertice 
		// revisando c/vertice


		// despues elimina el vertice
		// ojo que aca va a cambiar el tamaño del vector y por lo tanto
		// va a cambiar el destino de todos los arcosposteriores a ese numero de todos los vertices!
		// 2 estrategias: cambio todos los destinos de todos los arcos
		// o agrego un struct con 2 campor: nombre(id) y activo/inactivo para los eliminados

		// PREGUNTAR
	}


	// PRE CONDICION: existeArco(origen, destino)
	void Grafo::modificar_costo_arco(int origen, int destino, const int &costo){
		std::list<Arco> copia_lista= vertices.at(origen).lista_arcos;
		
		if (this-> existe_arco(origen, destino)){
			list<Arco>::iterator un_iterador= copia_lista.begin();
			
			// avanza el iterador hasta q encuentra el arco en cuestion
			while (un_iterador != copia_lista.end() && (*un_iterador).Devolver_destino() != destino)
				un_iterador++;

			// borra el arco
			copia_lista.erase(un_iterador);

			//agrega un arco nuevo al final con el costo nuevo
			Arco arco_modificado(destino, costo);
			copia_lista.push_back(arco_modificado);

			// reemplaza la lista vieja de arcos x la nueva
			vertices.at(origen).lista_arcos= copia_lista;
		}

	}



	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void Grafo::agregar_arco(int origen, int destino, const int & costo){
		Arco un_arco(destino, costo);
		vertices.at(origen).lista_arcos.push_back(un_arco);

	}

	// POST CONDICION: !existeArco(origen, destino)
	void Grafo::eliminar_arco(int origen, int destino){
		std::list<Arco> copia_lista= vertices.at(origen).lista_arcos;
		
		if (this-> existe_arco(origen, destino)){
			list<Arco>::iterator un_iterador= copia_lista.begin();
			
			// avanza el iterador hasta q encuentra el arco en cuestion
			while (un_iterador != copia_lista.end() && (*un_iterador).Devolver_destino() != destino)
				un_iterador++;

			// borra el arco
			copia_lista.erase(un_iterador);

			// reemplaza la lista vieja de arcos x la nueva
			vertices.at(origen).lista_arcos= copia_lista;
		}

	}

	void Grafo::vaciar(){


	}