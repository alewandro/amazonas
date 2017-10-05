#include <iostream>
#include "Arco.h"
#include "Grafo.h"
#include <list>
#include <set>
#include <math.h>

using namespace std;

/*
///////////////////////////////////////
PROBLEMAS:

- ENTRA EN LOOP AL INGRESAR VALOR ALFANUMERICO EN SUBMENU JUGAR!!

- FALTA CHEQUEAR QUE LA PIEZA a mover LE PERTENEZCA AL JUGADOR!!
(que no pueda mover ni las azules ni las x)

- Mejorar disparo de flecha!!

///////////////////////////////////////


 
TABLERO: 
 tablero de 10 x 10  (la representacion va de 0 a 9)
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


void imprimir_menu(){
	cout << string(50, '\n');

/*
    :::     ::::    ::::      :::     :::::::::  ::::::::  ::::    :::     :::      ::::::::  
  :+: :+:   +:+:+: :+:+:+   :+: :+:        :+:  :+:    :+: :+:+:   :+:   :+: :+:   :+:    :+: 
 +:+   +:+  +:+ +:+:+ +:+  +:+   +:+      +:+   +:+    +:+ :+:+:+  +:+  +:+   +:+  +:+        
+#++:++#++: +#+  +:+  +#+ +#++:++#++:    +#+    +#+    +:+ +#+ +:+ +#+ +#++:++#++: +#++:++#++ 
+#+     +#+ +#+       +#+ +#+     +#+   +#+     +#+    +#+ +#+  +#+#+# +#+     +#+        +#+ 
#+#     #+# #+#       #+# #+#     #+#  #+#      #+#    #+# #+#   #+#+# #+#     #+# #+#    #+# 
###     ### ###       ### ###     ### #########  ########  ###    #### ###     ###  ######## 


     /\                                                            
    /  \     _ __ ___     __ _   ____   ___    _ __     __ _   ___ 
   / /\ \   | '_ ` _ \   / _` | |_  /  / _ \  | '_ \   / _` | / __|
  / ____ \  | | | | | | | (_| |  / /  | (_) | | | | | | (_| | \__ \
 /_/    \_\ |_| |_| |_|  \__,_| /___|  \___/  |_| |_|  \__,_| |___/
*/


	cout << "       d8888                                                                    " << endl; 
	cout << "      d88888                                                                    " << endl; 
	cout << "     d88P888                                                                    " << endl; 
	cout << "    d88P 888 88888b.d88b.   8888b.  88888888  .d88b.  88888b.   8888b.  .d8888b " << endl; 
	cout << "   d88P  888 888  888  88b      88b    d88P  d88  88b 888  88b      88b 88K     " << endl; 
	cout << "  d88P   888 888  888  888 .d888888   d88P   888  888 888  888 .d888888  Y8888b." << endl; 
	cout << " d8888888888 888  888  888 888  888  d88P    Y88..88P 888  888 888  888      X88" << endl; 
	cout << "d88P     888 888  888  888  Y888888 88888888   Y88P   888  888  Y888888  88888P " << endl; 
	cout << endl;
	cout << endl;
	cout << "                           1 - Jugar" << endl;
	cout << endl;
	cout << "                           2 - Modificar Heuristica" << endl;
	cout << endl;
	cout << "                           0 - Salir" << endl;
	cout << string(10, '\n');
}

/*
void imprimir_tablero(set<int> &estado){
	
	cout << string(50, '\n');

	cout << "        A   B   C   D   E   F   G   H   I   J" << endl;
	cout << "      o---------------------------------------o" << endl;
	cout << "   10 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    9 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    8 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    7 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    6 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    5 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    4 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    3 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    2 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    1 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      |---------------------------------------|" << endl;
	cout << "    0 |   :   :   :   :   :   :   :   :   :   |" << endl;
	cout << "      o---------------------------------------o" << endl;

}
*/

void imprime_ficha(set<int> &estado_actual, int casillero){
	int columna= casillero % 10;
	int fila= (casillero - columna) / 10; 
	
	int R1= 100 + columna * 10 + fila;
	int A1= 500 + columna * 10 + fila;
	int X=  900 + columna * 10 + fila;

	for (int i= 0; i<=3; i++)						// chequea las 4 reinas rojas
		if (estado_actual.count(R1 + i * 100)){
			cout << "R";
			return;
		}

	for (int i= 0; i<=3; i++)						// chequea las 4 reinas azules
		if (estado_actual.count(A1 + i * 100)){
			cout << "A";
			return;
		}

	if (estado_actual.count(X))
		cout << "x";
	else
		cout << " ";

}

