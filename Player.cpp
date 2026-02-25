#include <iostream>
#include "Player.h"
#include <conio2.h>
using namespace std;

Player::Player(int posX, int posY){
	x = posX;
	y = posY;
	vida = 3;
}

void Player::dibujar(){
	gotoxy(x, y);
	textcolor(RED);
	cout<<"<A>";
}

void Player::borrar(){
	gotoxy(x, y);
	cout<<"   ";
}

void Player::moverIzquierda(int bordeIzq){
	if(x > bordeIzq + 1) {  // +1 para no chocar con el borde
		borrar();
		x--;
		dibujar();
	}
}

void Player::moverDerecha(int bordeDer){
	if(x < bordeDer - 3) {  // -3 para no chocar con el borde
		borrar();
		x++;
		dibujar();
	}
}

void Player::perderVida(){
	vida--;
	if(vida < 0) vida = 0;
}
