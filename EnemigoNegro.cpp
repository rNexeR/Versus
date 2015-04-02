#include "EnemigoNegro.h"

EnemigoNegro::EnemigoNegro(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, int level)
{
    velocity = 1;
    if(!al_init_image_addon())
    {
        cout<<"failed to initialize image addon!"<<endl;
    }

    alternar = false;
    //carga de imagenes
    string path = "GameFiles/assets/personajes/enemies/black/enemyBlack" + toString(level) + ".png";
    mapa_sprites[0] = vector<ALLEGRO_BITMAP*>();
    mapa_sprites[0].push_back(al_load_bitmap(path.c_str()));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    this->event_queue = event_queue;
    init(personajes);
    setAnimacion(0);
    disparos = new list<ObjetosAnimados*>;//Inicializar disparos
}

void EnemigoNegro::act(ALLEGRO_EVENT* ev){
    detalles->y+=velocity;
    int randomEstado = rand() % 100000;
    if(randomEstado % 57 == 0){//Si es divisible entre 31, entonces agregar el disparo
        disparos->push_back(new Disparos(1, detalles->x + 15, detalles->y + 40, 0));
    }

    randomizarMovimiento();

    frame++;
    if (detalles->y > 600)
        muerto = true;
}

void EnemigoNegro::randomizarMovimiento(){
    int randomNumber = rand() % 10000;
    if (randomNumber % 175 == 0){
        alternar = true;
    }else if (randomNumber % 125 == 0){
        alternar = false;
    }

    int moveBy = 2;

    if(alternar & detalles->x > 0){
        detalles->x -= moveBy;
    }else if (!alternar & detalles->x < 450){
        detalles->x += moveBy;
    }


}

EnemigoNegro::~EnemigoNegro()
{
    //dtor
}
