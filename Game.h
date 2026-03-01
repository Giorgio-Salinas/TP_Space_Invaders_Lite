#ifndef GAME_H
#define GAME_H
#include <conio2.h>
#include <ctime>
#include "Player.h"
#include "ProyectilPlayer.h"
#include "Enemy.h"
#include "ProyectilEnemy.h"

class Game{
private:
	static const int MAX_BALAS = 100;
	static const int MAX_ENEMIGOS = 30;
	static const int BORDE_IZQ = 2;
	static const int BORDE_DER = 80;
	static const int BORDE_SUP = 1;
	static const int BORDE_INF = 25;
	int contadorMovimiento;
	bool juegoActivo;
	
	
	clock_t tiempoJuego;
	clock_t pasoJuego;
	int velocidadJuego;
	Player* jugador;
	ProyectilPlayer* balasJugador[MAX_BALAS];
	int cantidadBalas;
	Enemy* enemigos[MAX_ENEMIGOS];
	int cantidadEnemigos;
	int direccionBloque;
	ProyectilEnemy* balasEnemigas[MAX_BALAS];
	int cantidadBalasEnemigas;
	int puntuacion;
	int contadorDisparosEnemigos;
	int maxDisparosEnemigosSimultaneos;
public:
	Game(int velocidad = 30);
	~Game();
	void pantallaInicio();
	void iniciar();
	void disparar();
	void actualizarBalas();
	void eliminarBalasInactivas();
	void crearEnemigos();
	void moverEnemigos();
	void enemigosDisparan();
	void actualizarBalasEnemigas();
	void eliminarBalasEnemigasInactivas();
	void colisiones();
};

#endif
