//Ignacio Redondo Navarro Grupo B

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime> //Lo necesito para el dado

using namespace std;

typedef enum {Rojo=1, Verde=2, Amarillo=3, Azul=4} tColor;



tColor obtener_jugador() { //Función para obtener color deseado por jugador
	int color = 0;
	tColor result=Rojo;
	cout << "Bienvenido, indique que color quiere ser(1=Rojo, 2=Verde, 3=Amarillo, 4=Azul) " <<endl ;
	while (cin >> color) {
		if (color < 5 && color>=1) {//Comprobación número correcto
			break;
		}
		else {
			cout << "Numero incorrecto, (1=Rojo, 2=Verde, 3=Amarillo, 4=Azul)" << endl;
		}
	}
	if (color == 1) //Asigno color según número introducido
		result = Rojo;
	else if (color == 2)
		result = Verde;
	else if (color == 3)
		result = Amarillo;
	else if (color == 4)
		result = Azul;

	return result;
}
bool comp_jugadores_diferentes(tColor color_1, tColor color_2) {//Jugadores deben ser distintos
	bool result = true;
	if (color_1 == color_2) {
		cout << "Los jugadores deben ser diferentes" << endl;
		result = false;
	}
	else if (color_1 != color_2)
		result = true;

	return result;
}
string colorACadena(tColor color) { //Cadena del color de cada jugador
	string result;
	if (color == Rojo)
		result = "Rojo";
	else if (color == Verde)
		result = "Verde";
	else if (color == Amarillo)
		result = "Amarillo";
	else if (color == Azul)
		result = "Azul";

	return result;
}
char letra(tColor color) { //Inicial color cada jugador
	char result='a';
	if (color == Rojo)
		result = 'R';
	else if (color == Verde)
		result = 'V';
	else if (color == Amarillo)
		result = 'M'; //Amarillol es M, si  no habría dos A
	else if (color == Azul)
		result = 'A';

	return result;
}
int salida(tColor color) {
	int salida = 0;
	if (color == Rojo)
		salida = 39;
	else if (color == Verde)
		salida = 56;
	else if (color == Amarillo)
		salida = 5;
	else if (color == Azul)
		salida = 22;

	return salida;
}
int meta(tColor color) {
	int meta = 0;
	if (color == Rojo)
		meta = 34;
	else if (color == Verde)
		meta = 51;
	else if (color == Amarillo)
		meta = 0;
	else if (color == Azul)
		meta = 17;

	return meta;
}





