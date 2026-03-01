#ifndef PROYECTIL_H
#define PROYECTIL_H

class Proyectil{
protected:
	int startX, startY;
	int velocidad;
	int color;
	char simbolo;
	bool activo;
	
public:
	Proyectil(int, int, int, int, char);
	virtual void dibujar();
	virtual void borrar();
	virtual void mover() = 0;
	virtual void actualizar();
	
	int getX() const { return startX; }
	int getY() const { return startY; }
	bool estaActivo() const { return activo; }
	void desactivar() { activo = false; }
};

#endif
