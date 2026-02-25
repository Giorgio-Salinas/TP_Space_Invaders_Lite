#ifndef GAME_H
#define GAME_H
#include <conio2.h>
#include <ctime>
#include "Player.h"
#include "ProyectilPlayer.h"

class Game{
private:
	static const int MAX_BALAS = 100;
	static const int MAX_ENEMIGOS = 30;
	static const int BORDE_IZQ = 2;
	static const int BORDE_DER = 80;
	static const int BORDE_SUP = 1;
	static const int BORDE_INF = 25;
	
	//control de tiempo.
	clock_t tiempoJuego;
	clock_t pasoJuego;
	int velocidadJuego;
	Player* jugador;
	ProyectilPlayer* balasJugador[MAX_BALAS];
	int cantidadBalas;
public:
	Game(int velocidad = 40);
	~Game();
	void pantallaInicio();
	void iniciar();
	void disparar();
	void actualizarBalas();
	void eliminarBalasInactivas();
};

#endif
