#ifndef PLAYER_H
#define PLAYER_H

class Player{
private:
	int vida;
	int x;
	int y;
	
public:
	Player(int posX, int posY);
	
	void dibujar();
	void borrar();
	void moverIzquierda(int bordeIzq);
	void moverDerecha(int bordeDer);
	int getX() const { return x; }
	int getY() const { return y; }
	int getVida() const { return vida; }
	void perderVida();
};

#endif
