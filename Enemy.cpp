#include "Enemy.h"
#include <iostream>
#include <conio2.h>
using namespace std;

Enemy::Enemy(int posX, int posY, int col, char simb, int pts){
	x = posX;
	y = posY;
	color = col;
	simbolo = simb;
	puntos = pts;
	vivo = true;
}

void Enemy::dibujar() {
	if(vivo) {
		gotoxy(x, y);
		textcolor(color);
		cout<<simbolo;
	}
}

void Enemy::borrar() {
	if(vivo) {
		gotoxy(x, y);
		cout << " ";
	}
}

void Enemy::mover(int direccion, bool& llegoAlBorde) {
	if(vivo) {
		borrar();
		x += direccion;
		
		if(x <= 3 || x >= 79) {
			llegoAlBorde = true;
		}
		
		dibujar();
	}
}void Enemy::bajar() {
	if(vivo) {
		borrar();
		y++;
		dibujar();
	}
}