void imprimir_tablero(set<int> &estado_actual){ 
	int casillero= 109;
	cout << string(50, '\n');

	cout << "        A   B   C   D   E   F   G   H   I   J" << endl;
	cout << "      o---------------------------------------o" << endl;

	string tablero("   10 | v : v : v : v : v : v : v : v : v : v |n      |---------------------------------------|n    9 | v : v : v : v : v : v : v : v : v : v |n      |---------------------------------------|n    8 | v : v : v : v : v : v : v : v : v : v |n      |---------------------------------------|n    7 | v : v : v : v : v : v : v : v : v : v |n      |---------------------------------------|n    6 | v : v : v : v : v : v : v : v : v : v |n      |---------------------------------------|n    5 | v : v : v : v : v : v : v : v : v : v |n      |---------------------------------------|n    4 | v : v : v : v : v : v : v : v : v : v |n      |---------------------------------------|n    3 | v : v : v : v : v : v : v : v : v : v |n      |---------------------------------------|n    2 | v : v : v : v : v : v : v : v : v : v |n      |---------------------------------------|n    1 | v : v : v : v : v : v : v : v : v : v |n      o---------------------------------------on");

	for (string::iterator it=tablero.begin(); it!=tablero.end(); ++it){
    	if (*it == 'n')
    		cout << endl;
    	else 
    		if (*it == 'v'){
    			if (casillero % 10 == 9)
    				casillero= casillero - 19;	
    			else 
    				casillero++;
    			imprime_ficha(estado_actual, casillero);

    		}else{
    			cout << *it;
    		}

	}

	cout << endl;

}

// devuelve en notacion el codigo numerico
string devolver_notacion(int set_member){
	string notacion;
	int fila= set_member % 10;
	int columna= ((set_member - fila) % 100)/10;
	int ficha= (set_member - fila - columna * 10)/100;

	string fichas[]= {"", "R1", "R2", "R3", "R4", "A1", "A2", "A3", "A4", "x"};
	string columnas[]= {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
	string filas[]= {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

	notacion= fichas[ficha];
	notacion += columnas[columna];
	notacion += filas[fila];

	return notacion;
}

/*
int devolver_codigo_numerico(string notacion){
	int codigo_numerico;



	return codigo_numerico;
}
*/
void imprimir_set(set<int> un_set){
	set<int>::iterator it= un_set.begin();
	
  	for (it; it!=un_set.end(); ++it)
    	cout << devolver_notacion(*it) << " - ";	// cout << " " << *it;
  	cout << endl;
}

void imprimir_submenu(){
	cout << "  0 - salir" << endl;
	cout << "  1 - jugadas posibles" << endl;
	cout << "  2 - mover pieza" << endl;
	cout << "  3 - disparar flecha" << endl;
}


//////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////




// devuelve el codigo de la ficha que esta en tal fila, tal columna. 
// devuelve -1 si no hay nada
int devolver_codigo_ficha(set<int> &estado, int columna, int fila){
	int casillero= columna * 10 + fila;

	if (estado.count(casillero + 100)) return 100;		// busca R1
	if (estado.count(casillero + 200)) return 200;		// busca R2
	if (estado.count(casillero + 300)) return 300;		// busca R3
	if (estado.count(casillero + 400)) return 400;		// busca R4
	if (estado.count(casillero + 500)) return 500;		// busca A1
	if (estado.count(casillero + 600)) return 600;		// busca A2
	if (estado.count(casillero + 700)) return 700;		// busca A3
	if (estado.count(casillero + 800)) return 800;		// busca A4
	if (estado.count(casillero + 900)) return 900;		// busca X
	
	return -1;											// no encontro nada

}

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
		estado.count(casillero + 900))   	// busca X
			return true;

	return false;	

}

