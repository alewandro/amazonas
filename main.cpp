#include <iostream>
#include "Tablero.h"
#include "Impresiones.h"
#include <list>
#include <set>
#include <math.h>
#include <stdlib.h>     // para numeros aleatorios
#include <time.h>       // para numeros aleatorios

using namespace std;

void genera_estados_posibles(set<int> &estado, int codigo_o, list< set<int> > &lista_estados){

	set<int> estado_posible;
	set<int> pos_validas;
	set<int> disparos_validos;
	int codigo, jugada;

	// calcula posiciones validas de movida para la pieza
	posiciones_validas(estado, codigo_o, pos_validas);

	// para c/jugada posible mueve la ficha
	set<int>::iterator it= pos_validas.begin();
	for (it; it!=pos_validas.end(); it++){
		estado_posible= estado;								// copia el estado original y trabaja con la copia
		mover_ficha(estado_posible, codigo_o, *it);

		// disparos validos posibles EN ese estado posible
		codigo= (*it % 100) + 900;							// por ser int, me da el codigo de ficha
		posiciones_validas(estado_posible, codigo, disparos_validos);

		// para c/disparo posible genera un estado y lo agrega a la lista
		set<int>::iterator it_disparo= disparos_validos.begin();
		for (it_disparo; it_disparo!=disparos_validos.end(); it_disparo++){
			jugada = *it_disparo * 1000 + *it;               // 6 digitos:  9xx5xx  flechaficha
			estado_posible.insert(jugada);                   // para no perder la ultima jugada que se hizo
			estado_posible.insert(*it_disparo);              // inserta un disparo en estado (la jugada ya estaba cuando movio la ficha)
			lista_estados.push_back(estado_posible);         // pone el estado al final de la lista
			estado_posible.erase(*it_disparo);		         // borra el disparo para insertar el q sigue (con la misma jugada)
			estado_posible.erase(jugada);                    // borra la jugada para insertar la nueva
		}
	}
}

int funcion_heuristica (set<int> estado, int jugador, int heuristica) {
    //verifica segun criterios que tan bueno es el estado
    set<int> pos_validas;

    switch (heuristica){
        case 1:{
                // retorna un numero al azar entre 1 y 100
                int numero= 1 + rand()%(101-1);
                return numero;
        }
        break;
        case 2:{
                // retorna un promedio de posiciones validas para las reinas del jugador.
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
                return tamano/4 * jugador;
        }
        break;
        case 3:{       
                // retorna la diferencia de casilleros accesibles vs las del oponente
                int maximas_rojas= 0;
                int maximas_azules= 0;
                int diferencia= 0;
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
                if (jugador == 1)
                    diferencia= maximas_rojas - maximas_azules;
                else
                    diferencia= maximas_azules - maximas_rojas;
                    
                return diferencia * jugador;

        }
        break;
        case 4: {
            // retorna un valor maximo cuando a alguna reina enemiga le quedan pocas casillas de movimientos
            int minimo = 100;
            set<int>::iterator it= estado.begin();
            if (jugador == -1){
                while (*it/100 < 5) {
                    posiciones_validas(estado, *it, pos_validas);
                    if (!pos_validas.empty() && pos_validas.size() < minimo)
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
                    if (!pos_validas.empty() && pos_validas.size() < minimo)
                        minimo = pos_validas.size();
                    it++;
                }
                return 100 - minimo;
            }
        }
        break;
    }
}


