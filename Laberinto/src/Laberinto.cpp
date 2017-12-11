//============================================================================
// Name        : Laberinto.cpp
// Author      : Jose Antonio Alvarez Nieto
// Version     :
// Description : Proyecto final de Fundamento de Programaci�n
//				 Creaci�n de un "juego" en el que a trav�s de un laberinto tendr� que ir capturando
//				 diferentes objetivos para ir sumando puntos. Se registrar�n usuarios y sus puntuaciones
//				 m�ximas que seran guardados en ficheros.
//============================================================================

//Librerias
#include <iostream>
#include <fstream>
#include <conio.h>
#include <conio2.h>
#include <windows.h>

//Constantes
#define maxnick 11
#define maxnom 51
#define maxjug 20
#define columnas 40
#define filas 20
#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

//Tipos de datos
typedef char nombre[maxnom];
typedef char nick[maxnick];
typedef struct{
	nick minick;
	nombre minombre;
	char nacion;
	int edad;
	int puntos;
}jugador;
typedef jugador vec_jug[maxjug];
typedef jugador matriz_jugador[maxjug][5];
typedef char laberinto_pares[filas][columnas];
typedef char laberinto_impares[filas][columnas];
typedef char laberinto_vocales[filas][columnas];
typedef struct{
	vec_jug vj;
	int cont;
}regis_jug;
typedef char cadena_columna[columnas];

//Cabeceras de modulos
int menu1(void);
int menu2(void);
void leer_fichero_jugadores(regis_jug rj, jugador j_aux);
void leer_laberinto_pares(laberinto_pares laberintop);
void leer_laberinto_impares(laberinto_pares laberintoi);
void leer_laberinto_vocales(laberinto_pares laberintov);
void nuevo_jugador(regis_jug rj, nick nickaux, 	jugador reg_jug, jugador j_aux);
int buscar_nick(regis_jug rj, const nick nickaux);
int usuario_registrado(regis_jug rj, nick nickaux, jugador reg_jug, jugador j_aux);
void fichero_jugadores(jugador j_aux, regis_jug rj, matriz_jugador jugadores);
void mover(laberinto_pares laberintop);

using namespace std;

int main(){

	int opcion1, opcion2, registrado;
	jugador reg_jug;
	nick nickaux;
	regis_jug rj;
	jugador j_aux;
	matriz_jugador jugadores;
	laberinto_pares laberintop;
	laberinto_impares laberintoi;
	laberinto_vocales laberintov;

	clrscr();
	opcion1=menu1();

	while(opcion1!=4){

		switch (opcion1) {
		case 1:
			clrscr();
			cout<<"**************** Registrar jugador. ****************"<<endl;
			Sleep(2000);
			clrscr();
			//Registramos nuevo usuario y comprobamos si el nick ya existe para que use otro
			nuevo_jugador(rj, nickaux, reg_jug, j_aux);
			//Cuando acabemos el proceso de registro de usuario, volveremos al menu1();
			break;
		case 2:
			clrscr();
			cout<<"**************** Jugador existente. ****************"<<endl;
			Sleep(2000);
			clrscr();
			//Comprobamos si el nick est� ya registrado para usarlo en el laberinto.
			//Si existe, pasamos al menu2(); donde elegira a que tipo de laberinto quieres jugar.
			registrado=usuario_registrado(rj, nickaux,reg_jug, j_aux);
			if(registrado !=-1){

				clrscr();

				cout<<"Su usuario esta registrado"<<endl;
				Sleep(2000);

				opcion2=menu2();

				while(opcion2!=4){

					switch (opcion2) {
					case 1:
						clrscr();
						cout<<"**************** Caza de numeros pares.****************"<<endl;
						Sleep(2000);
						clrscr();
						//Cargamos el fichero laberintop.txt para jugar.
						leer_laberinto_pares(laberintop);
						mover(laberintop);
						//Una vez que el usuario llegue a la salida o pulse Esc, si la puntuacion obtenida es mayor a la que ya tenia o no tenia
						//ninguna se actualizara en caso contrario se quedar� la que ya tenia. Esto se hara con todos los laberintos.
						break;
					case 2:
						clrscr();
						cout<<"**************** Caza de numeros impares. ****************"<<endl;
						Sleep(2000);
						clrscr();
						//Cargamos el fichero laberintoi.txt para jugar.
						leer_laberinto_impares(laberintoi);
						//mover();
						break;
					case 3:
						clrscr();
						cout<<"**************** Caza de vocales. ****************"<<endl;
						Sleep(2000);
						clrscr();
						//Cargamos el fichero laberintov.txt para jugar.
						leer_laberinto_vocales(laberintov);
						//mover();
						break;
					default:
						break;
					}

					opcion2=menu2();
				}
			}else{

				clrscr();

				cout<<"Su usuario no esta registrado, registrelo antes de jugar."<<endl;
				Sleep(2000);

			}
			break;
		case 3:
			clrscr();
			cout<<"**************** Mostrar fichero de jugadores. ****************"<<endl;
			Sleep(2000);
			clrscr();
			//Mostramos el fichero jugadores.txt
			fichero_jugadores(j_aux, rj, jugadores);
			break;
		default:
			break;
		}

		opcion1=menu1();
	}

	return 0;
}

