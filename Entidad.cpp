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
bool Entidad::colision(Box* pCaja){
    if(pCaja->x + pCaja->width < detalles->x
        || pCaja->x > detalles->x-5 + detalles->width-5
        || pCaja->y + pCaja->height < detalles->y-5
        || pCaja->y > detalles->y-5 + detalles->height-5)
        return false;
    else
        return true;
}