int lanzar_dado(int posicion_activo, string color_activo) { //Función que actúa como dado y revisa si se tiran tres 6 seguidos
	//string tecla="???";
	int num_dado = 0;
		//cin >> tecla; Sería útil para simular que se lanza el dado
		 //Genera  número aleatorio entre 1 y 6
		//num_dado = (time(NULL) % 6) + 1; Sería la función para tener un dado aleatorio
		while (true) {
			cout << "\n" << color_activo << " introduce el numero que quieres sacar" << endl;
			cin >> num_dado;
			cin.ignore();
			if (num_dado > 0 && num_dado <= 6) {
				num_dado = num_dado;
				break;
			}
			else {
				cout << "Se supone que es un dado, del 1 al 6" << endl;
				continue;
			}			
		}

		return num_dado; 
							
}
int comp_cuenta_seis(int num_dado, int cuenta_de_6) {
	if (num_dado != 6)
		cuenta_de_6 = -1; //Así cortaremos el while del turno del jugador
	else if (num_dado == 6)
		cuenta_de_6++;

	return cuenta_de_6;
}
void narrador(int num_tirada, string sColor) {
	cout << sColor <<" sacaste un " << num_tirada << endl;
	if (num_tirada == 6)
		cout << "Con un 6 repites tirada, al tercero pierdes turno y vuelves a casa" << endl;
}
bool comp_sale_casa(int tirada, int posicion_activo) { //Función que comprueba si la ficha sale de casa
	bool result = true;
	if (posicion_activo == -1 && tirada != 5) {
		cout << "NO sale de casa" << endl;
		result = false;
	}
	else if (posicion_activo == -1 && tirada == 5) {
		cout << "Enhorabuena, sales de casa" << endl;
		result = true;
	}
	else if (posicion_activo != -1) //Si la ficha no está en casa, consideramos que ha salido
		result = true;


	return result;
}
int mueve_posicion(bool sale_casa,int tirada, int posicion_activo, int salida, int cuenta_6) {//Función que manipula posiciones
	if (cuenta_6 < 3) { //Mientras no haya sacado tres seis
		if (sale_casa && posicion_activo == -1) { //Manipulación si la ficha justo sale de casa
			posicion_activo = salida;
		}
		else if (sale_casa && posicion_activo != -1) { //Manipulación si la ficha ya estaba fuera
			posicion_activo = posicion_activo + tirada;

		}
		else if (!sale_casa) //Manipulación si la ficha se queda en casa
			posicion_activo = -1;
	}
	else if (cuenta_6 == 3) {//Si saca tres seis, para casa
		cout << "Tres 6... Hasta aqui llega tu turno" << endl;
		posicion_activo = -1;
	}

	
	return posicion_activo;
}
int comp_pasa_68(int posicion_activo) { //Función que corrige posición si te pasas de 68
	if (posicion_activo >= 68) {
		posicion_activo = posicion_activo - 68;
	}
	else if (posicion_activo < 68) //Si no se pasa no hay que cambiar nada
		posicion_activo = posicion_activo;
	

	return posicion_activo;
}
void aviso_cae_casa(int posicion_activo) { //Función que avisa si caes en casa
	int casas[12] = { 0, 5 ,12 , 17, 22, 29, 34, 39, 46, 51, 56, 63 };
	for (int i = 0; i < 12; i++) {
		if (posicion_activo == casas[i]) {
			cout << "Caiste en casilla segura" << endl;
			break;
		}
	}
}
bool comp_pasiva_casa(int posicion_pasivo) { //Función que comprueba si el pasivo está en casa
	bool result=true;
	int casas[12] = { 0, 5 ,12 , 17, 22, 29, 34, 39, 46, 51, 56, 63 };
	for (int i = 0; i < 12; i++) {
		if (posicion_pasivo == casas[i]) {
			result = true;
			break;
		}
		else
			result = false;
	}


	return result;
}
bool comp_come(bool pasiva_casa, int posicion_activo, int posicion_pasivo, string color_activo, string color_pasivo, int salida) { //Función que comprueba si el jugador come a rival
	bool result = true;
	if (posicion_activo != -1) { //Si activo está en casa impedimos que coma a otro que esté en casa
		if (!pasiva_casa) { //Come si la ficha no está en casa
			if (posicion_activo == posicion_pasivo) {
				cout << color_activo << " come ficha de " << color_pasivo << " !!" << endl;        
				result = true;
			}
			else if (posicion_activo != posicion_pasivo)
				result = false;
		}
		else if (pasiva_casa) {
			if (posicion_activo == posicion_pasivo) { //Sólo le come si están en la misma posición
				if (posicion_pasivo == salida) {
					cout << color_pasivo << " estabas en la salida, te elimino!" << endl;
					result = true; //Si justo estas en la salida y el otro sale te elimina
				}
				else if (posicion_pasivo != salida)
					result = false;
			}
			else if(posicion_pasivo != salida)
				result = false;
		} 
	}
	else if (posicion_activo == -1) //Si está en casa no come
		result = false;
	

	return result;
}
int if_comida_a_casa(bool come, int posicion_activo, int posicion_pasivo, string color_pasivo, int salida) {//Función que manda al comido a casa
	if (come) {
		cout << color_pasivo << " vuelve a casa" << endl;
		posicion_pasivo = -1;
	}
	else if (!come) { //Si no ha sido comido devolvemos posición sin cambios
		posicion_pasivo = posicion_pasivo;
	}

	return posicion_pasivo;
}
int if_come_avanza_20_pasivo_no_casa(bool come,int posicion_activo,int posicion_pasivo, string color_activo, string color_pasivo) {//Función que te avanza 20 si has comido
	if (come) {																															//y te retrasa 1 si has caido en una casa ocupada
		cout << color_activo << " avanza 20!!" << endl;
		posicion_activo = posicion_activo + 20;
	}
	else if (!come) {//Dos escenarios posibles si no come
		if (posicion_activo == posicion_pasivo && posicion_activo != -1) { //Si no come y están en = posición es porque pasivo en casa, retraso uno a activo. A menos que ambos estén en casa
			cout << color_pasivo << " esta en casa. " << color_activo << " no pudo comerle!!" << endl;
			posicion_activo = posicion_activo - 1;
		}
		else if (posicion_activo != posicion_pasivo)// No come porque no están en = posición
			posicion_activo = posicion_activo;
	}

	return posicion_activo;
}
//Aquí va otra correción de si se ha pasado de 68 tras comer
int comp_pasa_meta(bool come, int posicion_activo, int meta, int tirada, int salida) {
	int posicion_prueba = posicion_activo;

	if (!come) {
		if (posicion_activo > meta && posicion_activo < salida) { //La tierra de nadie de si te has pasado está entre zanata y salida
			cout << "Te pasaste de la meta!!" << endl;
			posicion_activo = posicion_activo - tirada;
			if (posicion_activo < 0)
				posicion_activo = 68 + posicion_activo;
		}
		else {//Si no está en la tierra de nadie no hacemos nada
			posicion_activo = posicion_activo;
		}
	}
	else if (come) {
		if (posicion_activo > meta && posicion_activo < salida) { //Comprobación estándar de si se pasó de la meta
			cout << "Vaya, te pasaste de la meta. No suman las 20" << endl;
			posicion_activo = posicion_activo - 20;
			if (posicion_activo < 0)
				posicion_activo = 68 + posicion_activo;
		}
		else { //Tras comer puede pasarse de la meta y la salida, realizamos comprobación más exacta que la de arriba
			posicion_prueba = posicion_activo - 20; //Utilizamos variable de prueba para no manipular demasiado a posicion_activo
			if (posicion_prueba < 0)                //Volvemos a la posición antes de sumar las 20 de comer
				posicion_prueba = 68 + posicion_prueba;
			for (int i = 1; i < 21; i++) {
				posicion_prueba++; //Vamos sumándole de uno en uno las 20 posiciones que va a avanzar
				posicion_prueba = comp_pasa_68(posicion_prueba);//Corregimos si se pasa de 68
				if (posicion_prueba > meta && posicion_prueba < salida) {
					cout << "Vaya, te pasaste de la meta. No suman las 20" << endl;
					posicion_activo = posicion_prueba - i; //Si se pasa, se le resta a su posición ya cambiada (posicion_activo-20) el número de veces que ha pasado por el bucle y te da la posición antes de comer
					if (posicion_activo < 0) {
						posicion_activo = 68 + posicion_activo;
					}
					break;
				}
				else //Si no se pasó de la meta, devolvemos su posición tras comer normal
					posicion_activo = posicion_activo;
			} 
		}
	}
	return posicion_activo;
}
int cambio_externo_comido(int posicion_activo, int posicion_pasivo) { //Función que cambia posicion_pasivo = -1 si es comido (correr_juego solo cambia posicion_activo)
	if (posicion_activo == posicion_pasivo) { //Si están en la misma posición es porque ha sido comido pero no pudo sumar 20
		posicion_pasivo = -1;
	}
	else {
		posicion_activo = posicion_activo - 20; //Comprobamos si le comió y después pudo sumar 20
		if (posicion_activo < 0)
			posicion_activo = 68 + posicion_activo;
		if (posicion_activo == posicion_pasivo)
			posicion_pasivo = -1;
		else if (posicion_activo != posicion_pasivo) //Si no le ha comido no realizamos cambios
			posicion_pasivo = posicion_pasivo;
	}
		

	return posicion_pasivo;
}
bool comp_ganador(int posicion_activo, int meta) { //Función que comprueba si el jugador activo ha ganado
	bool result = true;
	if (posicion_activo == meta) {
		result = true; //En el bucle del juego se añade algo que pare todo
	}
	else if (posicion_activo != meta)
		result = false;


	return result;
}


