#include "ObjetosAnimados.h"

ObjetosAnimados::ObjetosAnimados()
{
    //ctor
}

ObjetosAnimados::~ObjetosAnimados()
{
    al_destroy_bitmap(sprite);//destruir el bitmap para evitar SFs
    //dtor
}

void ObjetosAnimados::draw(){
    if (sprite)//si el sprite está cargado, dibujar
        al_draw_bitmap(sprite, detalles->x, detalles->y, 0);
}

bool ObjetosAnimados::collision(Box* pCaja){//para comparar colisiones...quizá
    if(pCaja->x + pCaja->width < detalles->x
        || pCaja->x > detalles->x + pCaja->width
        || pCaja->y + pCaja->height < detalles->y
        || pCaja->y > detalles->y + pCaja->height)
        return false;
    else
        return true;
}
