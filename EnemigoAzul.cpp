#include "EnemigoAzul.h"

EnemigoAzul::EnemigoAzul(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos,ALLEGRO_DISPLAY *display, int level)
{
    velocity = 0.5;
    firingRate = 45;
    moveBy = 3;
    randomAlternative1 = 100;
    randomAlternative2 = 155;
    laserDmg = 4;

    vidas = 35;

    alternar = false;
    //carga de imagenes
    string path = "GameFiles/assets/personajes/enemies/blue/enemyBlue" + toString(level) + ".png";
    mapa_sprites[0] = vector<ALLEGRO_BITMAP*>();
    mapa_sprites[0].push_back(al_load_bitmap(path.c_str()));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    this->event_queue = event_queue;
    init(personajes, obstaculos, display);
    setAnimacion(0);
    disparos = new list<ObjetosAnimados*>;//Inicializar disparos
}


void EnemigoAzul::determinarRandomMovimiento(){
    if(alternar && detalles->x > 0){
        detalles->x -= moveBy;
        if(detalles->y > 100)
            detalles->y -= (moveBy);
    }else if (!alternar && detalles->x < 450){
        detalles->x += moveBy;
    }
}
EnemigoAzul::~EnemigoAzul()
{
}
