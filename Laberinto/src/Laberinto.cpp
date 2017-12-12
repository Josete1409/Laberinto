//============================================================================
// Name        : Laberinto.cpp
// Author      : Jose Antonio Alvarez Nieto
// Version     :
// Description : Proyecto final de Fundamento de Programación
//				 Creación de un "juego" en el que a través de un laberinto tendrá que ir capturando
//				 diferentes objetivos para ir sumando puntos. Se registrarán usuarios y sus puntuaciones
//				 máximas que seran guardados en ficheros.
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
#define F1 59 //(salto-derecha)
#define F2 60 //(salto-izquierda)
#define F3 61 //(salto-arriba)
#define F4 62 //(salto-abajo)

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
void leer_fichero_jugadores(regis_jug & rj, jugador reg_jug);
void leer_laberinto_pares(laberinto_pares laberintop, cadena_columna cp);
void leer_laberinto_impares(laberinto_impares laberintoi, cadena_columna ci);
void leer_laberinto_vocales(laberinto_vocales laberintov, cadena_columna cv);
void nuevo_jugador(regis_jug & rj, nick nickaux, jugador reg_jug);
int usuario_registrado(regis_jug rj, nick nickaux, jugador reg_jug);
void fichero_jugadores(jugador reg_jug, regis_jug rj);
int buscar_nick(regis_jug rj, const nick nickaux);
void mover_pares(laberinto_pares laberintop);
void mover_impares(laberinto_impares laberintoi);
void mover_vocales(laberinto_vocales laberintov);
void cargar_laberinto_pares(laberinto_pares laberintop);
void cargar_laberinto_impares(laberinto_impares laberintoi);
void cargar_laberinto_vocales(laberinto_vocales laberintov);
void escribir_fichero_jugadores(regis_jug & rj);


using namespace std;

int main(){

	int opcion1, opcion2, registrado;
	jugador reg_jug;
	regis_jug rj;
	nick nickaux;
	laberinto_pares laberintop;
	laberinto_impares laberintoi;
	laberinto_vocales laberintov;
	cadena_columna cp;
	cadena_columna ci;
	cadena_columna cv;

	rj.cont=0;

	leer_fichero_jugadores(rj, reg_jug);

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
			nuevo_jugador(rj, nickaux, reg_jug);
			//Cuando acabemos el proceso de registro de usuario, volveremos al menu1();
			break;
		case 2:
			clrscr();
			cout<<"**************** Jugador existente. ****************"<<endl;
			Sleep(2000);
			clrscr();
			//Comprobamos si el nick está ya registrado para usarlo en el laberinto.
			//Si existe, pasamos al menu2(); donde elegira a que tipo de laberinto quieres jugar.
			registrado=usuario_registrado(rj, nickaux, reg_jug);
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
						leer_laberinto_pares(laberintop, cp);
						cargar_laberinto_pares(laberintop);
						mover_pares(laberintop);
						//Una vez que el usuario llegue a la salida o pulse Esc, si la puntuacion obtenida es mayor a la que ya tenia o no tenia
						//ninguna se actualizara en caso contrario se quedará la que ya tenia. Esto se hara con todos los laberintos.
						break;
					case 2:
						clrscr();
						cout<<"**************** Caza de numeros impares. ****************"<<endl;
						Sleep(2000);
						clrscr();
						//Cargamos el fichero laberintoi.txt para jugar.
						leer_laberinto_impares(laberintoi, ci);
						cargar_laberinto_impares(laberintoi);
						mover_impares(laberintoi);
						break;
					case 3:
						clrscr();
						cout<<"**************** Caza de vocales. ****************"<<endl;
						Sleep(2000);
						clrscr();
						//Cargamos el fichero laberintov.txt para jugar.
						leer_laberinto_vocales(laberintov, cv);
						cargar_laberinto_vocales(laberintov);
						mover_vocales(laberintov);
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
			fichero_jugadores(reg_jug, rj);
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

void leer_fichero_jugadores(regis_jug & rj, jugador reg_jug){

	ifstream fi_jugadores;
	int i;

	fi_jugadores.open("jugadores.txt");

	if(!fi_jugadores.fail()){

		//leemos el fichero y lo vamos guardando en el vector
		fi_jugadores>>reg_jug.minick;
		i=0;

		while(!fi_jugadores.eof()){

			strcpy(rj.vj[i].minick, reg_jug.minick);
			fi_jugadores>>rj.vj[i].minombre;
			fi_jugadores>>rj.vj[i].nacion;
			fi_jugadores>>rj.vj[i].edad;
			fi_jugadores>>rj.vj[i].puntos;

			i++;
			rj.cont++;
			fi_jugadores>>reg_jug.minick;

		}

	}

	fi_jugadores.close();

}

void leer_laberinto_pares(laberinto_pares laberintop, cadena_columna cp){

	/*int i;
	ifstream fi_pares;

	fi_pares.open("laberintop.txt");

	if(!fi_pares.fail()){

		fi_pares>>cp;
		i=0;

		while(!fi_pares.eof()){

			for(int j=0; j<columnas; j++){

				laberintop[i][j]=cp[j];
			}

			fi_pares>>cp;
			i++;
		}
	}

	fi_pares.close();*/

	ifstream fi_pares;

	fi_pares.open("laberintop.txt");

	if(!fi_pares.fail()){

		while(!fi_pares.eof()){

			for(int i=0; i<filas; i++){

				for(int j=0; j<columnas; j++){

					fi_pares>>laberintop[i][j];

				}
			}
		}
	}

	fi_pares.close();
}

void leer_laberinto_impares(laberinto_impares laberintoi, cadena_columna ci){

	/*int i;
	ifstream fi_impares;

	fi_impares.open("laberintoi.txt");

	if(!fi_impares.fail()){

		fi_impares>>ci;
		i=0;

		while(!fi_impares.eof()){

			for(int j=0; j<columnas; j++){

				laberintoi[i][j]=ci[j];
			}

			fi_impares>>ci;
			i++;
		}

	}

	fi_impares.close();*/

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
	}

	fi_impares.close();

}

