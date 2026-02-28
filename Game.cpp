#include "Game.h"
#include <iostream>
#include <conio2.h>
#include "Player.h"
#include "BasicEnemy.h"
#include "AdvancedEnemy.h"
using namespace std;

Game::Game(int velocidad){
	velocidadJuego = velocidad;
	pasoJuego = CLOCKS_PER_SEC /velocidadJuego;
	tiempoJuego = clock();
	juegoActivo = true;
	contadorMovimiento = 0;
	
	jugador = new Player(35, BORDE_INF - 1 );
	
	cantidadBalas = 0;
	for(int i = 0; i < MAX_BALAS; i++) {
		balasJugador[i] = nullptr;
	}
	
	cantidadEnemigos = 0;
	direccionBloque = 1;
	for(int i = 0; i < MAX_ENEMIGOS; i++) {
		enemigos[i] = nullptr;
	}
	
	crearEnemigos();
	
	cantidadBalasEnemigas = 0;
	puntuacion = 0;
	contadorDisparosEnemigos = 0;
	for(int i = 0; i < MAX_BALAS; i++) {
		balasEnemigas[i] = nullptr;
	}
	
	maxDisparosEnemigosSimultaneos = 3;
	
}

Game::~Game() {
	delete jugador;
	
	for(int i = 0; i < MAX_BALAS; i++) {
		if(balasJugador[i] != nullptr) {
			delete balasJugador[i];
		}
	}
	
	// Libera memoria de enemigos
	for(int i = 0; i < MAX_ENEMIGOS; i++) {
		if(enemigos[i] != nullptr) {
			delete enemigos[i];
		}
	}
}


void Game::disparar() {
	
	for(int i = 0; i < MAX_BALAS; i++) {
		if(balasJugador[i] == nullptr) { 
			// Crear nueva bala en la posición del jugador
			balasJugador[i] = new ProyectilPlayer(
			jugador->getX() + 1,  // +1 para centrar (porque <A> ocupa 3)
			jugador->getY() - 1
			);
			cantidadBalas++;
			break;  // Sale después de crear una bala
		}
	}
}

void Game::actualizarBalas() {
	for(int i = 0; i < MAX_BALAS; i++) {
		if(balasJugador[i] != nullptr) {
			balasJugador[i]->actualizar();  // Cada bala se mueve sola
		}
	}
}

void Game::eliminarBalasInactivas() {
	for(int i = 0; i < MAX_BALAS; i++) {
		// Si la bala existe pero ya no está activa
		if(balasJugador[i] != nullptr && !balasJugador[i]->estaActivo()) {
			delete balasJugador[i];      // Libera memoria
			balasJugador[i] = nullptr;    // Marca como libre
			cantidadBalas--;
		}
	}
}

void Game::enemigosDisparan() {
	contadorDisparosEnemigos++;
	
	// Solo dispara si no se alcanzó el límite
	if(cantidadBalasEnemigas < maxDisparosEnemigosSimultaneos) {
		if(contadorDisparosEnemigos % 30 == 0) {
			for(int i = 0; i < MAX_ENEMIGOS; i++) {
				if(enemigos[i] != nullptr && enemigos[i]->estaVivo()) {
					if(rand() % 100 < 3) {
						for(int j = 0; j < MAX_BALAS; j++) {
							if(balasEnemigas[j] == nullptr) {
								balasEnemigas[j] = new ProyectilEnemy(
																	  enemigos[i]->getX() + 1,
																	  enemigos[i]->getY() + 1
																	  );
								cantidadBalasEnemigas++;
								break;
							}
						}
					}
				}
			}
		}
	}
	
	if(contadorDisparosEnemigos >= 1000) {
		contadorDisparosEnemigos = 0;
	}
}

void Game::actualizarBalasEnemigas() {
	for(int i = 0; i < MAX_BALAS; i++) {
		if(balasEnemigas[i] != nullptr) {
			balasEnemigas[i]->actualizar();
		}
	}
}

void Game::eliminarBalasEnemigasInactivas() {
	for(int i = 0; i < MAX_BALAS; i++) {
		if(balasEnemigas[i] != nullptr && !balasEnemigas[i]->estaActivo()) {
			delete balasEnemigas[i];
			balasEnemigas[i] = nullptr;
			cantidadBalasEnemigas--;
		}
	}
}