void obtener_fila_columna(string &notacion, int &columna, int &fila){

	string columnas[]= {"Aa", "Bb", "Cc", "Dd", "Ee", "Ff", "Gg", "Hh", "Ii", "Jj"};
	string filas[]= {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

	columna= -1;
	fila= -1;
	
	for (int i=0; i<10; i++){
		if (columnas[i][0] == notacion[0])
			columna= i;
	}

	for (int i=0; i<10; i++){
		if (columnas[i][1] == notacion[0]){
			columna= i;
			notacion[0]= columnas[i][0];
		}
	}

	for (int i=0; i<10; i++){
		if (filas[i].substr(0) == notacion.substr(1))
			fila= i;
	}

}

// devuelve el codigo numerico de una pieza en un lugar tipo notacion
// devuelve -1 si fila o columna estan mal
// devuelve -2 si la casilla esta vacia

int devolver_codigo(set<int> &estado, string &notacion){		// lo pasa x ref para corregirlo si es minuscula
	int columna, fila;
	
	obtener_fila_columna(notacion, columna, fila);
	
	if (columna == -1 || fila == -1)
		return -1;									// columna o fila incorrectos

	int ficha= devolver_codigo_ficha(estado, columna, fila); 
	
	if (ficha == -1)
		return -2;									// no hay nada en esa posicion 
	else
		return ficha + columna * 10 + fila;			// retorna el codigo numerico completo
	

}


// devuelve un set de posiciones validas para una ficha en un lugar(numerico)
void posiciones_validas(set<int> &estado, int ubicacion, set<int> &pos_validas){
	// ubicacion es ficha+x+y   (ficha+columna+fila)
	// 123, 547, etc a las que chequearle las jugadas validas

	int it_col, it_fila; 							// iteradores de fila y columna
	int fila= ubicacion % 10;
	int columna= ((ubicacion - fila) % 100)/10;
	int ficha= ubicacion - fila - columna * 10;   	// 100, 200, etc

	pos_validas.clear();
	
	//recorre 4 rectas: arriba, abajo, derecha, izquierda

	it_col= columna + 1;		// porque en columna esta la ficha
	while ( it_col <=9 && !casilla_ocupada(estado, it_col, fila)){
		pos_validas.insert(ficha + it_col*10 + fila);
		it_col++;
	}

	it_col= columna - 1;		// porque en columna esta la ficha
	while ( it_col >=0 && !casilla_ocupada(estado, it_col, fila)){
		pos_validas.insert(ficha + it_col*10 + fila);
		it_col--;
	}

	it_fila= fila + 1;			// porque en fila esta la ficha
	while ( it_fila <=9 && !casilla_ocupada(estado, columna, it_fila)){
		pos_validas.insert(ficha + columna * 10 + it_fila);
		it_fila++;
	}

	it_fila= fila - 1;			// porque en fila esta la ficha
	while ( it_fila >=0 && !casilla_ocupada(estado, columna, it_fila)){
		pos_validas.insert(ficha + columna * 10 + it_fila);
		it_fila--;
	}

	//recorre 4 diagonales
	
	it_fila= fila + 1;			// porque en fila esta la ficha
	it_col= columna + 1;		// porque en columna esta la ficha
	while ( it_col <=9 && it_fila <=9 && !casilla_ocupada(estado, it_col, it_fila)){
		pos_validas.insert(ficha + it_col*10 + it_fila);
		it_fila++;
		it_col++;
	}

	it_fila= fila - 1;			// porque en fila esta la ficha
	it_col= columna + 1;		// porque en columna esta la ficha
	while ( it_col <=9 && it_fila >=0 && !casilla_ocupada(estado, it_col, it_fila)){
		pos_validas.insert(ficha + it_col*10 + it_fila);
		it_fila--;
		it_col++;
	}

	it_fila= fila - 1;			// porque en fila esta la ficha
	it_col= columna - 1;		// porque en columna esta la ficha
	while ( it_col >=0 && it_fila >=0 && !casilla_ocupada(estado, it_col, it_fila)){
		pos_validas.insert(ficha + it_col*10 + it_fila);
		it_fila--;
		it_col--;
	}

	it_fila= fila + 1;			// porque en fila esta la ficha
	it_col= columna - 1;		// porque en columna esta la ficha
	while ( it_col >=0 && it_fila <=9 && !casilla_ocupada(estado, it_col, it_fila)){
		pos_validas.insert(ficha + it_col*10 + it_fila);
		it_fila++;
		it_col--;
	}
}


// busca el destino en el set de jugadas posibles
bool destino_valido(set<int> &estado, int codigo_origen, string destino){
	// string notacion;
	int codigo_destino, columna, fila, ficha;

	obtener_fila_columna(destino, columna, fila);
	ficha= devolver_codigo_ficha(estado, (codigo_origen % 100 - codigo_origen % 10)/10, codigo_origen % 10);
	codigo_destino= ficha + columna * 10 + fila;

	set<int> pos_validas;
	posiciones_validas(estado, codigo_origen, pos_validas);
	set<int>::iterator it= pos_validas.begin();
	
  	for (it; it!=pos_validas.end(); ++it){
    	// notacion= devolver_notacion(*it);
    	if (codigo_destino == *it) return true;
  	}

  	return false;
}


void mover_ficha(set<int> &estado_actual, int origen, string destino){
	int columna, fila;

	// elimina del set estado actual el origen
	// si es flecha no lo va a poder borrar
	estado_actual.erase(origen);				
	
	obtener_fila_columna(destino, columna, fila);

	int ficha= origen - origen % 100;

	estado_actual.insert(ficha + columna * 10 + fila);

}

void jugar(set<int> &estado_actual){

   	set<int> pos_validas;
    
    imprimir_submenu();  // do, codigo_origen, pos_validas);
	// set<int>::iterator it= pos_validas.begin()
            		
	int eleccion;
	cin >> eleccion;

    while (eleccion != 0){
        switch (eleccion){
            case 1:{						// jugadas posibles
            		cout << "Ingrese Origen (Letra Numero: A10): " << endl;
            		string origen;
            		cin >> origen;
            		int codigo= devolver_codigo(estado_actual, origen);
            		cout << " el codigo de su notacion es: " << codigo << endl;
            		if (codigo > -1){
	            		posiciones_validas(estado_actual, codigo, pos_validas);
	            		imprimir_set(pos_validas);
	            	}else{
	            		cout << "Codigo Incorrecto o no existen fichas en ese lugar ! " << endl;
	            	}

            	}
                break;
            case 2:{						// mover ficha
            		cout << "Ingrese Origen (Letra Numero: A10): ";
            		string posicion;
            		int codigo_origen, destino, fil, col, ficha;

            		cin >> posicion;
            		codigo_origen= devolver_codigo(estado_actual, posicion);
            		cout << " el codigo de su notacion es: " << codigo_origen << endl;
            		if (codigo_origen == -1){
	            		cout << "Codigo Incorrecto o no existen fichas en ese lugar ! " << endl;
	            		break;
	            	}
	            	//
	            	// FALTA CHEQUEAR QUE SEA UNA PIEZA QUE LE PERTENEZCA AL JUGADOR!!

	            	cout << "Ingrese Destino (Letra Numero: A10): " ;

            		cin >> posicion;
            		destino= devolver_codigo(estado_actual, posicion);
            		cout << destino << endl;
            		if (destino == -1){
	            		cout << "Fila o Columna Incorrectos! " << endl;
	            		break;
	            	}
	            	
	            	// posiciones_validas(estado_actual, codigo_origen, pos_validas); // crea set de validas para posicion origen
	            	// imprimir_set(pos_validas);
	            	
	            	// cout << destino_valido(estado_actual, codigo_origen, posicion);

	            	if (destino_valido(estado_actual, codigo_origen, posicion)){
	            		mover_ficha(estado_actual, codigo_origen, posicion);
   						imprimir_tablero(estado_actual);
   						
   						obtener_fila_columna(posicion, col, fil);
   						ficha= devolver_codigo_ficha(estado_actual, col, fil);
   						codigo_origen= ficha + col * 10 + fil; 						//la flecha sale del lugar de la reina
   						cout << "origen flecha " << posicion << " " << col << fil << endl;
   						
   						destino= -1; // setea para el while
   						while (destino < 0){
	   						cout << "Ingrese Destino de la Flecha: ";
	   						cin >> posicion;
		            		
		            		destino= devolver_codigo(estado_actual, posicion);
		            		
		            		if (destino == -1){
			            		cout << "Fila o Columna Incorrectos! (-1)" << endl;
			            		break;
		            		}else if (destino == -2){
			            		cout << "destino flecha vacio (-2)--> ok " << endl;
			            	}
			            	if (destino_valido(estado_actual, codigo_origen, posicion)){
				            	codigo_origen= codigo_origen - ficha + 900; 				// transforma en flecha
			            		mover_ficha(estado_actual, codigo_origen, posicion);
			            	}
			            }	
	            	}
	            	
            	}
                break;	
            default:{
            	    cout <<  endl << "Opción invalida\n" << "Ingrese una nueva opción\n";
            	    //eleccion= -1;
            	}
            	break;
        	}
    	
   		cout << endl << "Presione <ENTER> para continuar..";
        cin.ignore();
        cin.ignore();

   		imprimir_tablero(estado_actual);
    	imprimir_submenu();

        cin >> eleccion;
	

    }



}



//////////////////////////////////////////////////////////////////////////////////////
//								MAIN												//
//////////////////////////////////////////////////////////////////////////////////////

int main(){
	set<int> estado_actual;

	// define estado inicial: ubicacion de las 4 reinas de cada color
	estado_actual= {130, 260, 303, 493, 539, 669, 707, 897, 965};

	imprimir_menu();
	int opcion;
	cin >> opcion;

    while (opcion != 0){
        switch (opcion){
            case 1:{						// jugar
            		imprimir_tablero(estado_actual);
            		jugar(estado_actual);
            	}
                break;
	
            default:{
            	    cout <<  endl << "Opción invalida\n" << "Ingrese una nueva opción\n";
            	}
            break;
        	}

       	imprimir_menu();

        cin >> opcion;
	

    }


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