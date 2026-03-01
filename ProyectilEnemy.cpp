#include "ProyectilEnemy.h"
#include <conio2.h>

ProyectilEnemy::ProyectilEnemy(int posX, int posY) 
	: Proyectil(posX, posY, 3, LIGHTRED, 'x') {
	contadorMovimientoProyectil = 0;
}

void ProyectilEnemy::mover(){
	contadorMovimientoProyectil++;
	
	if(contadorMovimientoProyectil >= velocidad) {
		startY++;
		contadorMovimientoProyectil = 0;
	}
	
	if(startY >= 25) {
		activo = false;
		borrar();
	}
}
