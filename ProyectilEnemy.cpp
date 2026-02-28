#include "ProyectilEnemy.h"
#include <conio2.h>

ProyectilEnemy::ProyectilEnemy(int posX, int posY) 
	: Proyectil(posX, posY, 5, LIGHTRED, '*') {
	contadorMovimientoProyectil = 0;
}

void ProyectilEnemy::mover(){
	contadorMovimientoProyectil++;
	
	if(contadorMovimientoProyectil >= velocidad) {
		startY++;
		contadorMovimientoProyectil = 0;
	}
	
	if(startY >= 24) {
		activo = false;
		borrar();
	}
}
