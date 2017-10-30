#ifndef IMPRESIONES_H_INCLUDED
#define IMPRESIONES_H_INCLUDED
#include "Tablero.h"
#include <iostream>
#include <set>
#include <string>

using namespace std;

void imprimir_menu(){
	cout << string(50, '\n');
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
	cout << "                           2 - Preferencias - Heuristica" << endl;
	cout << endl;
	cout << "                           0 - Salir" << endl;
	cout << string(10, '\n');
}


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
	cout << "       _______________________________________ " << endl;

	string tablero("   10 | v | v | v | v | v | v | v | v | v | v | 10n      |___|___|___|___|___|___|___|___|___|___|n    9 | v | v | v | v | v | v | v | v | v | v | 9n      |___|___|___|___|___|___|___|___|___|___|n    8 | v | v | v | v | v | v | v | v | v | v | 8n      |___|___|___|___|___|___|___|___|___|___|n    7 | v | v | v | v | v | v | v | v | v | v | 7n      |___|___|___|___|___|___|___|___|___|___|n    6 | v | v | v | v | v | v | v | v | v | v | 6n      |___|___|___|___|___|___|___|___|___|___|n    5 | v | v | v | v | v | v | v | v | v | v | 5n      |___|___|___|___|___|___|___|___|___|___|n    4 | v | v | v | v | v | v | v | v | v | v | 4n      |___|___|___|___|___|___|___|___|___|___|n    3 | v | v | v | v | v | v | v | v | v | v | 3n      |___|___|___|___|___|___|___|___|___|___|n    2 | v | v | v | v | v | v | v | v | v | v | 2n      |___|___|___|___|___|___|___|___|___|___|n    1 | v | v | v | v | v | v | v | v | v | v | 1n      |___|___|___|___|___|___|___|___|___|___|n        A   B   C   D   E   F   G   H   I   Jn");

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


void imprimir_set(set<int> un_set){
	set<int>::iterator it= un_set.begin();

  	for (it; it!=un_set.end(); ++it)
    	cout << devolver_notacion(*it) << " - ";
  	cout << endl;
}


#endif // IMPRESIONES_H_INCLUDED
