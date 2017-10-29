#include <iostream>
#include "Tablero.h"
#include <list>
#include <set>
#include <math.h>
#include <stdlib.h>     // para numeros aleatorios
#include <time.h>       // para numeros aleatorios

using namespace std;

/*
*/

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


void imprimir_set(set<int> un_set){
	set<int>::iterator it= un_set.begin();

  	for (it; it!=un_set.end(); ++it)
    	cout << devolver_notacion(*it) << " - ";	// cout << " " << *it;
  	cout << endl;
}


//////////////////////////////////////////////////////////////////


void genera_estados_posibles(set<int> &estado, int codigo_o, list< set<int> > &lista_estados){

	set<int> estado_posible;
	set<int> pos_validas;
	set<int> disparos_validos;
	int codigo, jugada;

	// calcula posiciones validas de movida para la pieza
	posiciones_validas(estado, codigo_o, pos_validas);
	//cout << devolver_notacion(codigo_o) << " tiene " << pos_validas.size() << " posiciones validas" <<endl;

	// para c/jugada posible mueve la ficha
	set<int>::iterator it= pos_validas.begin();
	for (it; it!=pos_validas.end(); it++){
		estado_posible= estado;								// copia el estado original y trabaja con la copia
		mover_ficha(estado_posible, codigo_o, *it);

		// disparos validos posibles EN ese estado posible
		codigo= (*it % 100) + 900;							// por ser int, me da el codigo de ficha
		//codigo= codigo * 100;                             // codigo % 100 + 900;
		//codigo = *it - codigo + 900;						// codigo disparo
		posiciones_validas(estado_posible, codigo, disparos_validos);
		// cout << "disparos validos para posicion " << *it << " --> " << disparos_validos.size() << endl;


		// para c/disparo posible genera un estado y lo agrega a la lista
		set<int>::iterator it_disparo= disparos_validos.begin();
		for (it_disparo; it_disparo!=disparos_validos.end(); it_disparo++){
			jugada = *it_disparo * 1000 + *it;               // 6 digitos:  9xx5xx  flechaficha
			//cout << jugada << endl;
			estado_posible.insert(jugada);                   // para no perder la ultima jugada que se hizo
			estado_posible.insert(*it_disparo);              // inserta un disparo en estado (la jugada ya estaba cuando movio la ficha)
			lista_estados.push_back(estado_posible);         // pone el estado al final de la lista
			estado_posible.erase(*it_disparo);		         // borra el disparo para insertar el q sigue (con la misma jugada)
			estado_posible.erase(jugada);                    // borra la jugada para insertar la nueva
		}
	}

	// cout << "lista de estados posibles c/u con sus flechas: " << lista_estados.size() << endl << endl;
}

int funcion_heuristica (set<int> estado, int jugador, int heuristica) {
    //verifica segun criterios que tan bueno es el estado
    //por ahora retorna un promedio de posiciones validas para las reinas del jugador.
    set<int> pos_validas;

    switch (heuristica){
        case 1:{
                // retorna un numero al azar entre 1 y 100
                int numero= 1 + rand()%(101-1);
                return numero;
        }
        break;
        case 2:{
                int tamano = 0;
                set<int>::iterator it= estado.begin();
                for (it; it!= estado.end(); it++){
                    if (jugador == -1 && (*it/100 == 5 || *it/100 == 6 || *it/100 == 7 || *it/100 == 8)){       // identifica las reinas Azules
                        posiciones_validas(estado, *it, pos_validas);
                            tamano += pos_validas.size();
                    }
                    if (jugador == 1 && (*it/100 == 1 || *it/100 == 2 || *it/100 == 3 || *it/100 == 4)){        // identifica las reinas Rojas
                        posiciones_validas(estado, *it, pos_validas);
                            tamano += pos_validas.size();
                    }
                }
                return tamano/4;
        }
        break;
        case 3:{
                
                // maximiza la diferencia de casilleros accesibles vs las del oponente
                int maximas_rojas= 0;
                int maximas_azules= 0;
                set<int>::iterator it= estado.begin();
                for (it; it!= estado.end(); it++){
                    if (*it/100 == 5 || *it/100 == 6 || *it/100 == 7 || *it/100 == 8){       // identifica las reinas Azules
                        posiciones_validas(estado, *it, pos_validas);
                        maximas_azules += pos_validas.size();
                    }
                    if (*it/100 == 1 || *it/100 == 2 || *it/100 == 3 || *it/100 == 4){        // identifica las reinas Rojas
                        posiciones_validas(estado, *it, pos_validas);
                        maximas_rojas += pos_validas.size();
                    }
                }
                
                return (maximas_rojas - maximas_azules) * jugador;                             // jugador es 1 para rojas o -1 para azules

        }
        break;
        case 4: {
            int minimo = 0;
            set<int>::iterator it= estado.begin();
            if (jugador == -1){
                while (*it/100 < 5) {
                    posiciones_validas(estado, *it, pos_validas);
                    if (pos_validas.empty())
                        return 100;
                    else
                        if (pos_validas.size() < minimo)
                            minimo = pos_validas.size();
                    it++;
                }
                return 100 - minimo;
            }
            if (jugador == 1) {
                while (*it/100 < 5)
                    it++;
                while (*it/100 < 9) {
                    posiciones_validas(estado, *it, pos_validas);
                    if (pos_validas.empty())
                        return 100;
                    else
                        if (pos_validas.size() < minimo)
                            minimo = pos_validas.size();
                    it++;
                }
                return 100 - minimo;
            }

        }
        break;
    }
}