void ocultarCursor(){

	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(hCon,&cci);
}

void mover(laberinto_pares laberintop){

	ocultarCursor();

	int tecla, fila, columna, ancho_fila, ancho_columna, x, y;
	fila=0;
	columna=0;
	ancho_fila=20;
	ancho_columna=40;
	x=0;
	y=4;

	bool game_over=false;
	while(!game_over){
		if(kbhit()){
			tecla = getch();
			gotoxy(x, y);
			printf(" ");
			if(tecla == ARRIBA && y-2>fila){

				if(laberintop[y-1][x]=='#'){

					Beep(100,100);

				}else{

					y--;
				}
			}

			if(tecla == ABAJO && y+1<ancho_fila){

				if(laberintop[y][x]=='#'){

					Beep(100,100);

				}else{

					y++;
				}
			}

			if(tecla == IZQUIERDA && x-2>columna){

				if(laberintop[y][x-2]=='#'){

					Beep(100,100);

				}else{

					x--;
				}
			}

			if(tecla == DERECHA && x+1<ancho_columna){

				if(laberintop[y][x+1]=='#'){

					Beep(100,100);

				}else{

					x++;
				}
			}

			gotoxy(x,y);
			printf("%c", char(219));

			if(tecla == 27 /*TECLA ESC*/ || (x==39 && y==15) /*coordenadas S*/){
				game_over=true;
			}

		}
		Sleep(20);
	}

}

int menu1(void){

	int opcion1;

	clrscr();
	textcolor(WHITE);
	cout<<"Elige una de las opciones:"<<endl;
	cout<<""<<endl;
	cout<<"1.- Registrar jugador nuevo."<<endl;
	cout<<"2.- Jugador existente."<<endl;
	cout<<"3.- Mostrar fichero de jugadores."<<endl;
	cout<<"4.- Fin."<<endl;
	cout<<""<<endl;
	cout<<"Introduce la opcion que desees realizar: ";
	cin>>opcion1;

	while(opcion1<1 || opcion1>4){
		cout<<"Error, vuelva a introducir una opcion valida: ";
		cin>>opcion1;
	}

	return opcion1;

}

int menu2(void){

	int opcion2;

	clrscr();
	textcolor(WHITE);
	cout<<"Elige una de las opciones:"<<endl;
	cout<<""<<endl;
	cout<<"1.- Caza de numeros pares."<<endl;
	cout<<"2.- Caza de numeros impares."<<endl;
	cout<<"3.- Caza de vocales."<<endl;
	cout<<"4.- Volver al menu anterior."<<endl;
	cout<<""<<endl;
	cout<<"Introduce la opcion que desees realizar: ";
	cin>>opcion2;

	while(opcion2<1 || opcion2>4){
		cout<<"Error, vuelva a introducir una opcion valida: ";
		cin>>opcion2;
	}

	return opcion2;

}

