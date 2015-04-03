#include "ObjetosAnimados.h"

ObjetosAnimados::ObjetosAnimados()
{
}

ObjetosAnimados::~ObjetosAnimados()
{
    al_destroy_bitmap(sprite);//destruir el bitmap para evitar SFs
}

void ObjetosAnimados::draw(){
    if (sprite){//si el sprite está cargado, dibujar
        al_draw_bitmap(sprite, detalles->x, detalles->y, 0);
    }
}