void leer_laberinto_vocales(laberinto_vocales laberintov, cadena_columna cv){

	/*int i;
	ifstream fi_vocales;

	fi_vocales.open("laberintov.txt");

	if(!fi_vocales.fail()){

		fi_vocales>>cv;
		i=0;

		while(!fi_vocales.eof()){

			for(int j=0; j<columnas; j++){

				laberintov[i][j]=cv[j];
			}

			fi_vocales>>cv;
			i++;

		}
	}

	fi_vocales.close();*/

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
	}

	fi_vocales.close();

}

void nuevo_jugador(regis_jug & rj, nick nickaux, jugador reg_jug){

	int posaux;

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

	reg_jug.puntos=0; //Lo inicializamos a 0

	/*//Guardamos en el archivo el jugador nuevo

	fo_jugadores.open("jugadores.txt",ios::app);

	if(!fo_jugadores.fail()){

		fo_jugadores<<""<<endl;
		fo_jugadores<<reg_jug.minick<<" ";
		fo_jugadores<<reg_jug.minombre<<" ";
		fo_jugadores<<reg_jug.nacion<<" ";
		fo_jugadores<<reg_jug.edad<<" ";

	}

	fo_jugadores.close();*/

	clrscr();
	cout<<"Jugador registrado correctamente."<<endl;

	Sleep(2000);

}

int usuario_registrado(regis_jug rj, nick nickaux, jugador reg_jug){

	int posaux;;

	cout<<"Introduzca su nick:";
	cin>>nickaux;
	posaux = buscar_nick(rj, nickaux);

	return posaux;

}

void fichero_jugadores(jugador reg_jug, regis_jug rj){

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



	int i, posicion;

	i=0;
	posicion=-1;

	while (i<rj.cont && posicion==-1){

		if (strcmp(nickaux, rj.vj[i].minick)==0){

			posicion=i;

		}else{

			i++;

		}
	}

	return posicion;
}

