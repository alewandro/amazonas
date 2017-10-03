#include <iostream>
#include "Arco.h"
#include "Grafo.h"
#include <list>
#include <set>
#include <math.h>

using namespace std;

/* 
TABLERO: 
 tablero de 10 x 10
 para usar costo arco numerico (int costo)
 paso todo a numeros
 
 (A B C D E F G H I J) no se usan letras, solo numeros  
  0 1 2 3 4 5 6 7 8 9
9       A1    A2
8
7
6 A3                A4
5
4
3 R3                R4
2
1
0       R1    R2
  0 1 2 3 4 5 6 7 8 9
 (A B C D E F G H I J)  

los codigos de las fichas serian:
R1 = 100		A1 = 500
R2 = 200		A2 = 600
R3 = 300		A3 = 700
R4 = 400		A4 = 800

x = 900

JUGADA:  ficha+casillero_destino(x,y)
por ejemplo: 108  seria reina roja N°1 va a casilla 0,8 
por ejemplo: 934  seria flecha en casilla 3,4 --> (columna 3, fila 4)

entonces: 
934 mod 10 --> y= 4
(934 mod 100)/10 --> x=3
934/100 --> ficha= 9

ESTADO= SET<int> de valores mismo esquema: ficha+casillero
		tambien podria ser una lista... ver complejidad

JUGADA VALIDA: calcula todas las jugadas


*/

bool casilla_ocupada(set<int> &estado, int columna, int fila){
	
	int casillero= columna * 10 + fila;

	if (estado.count(casillero + 100) ||    // busca R1
		estado.count(casillero + 200) ||    // busca R2
		estado.count(casillero + 300) ||    // busca R3
		estado.count(casillero + 400) ||    // busca R4
		estado.count(casillero + 500) ||    // busca A1
		estado.count(casillero + 600) ||    // busca A2
		estado.count(casillero + 700) ||    // busca A3
		estado.count(casillero + 800) ||    // busca A4
		estado.count(casillero + 900) ||)   // busca X
			return true;

	return false;	

}

void jugadas_validas(set<int> &estado, int ubicacion, set<int> &jug_validas){
	// ubicacion es ficha+x+y   (ficha+columna+fila)
	// 123, 547, etc a las que chequearle las jugadas validas

	int fila= ubicacion % 10;
	int columna= ((ubicacion - fila) mod 100)/10;
	int ficha= ubicacion - fila - columna * 10;   // 100, 200, etc

	jug_validas.clear();
	
	//tiene 8 direcciones para recorrer!

	it_col= columna + 1;		// porque en columna esta la ficha
	while ( it_col <=9 && !casilla_ocupada(estado, columna, fila)){
		jug_validas.insert(ficha + it_col*10 + fila);
		it_col++;
	}

	it_col= columna - 1;		// porque en columna esta la ficha
	while ( it_col >=0 && !casilla_ocupada(estado, columna, fila)){
		jug_validas.insert(ficha + it_col*10 + fila);
		it_col--;
	}

	it_fila= fila + 1;			// porque en fila esta la ficha
	while ( it_fila <=9 && !casilla_ocupada(estado, columna, fila)){
		jug_validas.insert(ficha + columna + it_fila);
		it_fila++;
	}

	it_fila= fila - 1;			// porque en fila esta la ficha
	while ( it_fila >=0 && !casilla_ocupada(estado, columna, fila)){
		jug_validas.insert(ficha + columna + it_fila);
		it_fila--;
	}

	// completar las diagonales!!

}




int main(){
	set<int> estado;
	// define estado inicial: ubicacion de las 4 reinas de cada color
	estado= {130, 260, 303, 493, 539, 669, 707, 897};


/*

	int fichas;			// la cantidad de ficha al inicio
	int a;	 		// accion: n° de fichas a quitar.  1<= a <=3

	int utilidad; 	// utilidad es igual a la cantidad de fichas de la ultima accion


	cout << endl << "Ingrese la cantidad de fichas de la pila: ";
	cin >> fichas; 
	cout << endl;
	for (int i= fichas; i>= 0; i--)
		cout << i << endl;
	cout << endl;

	// 1)
	// Generación del árbol de juego (espacio de búsqueda). Se
	// generarán todos los nodos hasta llegar a un estado terminal.

	// la cantidad de nodos seria sumatoria desde i=0 hasta i=p-1 de a^i
	Grafo arbol_dejuego( (1-pow(3, fichas)) / (1-3) );
	cout << "cantidad de nodos: " << arbol_dejuego.devolver_longitud() <<endl;

	/* c/nodo del grafo tiene esta estructura:
				struct nodo{
				int estado;
				int utilidad;
				std::list<Arco> lista_arcos;	
				};
	*/


//	arma_arbol(arbol_dejuego, fichas);


	// 2)
	// Calcular los valores de la función de evaluación para cada
	// hoja del árbol.

	// 3)
	// Calcular el valor de un nodo interior a partir del valor de sus
	// hijos.


	// 4) 
	// Elegir la jugada conveniente a partir de estos valores.
	




	return 0;
}