int NegaMax (set<int> estado, int profundidad, int alpha, int beta, int jugador, set<int> &mejor_estado, int heuristica) {
    // Hay que hacer que guarde la jugada elegida en un entero y despues generarla para que mueva la ficha.
    set<int> pos_validas;
    list< set<int> > lista_estados;
    int Max, valor, h;
    int contador;
/*
    //imprimir_set(estado);
    set<int>::iterator iterador= estado.begin();
    for (iterador; iterador != estado.end(); iterador++)
        cout << "elemento: " << *iterador;
    //cout << "ultimo: " << *estado.end() << endl;
    //cout << "primero: " << *estado.begin() << endl;
    cin.ignore();


    cout << "jugador: " << jugador << endl;
    cout << "alpha: " << alpha << endl;
    cout << "beta: " << beta << endl;
    cin.ignore();
*/
    set<int>::iterator it= estado.begin();
        for (it; it!= estado.end(); it++){
            //cout << *it << endl;
            if (jugador == -1 && (*it/100 == 5 || *it/100 == 6 || *it/100 == 7 || *it/100 == 8)){		// identifica las reinas Azules

                posiciones_validas(estado, *it, pos_validas);
/*
                if (pos_validas.empty() || profundidad == 0){                         //ficha atrapada
                    h= funcion_heuristica(estado, jugador, heuristica) * jugador;
                    // cout << "Heuristica= " << h;
                    return h;
                }
                */
                if (profundidad == 0){                                                  
                    h= funcion_heuristica(estado, jugador, heuristica) * jugador;
                    return h;
                }
                else if (!pos_validas.empty()) {
                    Max = -1000;
                    genera_estados_posibles(estado, *it, lista_estados);

                    list< set<int> >::iterator it_lista = lista_estados.begin();
                    contador= 0;
                    for (it_lista; it_lista != lista_estados.end(); it_lista++) {
                        contador ++;
                        //imprimir_tablero(*it_lista);
                        //cin.ignore();
                        valor= -NegaMax(*it_lista, profundidad - 1, -beta, -alpha, -jugador, mejor_estado, heuristica);
                        if (valor > Max)
                            Max= valor;
                        if (valor > alpha) {
                            mejor_estado = *it_lista;
                            alpha= valor;
                        }
                        if (alpha >= beta){
                            return alpha;       
                        }
                        //cout << "jugador: " << jugador << " alpha vale: " << alpha << " y el it_lista: " << contador << endl;
                    }
                    // return alpha;
                }

            }else if (jugador == 1 && (*it/100 == 1 || *it/100 == 2 || *it/100 == 3 || *it/100 == 4)){		// identifica las reinas Rojas
                posiciones_validas(estado, *it, pos_validas);
/*
                if (pos_validas.empty() || profundidad == 0){//ficha atrapada
                    h= funcion_heuristica(estado, jugador, heuristica) * jugador;
                    // cout << "Heuristica= " << h;
                    return h;
                }
                */
                if (profundidad == 0){//ficha atrapada
                    h= funcion_heuristica(estado, jugador, heuristica) * jugador;
                    // cout << "Heuristica= " << h;
                    return h;
                }
                else if (!pos_validas.empty()) {
                    Max = -1000;
                    genera_estados_posibles(estado, *it, lista_estados);
                    contador= 0;
                    list< set<int> >::iterator it_lista = lista_estados.begin();
                    for (it_lista; it_lista != lista_estados.end(); it_lista++) {
                        contador++;
                        //imprimir_tablero(*it_lista);
                        //cin.ignore();
                        valor = -NegaMax(*it_lista, profundidad - 1, -beta, -alpha, -jugador, mejor_estado, heuristica);
                        if (valor > Max)
                            Max = valor;
                        if (valor > alpha){
                            mejor_estado = *it_lista;
                            alpha = valor;
                        }
                        if (alpha >= beta){
                            return alpha;
                        }
                        //cout << "jugador: " << jugador << " alpha vale: " << alpha << " y el it_lista: " << contador << endl;
                    }
                    
                }
            }
        }           // cierra el for
        return alpha;

}