void Game::pantallaInicio(){
	textcolor(LIGHTGREEN);
	gotoxy(30, 5);
	cout<<"<o> SPACE INVADERS LITE <o>"<<endl;
	
	gotoxy(29, 6);
	cout<<"(INTRODUCCION A LA PROGRAMACION)"<<endl;
	
	textcolor(WHITE);
	gotoxy(29, 8);
	cout<<"ALUMNO: Jorge Salinas"<<endl;
	
	textcolor(LIGHTCYAN);
	gotoxy(20, 12);
	cout<<"INSTRUCCIONES: "<<endl;
	
	gotoxy(20, 13);
	cout<<"A mueve a la izquierda (<-)!"<<endl;
	
	gotoxy(20, 14);
	cout<<"D mueve a la derecha (->)!"<<endl;
	
	gotoxy(20, 15);
	cout<<"Space dispara (|)!"<<endl;
	
	gotoxy(20, 16);
	cout<<"Pierdes si te quedas sin vidas o si los enemigos bajan demasiado!"<<endl;
	
	gotoxy(20, 18);
	cout<<"TOCA CUALQUIER TECLA PARA COMENZAR!"<<endl;
	
	gotoxy(20, 19);
	cout<<"TOCA ESC PARA SALIR!"<<endl;
	
	getch();
	
	clrscr();
	
	// Dibuja bordes 
	for(int i = BORDE_IZQ; i <= BORDE_DER; i++) {
		gotoxy(i, BORDE_SUP); cout << ".";
		gotoxy(i, BORDE_INF); cout << ".";
	}
	for(int i = BORDE_SUP; i <= BORDE_INF; i++) {
		gotoxy(BORDE_IZQ, i); cout << ".";
		gotoxy(BORDE_DER, i); cout << ".";
	}
}
void Game::crearEnemigos() {
	// 3 filas de enemigos
	for(int fila = 0; fila < 3; fila++) {
		for(int col = 0; col < 8; col++) {
			if(cantidadEnemigos >= MAX_ENEMIGOS) break;
			
			int x = BORDE_IZQ + 5 + (col * 6);
			int y = BORDE_SUP + 2 + fila;
			
			// Primera fila: enemigos avanzados
			if(fila == 0) {
				enemigos[cantidadEnemigos] = new AdvancedEnemy(x, y);
			} 
			// Filas 2 y 3: enemigos básicos
			else {
				enemigos[cantidadEnemigos] = new BasicEnemy(x, y);
			}
			cantidadEnemigos++;
		}
	}
}

void Game::moverEnemigos() {
	contadorMovimiento++;
	
	
	if(contadorMovimiento % 5 == 0) {
		bool llegoAlBorde = false;
		
		// Borra a todos los enemigos
		for(int i = 0; i < MAX_ENEMIGOS; i++) {
			if(enemigos[i] != nullptr && enemigos[i]->estaVivo()) {
				enemigos[i]->borrar();
			}
		}
		
		//  Mueve a todos los enemigos
		for(int i = 0; i < MAX_ENEMIGOS; i++) {
			if(enemigos[i] != nullptr && enemigos[i]->estaVivo()) {
				enemigos[i]->mover(direccionBloque, llegoAlBorde);
			}
		}
		
		// Dibuja a todos
		for(int i = 0; i < MAX_ENEMIGOS; i++) {
			if(enemigos[i] != nullptr && enemigos[i]->estaVivo()) {
				enemigos[i]->dibujar();
			}
		}
		
		// Si tocan el borde, baja.
		if(llegoAlBorde) {
			direccionBloque *= -1;
			
			// Baja todos
			for(int i = 0; i < MAX_ENEMIGOS; i++) {
				if(enemigos[i] != nullptr && enemigos[i]->estaVivo()) {
					enemigos[i]->borrar();
				}
			}
			
			for(int i = 0; i < MAX_ENEMIGOS; i++) {
				if(enemigos[i] != nullptr && enemigos[i]->estaVivo()) {
					enemigos[i]->bajar();
					
					if(enemigos[i]->getY() >= BORDE_INF - 1) {
						juegoActivo = false;
					}
				}
			}
			
			for(int i = 0; i < MAX_ENEMIGOS; i++) {
				if(enemigos[i] != nullptr && enemigos[i]->estaVivo()) {
					enemigos[i]->dibujar();
				}
			}
		}
		
		// Resetea el contador para que no crezca infinito
		if(contadorMovimiento >= 1000) {
			contadorMovimiento = 0;
		}
	}
}

	
	


void Game::iniciar(){
	int contadorFrames = 0;
	
	pantallaInicio();
	jugador->dibujar();
	char tecla;
	
	while (juegoActivo){
		// CONTROL DE TIEMPO
		if(tiempoJuego + pasoJuego < clock()) {
			
			contadorFrames++;
			
			
			if (kbhit()){
				tecla = getch();
				
				if (tecla == 27) {  // ESC
					juegoActivo = false;
				}
				else if (tecla == 'a' || tecla == 'A') {
					jugador->moverIzquierda(BORDE_IZQ);
				}
				else if (tecla == 'd' || tecla == 'D') {
					jugador->moverDerecha(BORDE_DER);
				}
				else if (tecla == ' ') { //space
					disparar();
				}
				
			}
			
			actualizarBalas();
			actualizarBalasEnemigas();
			moverEnemigos();
			enemigosDisparan();
			gotoxy(50, 1);
			cout << "Balas: " << cantidadBalas << "   ";
			eliminarBalasInactivas();
			eliminarBalasEnemigasInactivas();
			tiempoJuego = clock();  // Actualiza tiempo
		}
	}
	
	// Mensaje de despedida
	clrscr();
	gotoxy(35, 12);
	textcolor(LIGHTRED);
	cout << "JUEGO TERMINADO";
	getch();
}

