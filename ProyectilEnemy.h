#ifndef PROYECTILENEMIGO_H
#define PROYECTILENEMIGO_H
#include "Proyectil.h"

class ProyectilEnemy : public Proyectil{
private: 
	int contadorMovimientoProyectil;
public:
	ProyectilEnemy(int, int);
	void mover();
};

#endif
