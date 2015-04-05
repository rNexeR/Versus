#include "EnemigoVerde.h"

EnemigoVerde::EnemigoVerde(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, ALLEGRO_DISPLAY *display, int level)
{
    velocity = 0.2;
    firingRate = 35;
    moveBy = 5;
    laserDmg = 3;

    vidas = 20;

    alternar = false;
    //carga de imagenes
    string path = "GameFiles/assets/personajes/enemies/green/enemyGreen" + toString(level) + ".png";
    mapa_sprites[0] = vector<ALLEGRO_BITMAP*>();
    mapa_sprites[0].push_back(al_load_bitmap(path.c_str()));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    this->event_queue = event_queue;
    init(personajes, obstaculos, display);
    setAnimacion(0);
    disparos = new list<ObjetosAnimados*>;//Inicializar disparos
}

EnemigoVerde::~EnemigoVerde()
{
    //dtor
}
