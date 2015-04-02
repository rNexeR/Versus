#include "Entidad.h"

Entidad::Entidad()
{
    //ctor
}

Entidad::~Entidad()
{
    //dtor
}

//Detecta si el objeto está colisionando o no
bool Entidad::colision(Box* detalles, Box* pCaja){
    if(pCaja->x + pCaja->width < detalles->x
        || pCaja->x-5 > detalles->x-5 + detalles->width-5
        || pCaja->y-5 + pCaja->height-5 < detalles->y-5
        || pCaja->y-5 > detalles->y-5 + detalles->height-5)
        return false;
    else
        return true;
}
