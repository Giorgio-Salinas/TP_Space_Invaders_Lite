#ifndef PROYECTILPLAYER_H
#define PROYECTILPLAYER_H
#include "Proyectil.h"

class ProyectilPlayer : public Proyectil{
public:
	ProyectilPlayer(int posX, int posY);
	void mover();
};

#endif
