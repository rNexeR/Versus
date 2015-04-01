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
        || pCaja->x > detalles->x + pCaja->width
        || pCaja->y + pCaja->height < detalles->y
        || pCaja->y > detalles->y + pCaja->height)
        return false;
    else
        return true;
}