void creacion_tablero(char inicial_j1, char inicial_j2, int posicion_j1, int posicion_j2) {
	char tablero[4][68] = {
		{'o','-','-','-','-','o','-','-','-','-','-','-','o','-','-','-','-','o','-','-','-','-','o','-','-','-','-','-','-','o','-','-','-','-','o','-','-','-','-','o','-','-','-','-','-','-','o','-','-','-','-','o','-','-','-','-','o','-','-','-','-','-','-','o','-','-','-','-'},
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'o','-','-','-','-','o','-','-','-','-','-','-','o','-','-','-','-','o','-','-','-','-','o','-','-','-','-','-','-','o','-','-','-','-','o','-','-','-','-','o','-','-','-','-','-','-','o','-','-','-','-','o','-','-','-','-','o','-','-','-','-','-','-','o','-','-','-','-'},
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
	};
	if (posicion_j1 == -1)           //Con estos if coloco las fichas
		tablero[3][20] = inicial_j1;
	else if (posicion_j1 > -1) {
		tablero[1][posicion_j1] = inicial_j1;
	}
	if (posicion_j2 == -1)
		tablero[3][40] = inicial_j2;
	else if (posicion_j2 > -1)
		tablero[1][posicion_j2] = inicial_j2;
	
	cout << "\n          " << "00000000001111111111222222222233333333334444444444555555555566666666" << endl
		<< "          " << "01234567890123456789012345678901234567890123456789012345678901234567" << endl;
	for (int f = 0; f < 4; f++) {
		if (f == 0 || f == 2) {
			cout << "          " ;
			for (int c = 0; c < 68; c++)
				cout << tablero[f][c];
			cout << endl;
		}
		else if (f == 1) {
			cout << "\nCALLE" << "     " ;
			for (int c = 0; c < 68; c++)
				cout << tablero[f][c];
			cout << endl;
		}
		else if (f == 3) {
			cout << "\nCASA" << "      " ;
			for (int c = 0; c < 68; c++)
				cout << tablero[f][c];
			cout << endl;
		}
	}
	
	cout << endl;
}

