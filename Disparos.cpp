#include "Disparos.h"

Disparos::Disparos(int dmg, int posX, int posY, int dir)
{
    this->dmg = dmg;
    string path = "GameFiles/assets/lasers/laserGreen.png";
    if (dir>0){
        velocity = -10;
    }else{
        velocity = 10;
        path = "GameFiles/assets/lasers/laserRed.png";
    }
    //Inicializaciones de audio

    if(!al_init_image_addon())//chequear si se pudo inicializar para las imágenes
    {
        cout<<"failed to initialize image addon!"<<endl;
    }

    //Inicialización de la posición de la cajita
    detalles->x = posX;
    detalles->y = posY;
    tipoObjeto = "Disparo";//declarar el tipo de ObjetoAnimado
    sprite = al_load_bitmap(path.c_str());//cargar el sprite según el path dado
    colisionado = false;
    if(!sprite)
        return;

    detalles->width = al_get_bitmap_width(sprite);
    detalles->height = al_get_bitmap_height(sprite);
}

Disparos::~Disparos()
{
    delete detalles;
}

void Disparos::act(ALLEGRO_EVENT *ev){
    detalles->y += velocity;
}

void Disparos::draw(){
    if (sprite){//si el sprite está cargado, dibujar
        al_draw_bitmap(sprite, detalles->x, detalles->y, 0);
    }
}





