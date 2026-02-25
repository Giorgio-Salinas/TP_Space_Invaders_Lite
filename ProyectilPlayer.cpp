#include "ProyectilPlayer.h"
#include <conio2.h>



ProyectilPlayer::ProyectilPlayer(int posX, int posY) : Proyectil(posX, posY, 30, YELLOW, '|') {
	
}

void ProyectilPlayer::mover() {
	startY--;  // Sube
	
	// Si llega al techo, se desactiva
	if(startY <= 1) {
		activo = false;
	}
}