int NegaMax (set<int> estado, int profundidad, int alpha, int beta, int jugador, set<int> &mejor_estado, int heuristica, bool cpu_r, bool cpu_a) {
    set<int> pos_validas;
    list< set<int> > lista_estados;
    int Max, valor, h;

    set<int>::iterator it= estado.begin();
        for (it; it!= estado.end(); it++){
            if (jugador == -1 && (*it/100 == 5 || *it/100 == 6 || *it/100 == 7 || *it/100 == 8)){		// identifica las reinas Azules
                posiciones_validas(estado, *it, pos_validas);

                if (profundidad == 0){                                                  
                    h= funcion_heuristica(estado, jugador, heuristica) * jugador;
                    return h;
                }
                else if (!pos_validas.empty()) {
                    Max = -1000;
                    genera_estados_posibles(estado, *it, lista_estados);

                    list< set<int> >::iterator it_lista = lista_estados.begin();
                    for (it_lista; it_lista != lista_estados.end(); it_lista++) {

                        valor= -NegaMax(*it_lista, profundidad - 1, -beta, -alpha, -jugador, mejor_estado, heuristica, 0, 0);
                        if (valor > Max)
                            Max= valor;
                        if (valor > alpha) {
                            if (cpu_a)
                                mejor_estado = *it_lista;
                            alpha= valor;
                        }
                        if (alpha >= beta){
                            return alpha;
                        }
                    }
                }

            }else if (jugador == 1 && (*it/100 == 1 || *it/100 == 2 || *it/100 == 3 || *it/100 == 4)){		// identifica las reinas Rojas
                posiciones_validas(estado, *it, pos_validas);

                if (profundidad == 0){
                    h= funcion_heuristica(estado, jugador, heuristica) * jugador;
                    return h;
                }
                else if (!pos_validas.empty()) {
                    Max = -1000;
                    genera_estados_posibles(estado, *it, lista_estados);
                    list< set<int> >::iterator it_lista = lista_estados.begin();
                    for (it_lista; it_lista != lista_estados.end(); it_lista++) {
                        valor = -NegaMax(*it_lista, profundidad - 1, -beta, -alpha, -jugador, mejor_estado, heuristica, 0, 0);
                        if (valor > Max)
                            Max = valor;
                        if (valor > alpha){
                            if (cpu_r)
                                mejor_estado = *it_lista;
                            alpha = valor;
                        }
                        if (alpha >= beta){
                            return alpha;
                        }
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

    int eleccion, fila_o, columna_o, ficha_o, fila_d, columna_d, ficha_d, codigo_o, codigo_d, ori, desti;
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
    ori = codigo_o;
    desti = codigo_d;
    cout << " Ultima Jugada: " << devolver_notacion(codigo_o) << " mueve a " << devolver_notacion(codigo_d) << endl;

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

    cout << "Ultima Jugada: " << devolver_notacion(ori) << " mueve a " << devolver_notacion(desti) << "  Ultima Flecha: " << devolver_notacion(codigo_d) << endl;

}


void juega_cpu(set<int> &estado, int jugador, int profundidad, int heuristica){
    // si jugador=  1 ---> juegan las rojas
    // si jugador= -1 ---> juegan las azules

    list< set<int> > lista_estados;
    set<int> mejor_estado;
    int alpha, beta, origen;
    int movimiento=0, flechazo=0, ultima=0;
    bool cpu_r, cpu_a;

    alpha= -1000;
    beta= 1000;
    if (jugador == 1) {
        cpu_r = true;
        cpu_a = false;
    }
    else {
        cpu_a = true;
        cpu_r = false;
    }

    ultima = NegaMax(estado, profundidad, alpha, beta, jugador, mejor_estado, heuristica, cpu_r, cpu_a);

    set<int>::iterator iterador= mejor_estado.end();
    iterador--;
    descompone_jugada(*iterador, movimiento, flechazo);
    mejor_estado.erase(*iterador);

    iterador= estado.begin();
    while (*iterador /100 != movimiento /100)
        iterador++;

    origen = *iterador;

    estado= mejor_estado;
    imprimir_tablero(estado);

    cout << " ultimo movimiento: " << devolver_notacion(origen) << " - " << devolver_notacion(movimiento) << ",  flecha: " << devolver_notacion(flechazo) << endl;
}


void administra_juego(set<int> &estado, int rojas, int azules, int profundidad_rojas, int profundidad_azules, int heuristica_rojas, int heuristica_azules){
    // esta funcion alterna los jugadores
    // primero juegan las ROJAS y despues juegan las AZULES

    set<int> pos_validas;
    bool gano_rojo= false;
    bool gano_azul= false;
    int posibles_azul, posibles_rojas;

    int ganadas_rojas= 0;
    int ganadas_azules= 0;

    // define estado inicial: ubicacion de las 4 reinas de cada color
    estado= {130, 260, 303, 493, 539, 669, 706, 896};

    imprimir_tablero(estado);

    while (!gano_rojo && !gano_azul){

        if (rojas == 1)                             // juega humano
            juega_humano(estado, 1);                // 1= rojas
        else{
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
        cout << " GANADOR: jugador Azul";
        int puntaje=0;
        set<int>::iterator it = estado.begin();
        for(it; it!=estado.end(); it++){
            if (*it/100 == 5 || *it/100 == 6 || *it/100 == 7 || *it/100 == 8){
                posiciones_validas(estado, *it, pos_validas);
                puntaje += pos_validas.size();
            }
        }
        cout << " con un puntaje de: " << puntaje << endl << endl << "      Presione <ENTER> para continuar";
        cin.ignore();
        cin.ignore();
    }
    else if (gano_rojo){
        cout << " GANADOR: jugador Rojo";
        int puntaje=0;
        set<int>::iterator it = estado.begin();
        for(it; it!=estado.end(); it++){
            if (*it/100 == 1 || *it/100 == 2 || *it/100 == 3 || *it/100 == 4){
                posiciones_validas(estado, *it, pos_validas);
                puntaje += pos_validas.size();
            }
        }
        cout << " con un puntaje de: " << puntaje << endl << endl << "      Presione <ENTER> para continuar";
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

    rojas= 1000000;                                  // para asegurar pase x preferencias antes de jugar

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
            	}
                break;
            case 2:{
					rojas= 0;
                    azules= 0;
                    cout << string(50, '\n');
                    cout << " Preferencias " << endl;

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
