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
#include <conio2.h>
#include <conio.h>
#include <windows.h>

//Costantes



//Tipos de datos



using namespace std;

//Cabeceras de modulos
int menu(void);

int main() {

	int opcion;

	clrscr();
	opcion=menu();

	while(opcion!=7){

		switch (opcion) {
		case 1:
			clrscr();
			cout<<"**************** Registrar jugador. ****************"<<endl;
			Sleep(2000);
			clrscr();
			break;
		case 2:
			clrscr();
			cout<<"**************** Jugador existente. ****************"<<endl;
			Sleep(2000);
			clrscr();
			break;
		case 3:
			clrscr();
			cout<<"**************** Caza de numeros pares.****************"<<endl;
			Sleep(2000);
			clrscr();
			break;
		case 4:
			clrscr();
			cout<<"**************** Caza de numeros impares. ****************"<<endl;
			Sleep(2000);
			clrscr();
			break;
		case 5:
			clrscr();
			cout<<"**************** Caza de vocales. ****************"<<endl;
			Sleep(2000);
			clrscr();
			break;
		case 6:
			clrscr();
			cout<<"**************** Mostrar fichero de jugadores. ****************"<<endl;
			Sleep(2000);
			clrscr();
			break;
		default:
			break;

		}

		opcion=menu();
	}

	return 0;
}

int menu(void){

	int opcion;

	clrscr();
	textcolor(WHITE);
	cout<<"1.- Registrar jugador nuevo."<<endl;
	cout<<"2.- Jugador existente."<<endl;
	cout<<"3.- Caza de numeros pares."<<endl;
	cout<<"4.- Caza de numeros impares."<<endl;
	cout<<"5.- Caza de vocales."<<endl;
	cout<<"6.- Mostrar fichero de jugadores."<<endl;
	cout<<"7.- Fin."<<endl;
	cout<<"Introduce la opcion que desees realizar: ";
	cin>>opcion;

	while(opcion<1 || opcion>7){
		cout<<"Error, vuelva a introducir una opcion valida: ";
		cin>>opcion;
	}

	return opcion;

}
