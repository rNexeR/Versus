#include "Enemigos.h"

Enemigos::Enemigos()
{
    tipoObjeto = "Enemigo";
    detalles->x = rand()%450;
    detalles->y = 0;
}

int Enemigos::getTime(){
    return -1;
}

Enemigos::~Enemigos()
{
}
