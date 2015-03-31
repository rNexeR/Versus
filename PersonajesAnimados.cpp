#include "PersonajesAnimados.h"

PersonajesAnimados::PersonajesAnimados()
{

}

void PersonajesAnimados::draw(){
    vector<ALLEGRO_BITMAP*> *vector_textura_actual_temp = mapa_sprites[mapa_actual];
    ALLEGRO_BITMAP* temp = (*vector_textura_actual_temp)[animacion_actual];
    if (frame%3==0){
        animacion_actual++;
        if (animacion_actual>=vector_textura_actual_temp->size())
            animacion_actual = 0;
    }

    al_draw_bitmap(temp,detalles->x, detalles->y,0);
//    al_draw_scaled_bitmap(image[animacion],0,0,196,397,caja->x,caja->y,196,397,0);

    frame++;
}
void PersonajesAnimados::init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos){
    this->personajes = personajes;
    this->obstaculos = obstaculos;

    setAnimacion(PARADO_DERECHA);
    detalles->x = 50;
    detalles->y = 50;
    detalles->width = 50;
    detalles->height = 50;
    frame = 0;
    colisionado = false;
    muerto = false;
    //colisionado = false;
}

void PersonajesAnimados::init(list<PersonajesAnimados *> *personajes){
    this->personajes = personajes;
    setAnimacion(PARADO_DERECHA);
    detalles->x = 50;
    detalles->y = 50;
    detalles->width = 50;
    detalles->height = 50;
    frame = 0;
    colisionado = false;
    muerto = false;
    al_init_timeout(&timeout, 0.06);
}

bool PersonajesAnimados::colision(Box* pCaja){
    if(pCaja->x + pCaja->width < detalles->x
        || pCaja->x > detalles->x + pCaja->width
        || pCaja->y + pCaja->height < detalles->y
        || pCaja->y > detalles->y + pCaja->height)
        return false;
    else
        return true;
}

void PersonajesAnimados::setAnimacion(int nombre){
    if(this->mapa_actual != nombre){
        this->mapa_actual = nombre;
        this->animacion_actual = 0;
    }
}

void PersonajesAnimados::teclaPresionada(int keycode, bool *variable)
{
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev.keyboard.keycode==keycode)
            *variable = true;
    }
    if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(ev.keyboard.keycode==keycode)
            *variable = false;
    }
}

bool PersonajesAnimados::teclaDownEvent(int keycode)
{
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev.keyboard.keycode==keycode)
            return true;
    }
    return false;
}


void PersonajesAnimados::defenseCheck(){
//    if (clase=="principal"){
//        list<ObjetosAnimados*>::iterator i;
//        for(i=disparos_enemigos->begin(); i != disparos_enemigos->end(); i++){
//            if (colision((*i)->detalles))
//                colisionado =true;
//        }
//    }else if(clase=="enemigo"){
//        list<ObjetosAnimados*>::iterator i;
//        for(i=disparos_principal->begin(); i != disparos_principal->end(); i++){
//            if (colision((*i)->detalles))
//                colisionado =true;
//        }
//
//    }
}

int PersonajesAnimados::enumToInt(string animacion){
        if (animacion=="PARADO_DERECHA")
            return 0;
        else if (animacion == "PARADO_IZQUIERDA")
            return 1;
        else if (animacion=="CAMINANDO_DERECHA")
            return 2;
        else if (animacion=="CAMINANDO_IZQUIERDA")
            return 3;
        else if (animacion=="DISPARANDO_DERECHA")
            return 4;
        else if (animacion=="DISPARANDO_IZQUIERDA")
            return 5;
        else
            return -1;
}

PersonajesAnimados::~PersonajesAnimados()
{
    //dtor
}