void mover_pares(laberinto_pares laberintop){

	ocultarCursor();

	int tecla, x, y, num, puntuacion;
	char pared;

	pared='#';
	x=0;
	y=4;
	puntuacion=0;

	bool game_over=false;

	while(!game_over){

		if(kbhit()){

			tecla = getch();
			gotoxy(x, y);
			printf(" ");
			num=laberintop[y][x];

			if(tecla == F1){ //Satar-Derecha

				if(laberintop[y][x+2] == pared){

					Beep(250, 100);

				}else{

					x=x+2;
				}
			}

			if(tecla == F2){ //Satar-Izquierda

				if(laberintop[y][x-2] == pared){

					Beep(250, 100);

				}else{

					x=x-2;
				}
			}

			if(tecla == F3){ //Satar-Arriba

				if(laberintop[y-2][x] == pared){

					Beep(250, 100);

				}else{

					y=y-2;

				}
			}

			if(tecla == F4){ //Satar-Abajo

				if(laberintop[y+2][x] == pared){

					Beep(250, 100);

				}else{

					y=y+2;

				}
			}

			if(tecla == ARRIBA){

				if(laberintop[y-1][x] == pared){

					Beep(250, 100);

				}else{

					y--;
				}
			}

			if(tecla == ABAJO){

				if(laberintop[y+1][x] == pared){

					Beep(250, 100);

				}else{

					y++;
				}
			}

			if(tecla == IZQUIERDA){

				if(laberintop[y][x-1] == pared){

					Beep(250, 100);

				}else{

					x--;
				}
			}

			if(tecla == DERECHA){

				if(laberintop[y][x+1] == pared){

					Beep(250, 100);

				}else{

					x++;
				}
			}

			gotoxy(x,y);
			printf("%c", char(219));
			num=laberintop[y][x];

			if(num == '_' || num == 'E' || num == 'S'){

				puntuacion=puntuacion+0;

			}else{

				if(num%2 == 0){

					puntuacion=puntuacion+10;

				}else{

					puntuacion=puntuacion-10;
				}

			}

			if(tecla == 27 /*TECLA ESC*/ || (x==40 && y==15) /*coordenadas S*/){
				game_over=true;
				cout<<puntuacion;
				Sleep(3000);
			}

		}
		Sleep(20);
	}

}

void mover_impares(laberinto_impares laberintoi){

	ocultarCursor();

	int tecla, x, y, num, puntuacion;
	char pared;

	pared='#';
	x=0;
	y=4;
	puntuacion=0;

	bool game_over=false;

	while(!game_over){

		if(kbhit()){

			tecla = getch();
			gotoxy(x, y);
			printf(" ");
			num=laberintoi[y][x];

			if(tecla == F1){ //Satar-Derecha

				if(laberintoi[y][x+2] == pared){

					Beep(250, 100);

				}else{

					x=x+2;
				}
			}

			if(tecla == F2){ //Satar-Izquierda

				if(laberintoi[y][x-2] == pared){

					Beep(250, 100);

				}else{

					x=x-2;
				}
			}

			if(tecla == F3){ //Satar-Arriba

				if(laberintoi[y-2][x] == pared){

					Beep(250, 100);

				}else{

					y=y-2;

				}
			}

			if(tecla == F4){ //Satar-Abajo

				if(laberintoi[y+2][x] == pared){

					Beep(250, 100);

				}else{

					y=y+2;

				}
			}

			if(tecla == ARRIBA){

				if(laberintoi[y-1][x] == pared){

					Beep(250, 100);

				}else{

					y--;
				}
			}

			if(tecla == ABAJO){

				if(laberintoi[y+1][x] == pared){

					Beep(250, 100);

				}else{

					y++;
				}
			}

			if(tecla == IZQUIERDA){

				if(laberintoi[y][x-1] == pared){

					Beep(250, 100);

				}else{

					x--;
				}
			}

			if(tecla == DERECHA){

				if(laberintoi[y][x+1] == pared){

					Beep(250, 100);

				}else{

					x++;
				}
			}

			gotoxy(x,y);
			printf("%c", char(219));
			num=laberintoi[y][x];

			if(num == '_' || num == 'E' || num == 'S'){

				puntuacion=puntuacion+0;

			}else{

				if(num%2 == 0){

					puntuacion=puntuacion-10;

				}else{

					puntuacion=puntuacion+10;
				}

			}

			if(tecla == 27 /*TECLA ESC*/ || (x==40 && y==15) /*coordenadas S*/){
				game_over=true;
				cout<<puntuacion;
				Sleep(3000);
			}

		}
		Sleep(20);
	}

}