int correr_juego(bool sale_casa, bool pasiva_casa, bool come,string color_activo, string color_pasivo, int tirada, int posicion_activo, int posicion_pasivo, int salida, int meta, int cuenta_6, char inicial_activo, char inicial_pasivo) {
	sale_casa = comp_sale_casa(tirada, posicion_activo);
	posicion_activo = mueve_posicion(sale_casa, tirada, posicion_activo, salida, cuenta_6);
	posicion_activo = comp_pasa_68(posicion_activo);
	aviso_cae_casa(posicion_activo);
	pasiva_casa = comp_pasiva_casa(posicion_pasivo);
	come = comp_come(pasiva_casa, posicion_activo, posicion_pasivo, color_activo, color_pasivo, salida);
	posicion_pasivo = if_comida_a_casa(come, posicion_activo, posicion_pasivo, color_pasivo, salida);
	posicion_activo = if_come_avanza_20_pasivo_no_casa(come, posicion_activo, posicion_pasivo, color_activo, color_pasivo);
	posicion_activo = comp_pasa_68(posicion_activo);
	posicion_activo = comp_pasa_meta(come, posicion_activo, meta, tirada, salida);


	return posicion_activo;
}


int main() {
	tColor color1 = Rojo, color2 = Rojo;
	char inicial1 = 'a', inicial2 = 'a';
	string sColor1 = "???", sColor2 = "???";
	int posicion1 = -1, posicion2 = -1;
	int meta1 = 0, meta2 = 0;
	int salida1 = 0, salida2 = 0;
	int tirada = 0, contador_6 = 0;
	bool sale_casa = false, come = false, pasiva_casa=false, ganador = false;
	bool comprobante = false;
	while (!comprobante) { //Obtengo jugadores y compruebo son diferentes
		color1 = obtener_jugador();
		color2 = obtener_jugador();
		comprobante = comp_jugadores_diferentes(color1, color2);
	}
	inicial1 = letra(color1);
	inicial2 = letra(color2);
	sColor1 = colorACadena(color1);
	sColor2 = colorACadena(color2);
	meta1 = meta(color1);
	meta2 = meta(color2);
	salida1 = salida(color1);
	salida2 = salida(color2);
	//Final de obtención de datos de jugadores
	
	while (true) {
		contador_6 = 0; //Reinciamos el contador al principio de cada turno
		while(contador_6>=0 && contador_6 < 3 && !ganador){
			tirada = lanzar_dado(posicion1, sColor1);
			contador_6 = comp_cuenta_seis(tirada, contador_6); //Si el contador llega a 3, en correr_juego mandamos a casa al jugador
			system("cls"); //Borra tablero
			narrador(tirada, sColor1);
			posicion1 = correr_juego(sale_casa, pasiva_casa, come, sColor1, sColor2, tirada, posicion1, posicion2, salida1, meta1, contador_6, inicial1, inicial2);
			posicion2 = cambio_externo_comido(posicion1, posicion2);
			creacion_tablero(inicial1, inicial2, posicion1, posicion2);
			ganador = comp_ganador(posicion1, meta1); 
			}
		if (ganador) {
			cout << "Enhorabuena " << sColor1 << " has ganado!" << endl;
			break;
		}
		contador_6 = 0;
		while (contador_6 >= 0 && contador_6 < 3 && !ganador) {
			tirada = lanzar_dado(posicion2, sColor2);
			contador_6 = comp_cuenta_seis(tirada, contador_6);
			system("cls");
			narrador(tirada, sColor2);
			posicion2 = correr_juego(sale_casa, pasiva_casa, come, sColor2, sColor1, tirada, posicion2, posicion1, salida2, meta2,contador_6, inicial2, inicial1);
			posicion1 = cambio_externo_comido(posicion2, posicion1);
			creacion_tablero(inicial1, inicial2, posicion1, posicion2);
			ganador = comp_ganador(posicion2, meta2);
		}
		if (ganador) {
			cout << "Enhorabuena " << sColor2 << " has ganado!" << endl;
			break;
		}
	}
	


	
	return 0;
}