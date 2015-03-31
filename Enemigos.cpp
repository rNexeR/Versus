#include "Enemigos.h"

Enemigos::Enemigos()
{
    clase = "Enemigo";
    detalles->x = rand()%500;
    detalles->y = 0;
}

int Enemigos::getTime(){
    return -1;
}

Enemigos::~Enemigos()
{
    //dtor
}