void leer_fichero_jugadores(regis_jug rj, jugador j_aux){

	ifstream fi_jugadores;

	fi_jugadores.open("jugadores.txt",ios::binary);

	if(!fi_jugadores.fail()){

		//leemos el fichero y lo vamos guardando en el vector
		rj.cont=0;
		fi_jugadores>>j_aux.minick;
		while(!fi_jugadores.eof()){

			fi_jugadores>>rj.vj[rj.cont].minick;
			fi_jugadores>>rj.vj[rj.cont].minombre;
			fi_jugadores>>rj.vj[rj.cont].nacion;
			fi_jugadores>>rj.vj[rj.cont].edad;
			fi_jugadores>>rj.vj[rj.cont].puntos;

			rj.cont++;

		}
	}

	fi_jugadores.close();

}

void leer_laberinto_pares(laberinto_pares laberintop){

	int i;
	ifstream fi_pares;
	cadena_columna c1;

	fi_pares.open("laberintop.txt");

	if(!fi_pares.fail()){

		fi_pares>>c1;

		i=0;
		while(!fi_pares.eof()){

			for(int j=0; j<columnas; j++){

				laberintop[i][j]=c1[j];
			}

			fi_pares>>c1;
			i++;
		}

		for(int i=0; i<filas; i++){

			for(int j=0; j<columnas; j++){

				cout<<laberintop[i][j];
			}
			cout<<endl;
		}
	}

	fi_pares.close();
}

void leer_laberinto_impares(laberinto_impares laberintoi){

	ifstream fi_impares;

	fi_impares.open("laberintoi.txt");

	if(!fi_impares.fail()){

		while(!fi_impares.eof()){

			for(int i=0; i<filas; i++){

				for(int j=0; j<columnas; j++){

					fi_impares>>laberintoi[i][j];
				}
			}

		}

		for(int i=0; i<filas; i++){

			for(int j=0; j<columnas; j++){

				cout<<laberintoi[i][j];
			}
			cout<<endl;
		}
		Sleep(5000);
	}

	fi_impares.close();
}

void leer_laberinto_vocales(laberinto_vocales laberintov){

	ifstream fi_vocales;

	fi_vocales.open("laberintov.txt");

	if(!fi_vocales.fail()){

		while(!fi_vocales.eof()){

			for(int i=0; i<filas; i++){

				for(int j=0; j<columnas; j++){

					fi_vocales>>laberintov[i][j];
				}
			}

		}

		for(int i=0; i<filas; i++){

			for(int j=0; j<columnas; j++){

				cout<<laberintov[i][j];
			}
			cout<<endl;
		}
		Sleep(5000);
	}

	fi_vocales.close();
}

