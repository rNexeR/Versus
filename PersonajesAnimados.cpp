#include "PersonajesAnimados.h"

PersonajesAnimados::PersonajesAnimados()
{
    animacion_actual = 0;
    frame = 0;
    mapa_actual = 0;

    protegido = false;
    colisionado = false;
    muerto = false;
    quitarVidas = false;
}

void PersonajesAnimados::draw(ALLEGRO_EVENT* ev){
    vector<ALLEGRO_BITMAP*> *vector_textura_actual_temp = mapa_sprites[mapa_actual];
    ALLEGRO_BITMAP* temp = (*vector_textura_actual_temp)[animacion_actual];
    if (frame%3==0){
        animacion_actual++;
        if (animacion_actual>=vector_textura_actual_temp->size())
            animacion_actual = 0;
    }

    al_draw_bitmap(temp,200,200,0);
//    al_draw_scaled_bitmap(image[animacion],0,0,196,397,caja->x,caja->y,196,397,0);

    frame++;
}
void PersonajesAnimados::init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*disparos_principal, list<ObjetosAnimados*>*disparos_enemigos, list<ObjetosAnimados*>*obstaculos){
    this->personajes = personajes;
    this->disparos_principal = disparos_principal;
    this->disparos_enemigos = disparos_enemigos;
    this->obstaculos = obstaculos;
    colisionado = false;
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
    if(this->animacion_actual != nombre)
        this->mapa_actual = 0;
    this->animacion_actual = nombre;
}

void PersonajesAnimados::defenseCheck(){
    if (clase=="principal"){
        list<ObjetosAnimados*>::iterator i;
        for(i=disparos_enemigos->begin(); i != disparos_enemigos->end(); i++){
            if (colision((*i)->detalles))
                colisionado =true;
        }
    }else if(clase=="enemigo"){
        list<ObjetosAnimados*>::iterator i;
        for(i=disparos_principal->begin(); i != disparos_principal->end(); i++){
            if (colision((*i)->detalles))
                colisionado =true;
        }

    }
}

int enumToInt(string animacion){
        if (animacion=="PARADO")
            return 0;
        else if (animacion=="CAMINANDO_DERECHA")
            return 1;
        else if (animacion=="CAMINANDO_IZQUIERDA")
            return 2;
        else if (animacion=="DISPARANDO_DERECHA")
            return 3;
        else if (animacion=="DISPARANDO_IZQUIERDA")
            return 4;
        else if (animacion=="MUERTO")
            return 5;
        else
            return -1;
}

PersonajesAnimados::~PersonajesAnimados()
{
    //dtor
}