void mover_vocales(laberinto_vocales laberintov){

	ocultarCursor();

	int tecla, x, y, num, puntuacion;
	char pared;

	pared='#';
	x=0;
	y=4;
	puntuacion=0;

	bool game_over=false;

	while(!game_over){

		if(kbhit()){

			tecla = getch();
			gotoxy(x, y);
			printf(" ");
			num=laberintov[y][x];

			if(tecla == F1){ //Satar-Derecha

				if(laberintov[y][x+2] == pared){

					Beep(250, 100);

				}else{

					x=x+2;
				}
			}

			if(tecla == F2){ //Satar-Izquierda

				if(laberintov[y][x-2] == pared){

					Beep(250, 100);

				}else{

					x=x-2;
				}
			}

			if(tecla == F3){ //Satar-Arriba

				if(laberintov[y-2][x] == pared){

					Beep(250, 100);

				}else{

					y=y-2;

				}
			}

			if(tecla == F4){ //Satar-Abajo

				if(laberintov[y+2][x] == pared){

					Beep(250, 100);

				}else{

					y=y+2;

				}
			}

			if(tecla == ARRIBA){

				if(laberintov[y-1][x] == pared){

					Beep(250, 100);

				}else{

					y--;
				}
			}

			if(tecla == ABAJO){

				if(laberintov[y+1][x] == pared){

					Beep(250, 100);

				}else{

					y++;
				}
			}

			if(tecla == IZQUIERDA){

				if(laberintov[y][x-1] == pared){

					Beep(250, 100);

				}else{

					x--;
				}
			}

			if(tecla == DERECHA){

				if(laberintov[y][x+1] == pared){

					Beep(250, 100);

				}else{

					x++;
				}
			}

			gotoxy(x,y);
			printf("%c", char(219));
			num=laberintov[y][x];

			if(tecla == 27 /*TECLA ESC*/ || (x==40 && y==15) /*coordenadas S*/){
				game_over=true;
				cout<<puntuacion;
				Sleep(3000);
			}

		}
		Sleep(20);
	}

}

void cargar_laberinto_pares(laberinto_pares laberintop){

	for(int i=0; i<filas; i++){

		for(int j=0; j<columnas; j++){

			cout<<laberintop[i][j];
		}
		cout<<endl;
	}
}

void cargar_laberinto_impares(laberinto_impares laberintoi){

	for(int i=0; i<filas; i++){

		for(int j=0; j<columnas; j++){

			cout<<laberintoi[i][j];
		}
		cout<<endl;
	}

}

void cargar_laberinto_vocales(laberinto_vocales laberintov){

	for(int i=0; i<filas; i++){

		for(int j=0; j<columnas; j++){

			cout<<laberintov[i][j];
		}
		cout<<endl;
	}

}

void escribir_fichero_jugadores(regis_jug & rj){


	ofstream fo_jugadores;
	//Guardamos en el archivo el jugador nuevo

	fo_jugadores.open("jugadores.txt",ios::app);

	if(!fo_jugadores.fail()){

		fo_jugadores<<rj.vj[rj.cont].minick<<" ";
		fo_jugadores<<rj.vj[rj.cont].minombre<<" ";
		fo_jugadores<<rj.vj[rj.cont].nacion<<" ";
		fo_jugadores<<rj.vj[rj.cont].edad<<" ";
		fo_jugadores<<rj.vj[rj.cont].puntos<<" ";

	}

	fo_jugadores.close();


}

