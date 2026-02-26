#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
protected:
	int x, y;
	bool vivo;
	int color;
	char simbolo;
	int puntos;
	
public:
	Enemy(int, int, int, char, int);
	virtual ~Enemy(){};
	virtual void dibujar();
	virtual void borrar();
	void mover(int direccion, bool& llegoAlBorde);
	void bajar();
	int getX() const { return x; }
	int getY() const { return y; }
	bool estaVivo() const { return vivo; }
	int getPuntos() const { return puntos; }
	
	void morir() { vivo = false; }
};

#endif
