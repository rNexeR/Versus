#include "EnemigoNegro.h"

EnemigoNegro::EnemigoNegro(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, int level)
{
    var = 3;
    if(!al_init_image_addon())
    {
        cout<<"failed to initialize image addon!"<<endl;
    }


    //carga de imagenes
    string path = "GameFiles/assets/personajes/enemies/black/enemyBlack" + toString(level) + ".png";
    mapa_sprites[0] = new vector<ALLEGRO_BITMAP*>();
    mapa_sprites[0]->push_back(al_load_bitmap(path.c_str()));


    al_register_event_source(event_queue, al_get_keyboard_event_source());
    this->event_queue = event_queue;
    init(personajes);
    setAnimacion(0);
}

void EnemigoNegro::act(ALLEGRO_EVENT* ev){
    detalles->y+=var;
    frame++;
    if (detalles->y > 600)
        muerto = true;
}

EnemigoNegro::~EnemigoNegro()
{
    //dtor
}