void descompone_jugada(int jugada, int & mov, int & flecha) {
    mov = jugada % 1000;
    flecha = (jugada - mov)/1000;
}

/*
int NegaMax (Tablero T, int depth, int alpha, int beta, jugador j):
Si T es un tablero de juego finalizado o depth es igual a cero
    Devolver evaluaci�n_heuristica(T) * valor_jugador(J)
Sino
    Inicializar max en -infinito.
    Para cada jugada v�lida V del jugador J en el tablero T
        Generar el tablero T' resultante al realizar V
        Asignar valor =-NegaMax(T', depth-1, -beta, -alpha, J.adversario())
        Si valor > max
            Asignar max = valor
        Si valor > alpha
            Asignar alpha = valor
        Si alpha >= beta
            Devolver alpha
    Devolver alpha
*/

void juega_humano(set<int> &estado, int jugador){
    // si jugador=  1 ---> juegan las rojas
    // si jugador= -1 ---> juegan las azules

    int eleccion, fila_o, columna_o, ficha_o, fila_d, columna_d, ficha_d, codigo_o, codigo_d;       // x, y, ficha y codigo  origen / destino
    string origen, destino;
    bool xy_invalido= true;
    bool ficha_invalida= true;

    while (xy_invalido || ficha_invalida){
        xy_invalido= true;
        ficha_invalida= true;
        cout << "Ingrese Origen: ";
        cin >> origen;

        obtener_fila_columna(origen, columna_o, fila_o);
        if (columna_o == -1 || fila_o == -1)
            cout << "Fila o Columna Incorrecta" << endl;
        else
            xy_invalido= false;

        ficha_o= obtener_codigo_ficha(estado, columna_o, fila_o);
        if (jugador == 1){
            if (!ficha_o || ficha_o == 900 || ficha_o == 500 || ficha_o == 600 || ficha_o == 700 || ficha_o == 800)
                cout << "No hay fichas suyas para mover en ese casillero" << endl;
            else
                ficha_invalida= false;

        }

        if (jugador == -1){
            if (!ficha_o || ficha_o == 900 || ficha_o == 100 || ficha_o == 200 || ficha_o == 300 || ficha_o == 400)
                cout << "No hay fichas suyas para mover en ese casillero" << endl;
            else
                ficha_invalida= false;
        }
    }   // cierra el while

    codigo_o= ficha_o + columna_o * 10 + fila_o;

    // idem para el destino
    xy_invalido= true;
    ficha_invalida= true;

    while (xy_invalido || ficha_invalida){

        xy_invalido= true;
        ficha_invalida= true;

        cout << "Ingrese Destino: ";
        cin >> destino;

        obtener_fila_columna(destino, columna_d, fila_d);
        if (columna_d == -1 || fila_d == -1)
            cout << "Fila o Columna Incorrecta" << endl;
        else
            xy_invalido= false;

        ficha_d= obtener_codigo_ficha(estado, columna_d, fila_d);
        if (ficha_d)
            cout << "Casilla Destino Ocupada!" << endl;
        else{
            ficha_d= ficha_o;                               // es la misma ficha que va a otro lado
            codigo_d= ficha_d + columna_d * 10 + fila_d;

            if (!destino_valido(estado, codigo_o, codigo_d))
                cout << "Destino Inalcanzable !!";
            else
                ficha_invalida= false;
            }
    }       // cierra el while


    mover_ficha(estado, codigo_o, codigo_d);
    imprimir_tablero(estado);
    cout << "Ultima Jugada: " << devolver_notacion(codigo_o) << " mueve a " << devolver_notacion(codigo_d) << endl;


    // flecha

    codigo_o= codigo_d;                             // la flecha sale de la reina anterior
    ficha_d= 1;                                     // para la condicion del while

    while (columna_d == -1 || fila_d == -1 || ficha_d || !destino_valido(estado, codigo_o, codigo_d)){
        cout << "Ingrese Destino de la Flecha: ";
        cin >> destino;

        obtener_fila_columna(destino, columna_d, fila_d);
        if (columna_d == -1 || fila_d == -1){
            cout << "Fila o Columna Incorrecta" << endl;
        }

        ficha_d= obtener_codigo_ficha(estado, columna_d, fila_d);           // chequea si esta vacia!
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
    codigo_o= codigo_o - ficha_o + ficha_d;                             // el origen de la flecha es el destino de la reina anterior
    mover_ficha(estado, codigo_o, codigo_d);
    imprimir_tablero(estado);

    /// COPIAR LA INFO DE LA FICHA ORIGINARIA PORQUE LA PIERDO EN EL MEDIO Y NO LA PUEDO IMPRIMIR!!
    cout << "Ultima Jugada: " << devolver_notacion(codigo_o) << " mueve a " << devolver_notacion(codigo_o) << "  Ultima Flecha: " << devolver_notacion(codigo_d) << endl;

}


void juega_cpu(set<int> &estado, int jugador, int profundidad, int heuristica){
    // si jugador=  1 ---> juegan las rojas
    // si jugador= -1 ---> juegan las azules

    list< set<int> > lista_estados;
    set<int> mejor_estado;
    int alpha, beta;
    int movimiento=0, flechazo=0, ultima=0;

    alpha= -1000;
    beta= 1000;
/*
    if (jugador == 1){
        alpha= 1000;
        beta= -1000;
    }else{
        alpha= -1000;
        beta= 1000;

    }
*/
    ultima = NegaMax(estado, profundidad, alpha, beta, jugador, mejor_estado, heuristica);
/*
    set<int>::iterator iterador= mejor_estado.begin();
    for (iterador; iterador != mejor_estado.end(); iterador++)
        cout << "elemento: " << *iterador;
    //cout << "ultimo: " << *estado.end() << endl;
    //cout << "primero: " << *estado.begin() << endl;
    cin.ignore();
*/
    //cout << "ultima: " << ultima << endl;
    //estado= mejor_estado;
    set<int>::iterator iterador= mejor_estado.end();
    iterador--;
    descompone_jugada(*iterador, movimiento, flechazo);
    mejor_estado.erase(*iterador);

    iterador= estado.begin();
    while (*iterador /100 != movimiento /100)
        iterador++;

    //cout << "ficha origen: " << devolver_notacion(*iterador) << endl;

    estado= mejor_estado;
    imprimir_tablero(estado);

    //cout << "movimiento: " << devolver_notacion(movimiento) << ",  flecha: " << devolver_notacion(flechazo) << endl;


}


void administra_juego(set<int> &estado, int rojas, int azules, int profundidad_rojas, int profundidad_azules, int heuristica_rojas, int heuristica_azules){
    // esta funcion alterna los jugadores
    // primero juegan las ROJAS y despues juegan las AZULES

    // define estado inicial: ubicacion de las 4 reinas de cada color
    //estado= {130, 260, 303, 493, 539, 669, 706, 896};
    estado = {100, 260, 303, 493, 539, 661, 706, 896, 910, 911};
    // estado = {100, 260, 302, 448, 503, 669, 706, 896, 901, 910, 911, 912, 913, 916, 918, 921, 924, 928, 940, 944, 951, 952};

    set<int> pos_validas;
    bool gano_rojo= false;
    bool gano_azul= false;
    int posibles_azul, posibles_rojas;

    while (!gano_rojo && !gano_azul){
        imprimir_tablero(estado);

        if (rojas == 1)                             // juega humano
            juega_humano(estado, 1);                // 1= rojas
        else{
            // cout << "entra a jugar cpu rojas..." << endl;
            juega_cpu(estado, 1, profundidad_rojas, heuristica_rojas);
        }

        // evalua si gano rojo viendo si al azul le quedan movidas
        posibles_azul= 0;
        posibles_rojas= 0;
        set<int>::iterator it= estado.begin();
        for (it; it!= estado.end(); it++){
            if (*it/100 == 5 || *it/100 == 6 || *it/100 == 7 || *it/100 == 8){       // identifica las reinas Azules
                posiciones_validas(estado, *it, pos_validas);
                posibles_azul += pos_validas.size();
                // cout << "azul tiene " << posibles << " posibles jugadas" << endl;
            }
            // evalua si el rojo no quedo encerrado
            if (*it/100 == 1 || *it/100 == 2 || *it/100 == 3 || *it/100 == 4){       // identifica las reinas Rojas
                posiciones_validas(estado, *it, pos_validas);
                posibles_rojas += pos_validas.size();
            }
        }

        if (posibles_azul == 0)
            gano_rojo= true;
    
        if (posibles_rojas == 0)                        // porque se pudo haber encerrado solo el rojo
            gano_azul= true;        

        // ahora juegan las AZULES
        if (!gano_rojo && !gano_azul){
            if (azules == 1)                            // juega humano
                juega_humano(estado, -1);               // -1= azules
            else{
                // si las rojas tambien era cpu hace una pausa!!
                // cin.ignore();

                // cout << "entra a jugar cpu Azules..." << endl;
                juega_cpu(estado, -1, profundidad_azules, heuristica_azules);
            }

            // evalua si gano Azul viendo si al rojo le quedan movidas
            posibles_rojas= 0;
            posibles_azul= 0;
            it= estado.begin();
            for (it; it!= estado.end(); it++){
                if (*it/100 == 1 || *it/100 == 2 || *it/100 == 3 || *it/100 == 4){       // identifica las reinas Rojas
                    posiciones_validas(estado, *it, pos_validas);
                    posibles_rojas= posibles_rojas + pos_validas.size();
                    // cout << "rojo tiene " << posibles << " posibles jugadas" << endl;
                }
                if (*it/100 == 5 || *it/100 == 6 || *it/100 == 7 || *it/100 == 8){       // identifica las reinas Azules
                    posiciones_validas(estado, *it, pos_validas);
                    posibles_azul += pos_validas.size();
                }
            }

            if (posibles_rojas == 0)
                gano_azul= true;
            
            if (posibles_azul == 0)                     //  evalua esto porque se pudo haber encerrado solo
                gano_rojo= true;
        }       
    }       // cierra while

    if (gano_azul){
        cout << "GANADOR: jugador Azul";
        int puntaje=0;
        set<int>::iterator it = estado.begin();
        for(it; it!=estado.end(); it++){
            if (*it/100 == 5 || *it/100 == 6 || *it/100 == 7 || *it/100 == 8){
                posiciones_validas(estado, *it, pos_validas);
                puntaje += pos_validas.size();
            }
        }
        cout << " con un puntaje de: " << puntaje << endl;
        cin.ignore();
        cin.ignore();

    }
    else if (gano_rojo){
        cout << "GANADOR: jugador Rojo";
        int puntaje=0;
        set<int>::iterator it = estado.begin();
        for(it; it!=estado.end(); it++){
            if (*it/100 == 1 || *it/100 == 2 || *it/100 == 3 || *it/100 == 4){
                posiciones_validas(estado, *it, pos_validas);
                puntaje += pos_validas.size();
            }
        }
        cout << " con un puntaje de: " << puntaje << endl;
        cin.ignore();
        cin.ignore();
    }

}


void configurar_cpu(int &profundidad, int &heuristica ){

    cout << "o------------o" << endl;
    cout << "| Heuristica |" << endl;
    cout << "o------------o" << endl;
    cout << " 1 - Jugar al Azar                                                   " << endl;
    cout << " 2 - Maximizar Promedio de Casillas Libres                           " << endl;
    cout << " 3 - Maximizar la Diferencia de Casilleros Accesibles                " << endl;
    cout << " 4 - Premia Encerrar Piezas Enemigas                                 " << endl;
    cout << endl;
    cout << " Ingrese su opcion: ";
    cin >> heuristica;
    cout << endl;
    cout << endl;
    cout << "o-------------o" << endl;
    cout << "| Profundidad |" << endl;
    cout << "o-------------o" << endl;
    cout << " Ingrese el Nivel de Analisis Deseado (1 a 10) " << endl;
    cout << endl;
    cout << " Ingrese su opcion: ";
    cin >> profundidad;
    cout << endl;
    
}


//////////////////////////////////////////////////////////////////////////////////////
//								MAIN												//
//////////////////////////////////////////////////////////////////////////////////////

int main(){
    srand(time(NULL));      //genera semilla para numeros aleatorios a partir de la hora del sistema
	set<int> estado;
	int rojas, azules, opcion, profundidad_azules, profundidad_rojas, heuristica_azules, heuristica_rojas;

    rojas= 1000000;                                        // para asegurar pase x preferencias antes de jugar

	imprimir_menu();
	cin >> opcion;

    while (opcion != 0){
        switch (opcion){
            case 1:{						// jugar
                    if (rojas == 1000000){
                        cout << string(50, '\n');
                        cout << "o-----------------------------------------------------o" << endl;
                        cout << "|   Debe configurar sus Preferencias antes de Jugar!  |" << endl;
                        cout << "o-----------------------------------------------------o" << endl << endl << endl;
                        cout << "          Presione <ENTER> para continuar...";
                        cin.ignore();
                        cin.ignore();
                        break;
                    }
            		imprimir_tablero(estado);
            		administra_juego(estado, rojas, azules, profundidad_rojas, profundidad_azules, heuristica_rojas, heuristica_azules);
                    // jugar(estado);
            	}
                break;
            case 2:{						              
					rojas= 0;
                    azules= 0;
                    cout << string(50, '\n');
                    //cout << "o--------------o" << endl;
                    cout << " Preferencias " << endl;
                    //cout << "o--------------o" << endl << endl;

                    cout << "_______________________________________" << endl << endl << " Modo Jugador ROJO" << endl << "_______________________________________" << endl << " 1- Humano" << endl <<" 2- Computadora" << endl;
                    cout << endl << " Ingrese una Opcion: ";
                    while ((rojas != 1) && (rojas != 2) )
                        cin >> rojas;
                    if (rojas == 2){
                        cout << endl << "Configuracion de la Computadora Roja" << endl << endl;
                        configurar_cpu(profundidad_rojas, heuristica_rojas);
                    }

                    cout  << endl << endl;
                    cout << "_______________________________________" << endl << endl << " Modo Jugador AZUL" << endl << "_______________________________________" << endl << " 1- Humano" << endl <<" 2- Computadora" << endl;
                    cout << endl << " Ingrese una Opcion: ";
                    while ((azules != 1) && (azules!= 2))
                        cin >> azules;
                    if (azules == 2){
                        cout << endl << "Configuracion de la Computadora Azul" << endl << endl;
                        configurar_cpu(profundidad_azules, heuristica_azules);
                    }

                    cout << string(50, '\n');
            	    cout << "o--------------o" << endl;
                    cout << "| Preferencias |" << endl;
                    cout << "o--------------o" << endl << endl;
                    cout << "Modo elegido -->  ";
                    cout << "Rojas: ";
                    if (rojas == 1)
                        cout << "Humano    : vs :   Azules: ";
                    else
                        cout << "Computadora    : vs :   Azules: ";
                    if (azules == 1)
                        cout << "Humano" << endl;
                    else
                        cout << "Computadora" << endl;
                }

                break;

            default:{
            	    cout <<  endl << "Opcion invalida\n" << "Ingrese una nueva opcion\n";
            	}
            break;
        	}

       	imprimir_menu();

        cin >> opcion;


    }

	return 0;
}
