#include "Game.h"
#include <iostream>
#include <conio2.h>
#include "Player.h"
using namespace std;

Game::Game(int velocidad){
	velocidadJuego = velocidad;
	pasoJuego = CLOCKS_PER_SEC /velocidadJuego;
	tiempoJuego = clock();
	
	jugador = new Player(35, BORDE_INF - 1 );
	
	cantidadBalas = 0;
	for(int i = 0; i < MAX_BALAS; i++) {
		balasJugador[i] = nullptr;
	}
	
}

Game::~Game() {
	delete jugador;
	
	for(int i = 0; i < MAX_BALAS; i++) {
		if(balasJugador[i] != nullptr) {
			delete balasJugador[i];
		}
	}
}

void Game::disparar() {
	// Busca un espacio libre en el array
	for(int i = 0; i < MAX_BALAS; i++) {
		if(balasJugador[i] == nullptr) {  // Espacio libre
			// Crear nueva bala en la posición del jugador
			balasJugador[i] = new ProyectilPlayer(
												  jugador->getX() + 1,  // +1 para centrar (porque <A> ocupa 3)
												  jugador->getY() - 1
												  );
			cantidadBalas++;
			break;  // Salir después de crear UNA bala
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
		// Si la bala existe pero ya no esta activa
		if(balasJugador[i] != nullptr && !balasJugador[i]->estaActivo()) {
			delete balasJugador[i];      // Liberar memoria
			balasJugador[i] = nullptr;    // Marcar como libre
			cantidadBalas--;
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
	
	// Dibuja bordes después de limpiar
	for(int i = BORDE_IZQ; i <= BORDE_DER; i++) {
		gotoxy(i, BORDE_SUP); cout << ".";
		gotoxy(i, BORDE_INF); cout << ".";
	}
	for(int i = BORDE_SUP; i <= BORDE_INF; i++) {
		gotoxy(BORDE_IZQ, i); cout << ".";
		gotoxy(BORDE_DER, i); cout << ".";
	}
}


void Game::iniciar(){
	
	pantallaInicio();
	jugador->dibujar();
	bool juegoActivo(true);
	char tecla;
	
	while (juegoActivo){
		// CONTROL DE TIEMPO
		if(tiempoJuego + pasoJuego < clock()) {
			
			if (kbhit()){
				char tecla = getch();
				
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
			gotoxy(50, 1);
			cout << "Balas: " << cantidadBalas << "   ";
			eliminarBalasInactivas();
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

