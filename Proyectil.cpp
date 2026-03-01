#include <iostream>
#include "Proyectil.h"
#include <conio2.h>
using namespace std;

Proyectil::Proyectil(int sx, int sy, int vel, int col, char simb){
	startX = sx;
	startY = sy;
	velocidad = vel;
	color = col;
	simbolo = simb;
	activo = true;
	
}

void Proyectil::dibujar(){
	if (activo){
	gotoxy(startX, startY);
	textcolor(color);
	cout << simbolo;
	}
}

void Proyectil::borrar(){
	if (activo){
	gotoxy(startX, startY);
	cout << " ";
	}
}


void Proyectil::actualizar(){
	if(activo) {
		borrar();
		mover();
		if(activo) {
			dibujar();
		}
	}
}
