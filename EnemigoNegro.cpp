#include "EnemigoNegro.h"

EnemigoNegro::EnemigoNegro(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, ALLEGRO_DISPLAY *display, int level)
{
    velocity = 1;
    moveBy = 2;

    vidas = 5;

    alternar = false;
    //carga de imagenes
    string path = "GameFiles/assets/personajes/enemies/black/enemyBlack" + toString(level) + ".png";
    mapa_sprites[0] = vector<ALLEGRO_BITMAP*>();
    mapa_sprites[0].push_back(al_load_bitmap(path.c_str()));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    this->event_queue = event_queue;
    init(personajes, obstaculos, display);
    setAnimacion(0);
    disparos = new list<ObjetosAnimados*>;//Inicializar disparos
}


EnemigoNegro::~EnemigoNegro()
{
}
