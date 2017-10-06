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

JUGADA VALIDA: calcula todas las jugadas posibles


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

//	string tablero("   10 | v : v : v : v : v : v : v : v : v : v | 10n      |_______________________________________|n    9 | v : v : v : v : v : v : v : v : v : v | 9n      |---------------------------------------|n    8 | v : v : v : v : v : v : v : v : v : v | 8n      |---------------------------------------|n    7 | v : v : v : v : v : v : v : v : v : v | 7n      |---------------------------------------|n    6 | v : v : v : v : v : v : v : v : v : v | 6n      |---------------------------------------|n    5 | v : v : v : v : v : v : v : v : v : v | 5n      |---------------------------------------|n    4 | v : v : v : v : v : v : v : v : v : v | 4n      |---------------------------------------|n    3 | v : v : v : v : v : v : v : v : v : v | 3n      |---------------------------------------|n    2 | v : v : v : v : v : v : v : v : v : v | 2n      |---------------------------------------|n    1 | v : v : v : v : v : v : v : v : v : v | 1n      o---------------------------------------on        A   B   C   D   E   F   G   H   I   Jn");
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
	cout << "  3 - mueve NegaMax" << endl;
}


//////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////




// devuelve el codigo de la ficha que esta en tal fila, tal columna. 
// devuelve -1 si no hay nada
int obtener_codigo_ficha(set<int> &estado, int columna, int fila){
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
	
	return 0;											// no encontro nada

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

// devuelve un set de posiciones validas para una ficha en un lugar(numerico)
void posiciones_validas(set<int> &estado, int codigo_o, set<int> &pos_validas){
	// ubicacion es ficha+x+y   (ficha+columna+fila)
	// 123, 547, etc a las que chequearle las jugadas validas

	int it_col, it_fila; 							// iteradores de fila y columna
	int fila= codigo_o % 10;
	int columna= ((codigo_o - fila) % 100)/10;
	int ficha= codigo_o - fila - columna * 10;   	// 100, 200, etc

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
bool destino_valido(set<int> &estado, int codigo_o, int codigo_d){

	set<int> pos_validas;
	posiciones_validas(estado, codigo_o, pos_validas);
	set<int>::iterator it= pos_validas.begin();
	
  	for (it; it!=pos_validas.end(); ++it){
    	if (codigo_d == *it) return true;
  	}

  	return false;
}


void mover_ficha(set<int> &estado, int codigo_o, int codigo_d){

	// elimina del set estado actual el origen
	// si es flecha no lo va a poder borrar
	estado.erase(codigo_o);				
	
	estado.insert(codigo_d);

}

void genera_estados_posibles(set<int> &estado, int codigo_o, list< set<int> > &lista_estados){
	set<int> estado_posible;
	set<int> pos_validas;
	set<int> disparos_validos;
	int codigo; 

	// calcula posiciones validas de movida para la pieza
	posiciones_validas(estado, codigo_o, pos_validas);
	cout << "posiciones_validas para " << codigo_o << " : " << pos_validas.size() << endl;

	// para c/jugada posible mueve la ficha
	set<int>::iterator it= pos_validas.begin();
	for (it; it!=pos_validas.end(); it++){
		estado_posible= estado;								// copia el estado original y trabaja con la copia
		mover_ficha(estado_posible, codigo_o, *it);

		// disparos validos posibles EN ese estado posible
		codigo= *it/100;									// por ser int, me da el codigo de ficha
		codigo= codigo * 100;					
		codigo = *it - codigo + 900;						// codigo disparo
		posiciones_validas(estado_posible, codigo, disparos_validos);
		cout << "disparos validos para posicion " << codigo << " --> " << disparos_validos.size() << endl;


		// para c/disparo posible genera un estado y lo agrega a la lista
		set<int>::iterator it_disparo= disparos_validos.begin();
		for (it_disparo; it_disparo!=disparos_validos.end(); it_disparo++){		
			estado_posible.insert(*it_disparo);  			//inserta un disparo en estado
			lista_estados.push_back(estado_posible);
			estado_posible.erase(*it_disparo);				//borra el disparo para insertar el q sigue
		}
	}

	cout << "lista de estado_posible: " << lista_estados.size() << endl; 
}

void jugar(set<int> &estado){

	int eleccion, fila_o, columna_o, ficha_o, fila_d, columna_d, ficha_d, codigo_o, codigo_d;		// x, y, ficha y codigo  origen / destino
	string origen, destino;
   	set<int> pos_validas;
    
    imprimir_submenu();
            		
	cin >> eleccion;

    while (eleccion != 0){
        switch (eleccion){
            case 1:{						// jugadas posibles
            		cout << "Ingrese Origen: ";
            		cin >> origen;

            		obtener_fila_columna(origen, columna_o, fila_o);
            		if (columna_o == -1 || fila_o == -1){
            			cout << "Fila o Columna Incorrecta" << endl;
            			break;
            		}
            		
            		ficha_o= obtener_codigo_ficha(estado, columna_o, fila_o);
            		if (!ficha_o || ficha_o == 900){
            			cout << "No hay fichas suyas para mover en ese casillero" << endl;
            			break;
            		}
            		
            		codigo_o= ficha_o + columna_o * 10 + fila_o;
					posiciones_validas(estado, codigo_o, pos_validas);
	            	imprimir_set(pos_validas);

            	}
                break;
            case 2:{						// mover ficha
            		
            		cout << "Ingrese Origen: ";
            		cin >> origen;

            		obtener_fila_columna(origen, columna_o, fila_o);
            		if (columna_o == -1 || fila_o == -1){
            			cout << "Fila o Columna Incorrecta" << endl;
            			break;
            		}
            		
            		ficha_o= obtener_codigo_ficha(estado, columna_o, fila_o);
            		if (!ficha_o || ficha_o == 900 || ficha_o == 500 || 
            			ficha_o == 600 || ficha_o == 700 || ficha_o == 800){
            			cout << "No hay fichas suyas para mover en ese casillero" << endl;
            			break;
            		}
            		
            		codigo_o= ficha_o + columna_o * 10 + fila_o;

            		// idem para el destino
            		cout << "Ingrese Destino: ";
            		cin >> destino;

            		obtener_fila_columna(destino, columna_d, fila_d);
            		if (columna_d == -1 || fila_d == -1){
            			cout << "Fila o Columna Incorrecta" << endl;
            			break;
            		}
            		
            		ficha_d= obtener_codigo_ficha(estado, columna_d, fila_d);
            		if (ficha_d){
            			cout << "Casilla Ocupada!" << endl;
            			break;
            		}
            		
            		ficha_d= ficha_o;								// es la misma ficha que va a otro lado
            		codigo_d= ficha_d + columna_d * 10 + fila_d;

            		if (destino_valido(estado, codigo_o, codigo_d)){
	            		mover_ficha(estado, codigo_o, codigo_d);
	   					imprimir_tablero(estado);
	   				}else{
	   					cout << "Destino Inalcanzable !!";
	   					break;
	   				}

   					// flecha

	   				codigo_o= codigo_d;								// la flecha sale de la reina anterior
   					ficha_d= 1; 									// para la condicion del while

	   				while (columna_d == -1 || fila_d == -1 || ficha_d || !destino_valido(estado, codigo_o, codigo_d)){	
	            		cout << "Ingrese Destino de la Flecha: ";
	            		cin >> destino;

	            		obtener_fila_columna(destino, columna_d, fila_d);
	            		if (columna_d == -1 || fila_d == -1){
	            			cout << "Fila o Columna Incorrecta" << endl;
	            		}
	            		
	            		ficha_d= obtener_codigo_ficha(estado, columna_d, fila_d);			// chequea si esta vacia!
	            		if (ficha_d){
	            			cout << "Casilla Ocupada!" << endl;
	            		}
	            		codigo_d= ficha_o + columna_d * 10 + fila_d;
	   
	               		if (!destino_valido(estado, codigo_o, codigo_d)){
	            			cout << "Destino Inalcanzable !!" << endl;
	            		}


	            	}

            		ficha_d = 900;
            		codigo_d= ficha_d + columna_d * 10 + fila_d;
   					codigo_o= codigo_o - ficha_o + ficha_d;								// el origen de la flecha es el destino de la reina anterior
            		mover_ficha(estado, codigo_o, codigo_d);
   					imprimir_tablero(estado);
	   				
            	}
            	break;

            	case 3:{
            		list< set<int> > lista_estados;

            		// encuentra en el estado a c/reina y le genera todas las jugadas posibles
            		set<int>::iterator it= estado.begin();
            		for (it; it!= estado.end(); it++){
            			if (*it/100 == 5 || *it/100 == 6 || *it/100 == 7 || *it/100 == 8){		// identifica las reinas Azules
            				genera_estados_posibles(estado, *it, lista_estados);
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

   		imprimir_tablero(estado);
    	imprimir_submenu();

        cin >> eleccion;
	

    }



}



//////////////////////////////////////////////////////////////////////////////////////
//								MAIN												//
//////////////////////////////////////////////////////////////////////////////////////

int main(){
	set<int> estado;
	int opcion, profundidad;

	profundidad= 1; 				// por defecto
	max_reinas_propias=5;
	min_reinas_Oponente=5;

	// define estado inicial: ubicacion de las 4 reinas de cada color
	estado= {130, 260, 303, 493, 539, 669, 707, 897};

	imprimir_menu();
	cin >> opcion;

    while (opcion != 0){
        switch (opcion){
            case 1:{						// jugar
            		imprimir_tablero(estado);
            		jugar(estado);
            	}
                break;
            case 2:{						// jugar
            		//imprimir_preferencias();
					cout << string(50, '\n');
            		cout << " Preferencias" << endl;
					cout << "o---------------------------------------------------------------------o" << endl;
            		cout << "| 1 - Ingrese la Cantidad de Niveles de Analisis Deseado   |    " << profundidad << "     |" << endl;
					cout << "o---------------------------------------------------------------------o" << endl << endl;
            		cout << " Heuristica" << endl;
					cout << "o---------------------------------------------------------------------o" << endl;
            		cout << "| 2 - Maximizar Recorrido Reinas Propias                   |    5     |" << endl;
            		cout << "| 3 - Minimizar Recorrido Reinas Oponente                  |    3     |" << endl;
            		cout << "| 4 - Otro 1                                               |    1     |" << endl;
            		cout << "| 5 - Otro 2                                               |    1     |" << endl;
					cout << "o---------------------------------------------------------------------o" << endl;
            		cout << "|                                         Total Heuristica |    10    |" << endl;
					cout << "o---------------------------------------------------------------------o" << endl << endl;
            		cout << " Ingrese una Opcion: ";
            		cin >> profundidad;
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