void nuevo_jugador(regis_jug rj, nick nickaux, jugador reg_jug, jugador j_aux){

	int i, posaux;;

	ofstream fo_jugadores;
	ifstream fi_jugadores;

	rj.cont=0;

	fi_jugadores.open("jugadores.txt");

	if(!fi_jugadores.fail()){

		//leemos el fichero y lo vamos guardando en el vector
		fi_jugadores>>j_aux.minick;
		i=0;
		while(!fi_jugadores.eof()){

			strcpy(rj.vj[i].minick,j_aux.minick); //Funcion para copiar el contenido de una cadena a otra.
			fi_jugadores>>rj.vj[i].minombre;
			fi_jugadores>>rj.vj[i].nacion;
			fi_jugadores>>rj.vj[i].edad;
			fi_jugadores>>rj.vj[i].puntos;
			i++;
			rj.cont++;
			fi_jugadores>>j_aux.minick;
		}
	}

	fi_jugadores.close();

	//Introducimos los datos en el registro jugador reg_jug para despues volcarlo en el fichero.

	cout<<"Introduzca su nick:";
	cin>>nickaux;
	posaux = buscar_nick(rj, nickaux);
	while (posaux !=-1){

		cout<<"Ese nick ya existe, introduzca otro nick:";
		cin>>nickaux;
		posaux = buscar_nick(rj, nickaux);

	}
	strcpy(reg_jug.minick, nickaux); //Funcion para copiar el contenido de una cadena a otra.

	cout<<"Introduzca su nombre y apellidos (Sin espacios):";
	cin>>reg_jug.minombre;

	cout<<"Introduzca su nacionalidad (e --> ESP , x -->EXT):";
	cin>>reg_jug.nacion;
	reg_jug.nacion=toupper(reg_jug.nacion);

	while(reg_jug.nacion != 'E' && reg_jug.nacion != 'X'){

		cout<<"Caracter introducido no valido, vuelva a intentarlo."<<endl;
		cout<<"Introduzca su nacionalidad (e --> ESP , x -->EXT):";
		cin>>reg_jug.nacion;
		reg_jug.nacion=toupper(reg_jug.nacion);
	}

	cout<<"Introduzca su edad:";
	cin>>reg_jug.edad;

	//Guardamos en el archivo el jugador nuevo

	fo_jugadores.open("jugadores.txt",ios::app);

	if(!fo_jugadores.fail()){

		fo_jugadores<<""<<endl;
		fo_jugadores<<reg_jug.minick<<" ";
		fo_jugadores<<reg_jug.minombre<<" ";
		fo_jugadores<<reg_jug.nacion<<" ";
		fo_jugadores<<reg_jug.edad<<" ";

	}

	fo_jugadores.close();

	clrscr();
	cout<<"Jugador registrado correctamente."<<endl;
	Sleep(2000);

}

int usuario_registrado(regis_jug rj, nick nickaux, jugador reg_jug, jugador j_aux){

	int i, posaux;;

	ifstream fi_jugadores;

	rj.cont=0;

	fi_jugadores.open("jugadores.txt");

	if(!fi_jugadores.fail()){

		//leemos el fichero y lo vamos guardando en el vector
		fi_jugadores>>j_aux.minick;
		i=0;
		while(!fi_jugadores.eof()){

			strcpy(rj.vj[i].minick,j_aux.minick); //Funcion para copiar el contenido de una cadena a otra.
			fi_jugadores>>rj.vj[i].minombre;
			fi_jugadores>>rj.vj[i].nacion;
			fi_jugadores>>rj.vj[i].edad;
			fi_jugadores>>rj.vj[i].puntos;
			i++;
			rj.cont++;
			fi_jugadores>>j_aux.minick;
		}
	}

	fi_jugadores.close();

	cout<<"Introduzca su nick:";
	cin>>nickaux;
	posaux = buscar_nick(rj, nickaux);

	return posaux;

}

void fichero_jugadores(jugador j_aux, regis_jug rj, matriz_jugador jugadores){

	leer_fichero_jugadores(rj, j_aux);

	//Muestra el fichero jugadores.txt

	for(int i=0; i<rj.cont; i++){

		cout<<rj.vj[i].minick<<" ";
		cout<<rj.vj[i].minombre<<" ";
		cout<<rj.vj[i].nacion<<" ";
		cout<<rj.vj[i].edad<<" ";
		cout<<rj.vj[i].puntos<<endl;

	}

	Sleep(5000);
}

int buscar_nick (regis_jug rj, const nick nickaux){

	int i=0;
	int posicion=-1;

	while (i<rj.cont && posicion==-1){

		if (strcmp(nickaux, rj.vj[i].minick)==0){

			posicion=i;

		}else{

			i++;

		}
	}

	return posicion;
}
