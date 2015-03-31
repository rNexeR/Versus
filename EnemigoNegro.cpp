#include "EnemigoNegro.h"

EnemigoNegro::EnemigoNegro(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, int level)
{
    if(!al_init_image_addon())
    {
        cout<<"failed to initialize image addon!"<<endl;
    }


    //carga de imagenes
    string path = "GameFiles/assets/personajes/enemies/black/enemyBlack" + toString(level) + ".png";
    mapa_sprites[0] = new vector<ALLEGRO_BITMAP*>();
    mapa_sprites[0]->push_back(al_load_bitmap(path.c_str()));
//    string path = "GameFiles/initImages/enemigoNegroLvl"+toString(level)+".txt";
//    ifstream in(path.c_str());
//    if(!in)
//    {
//        cout<<"Error no se encontro el archivo!"<<endl;
//        return;
//    }
//    string animacion;
//    while(in>>animacion)
//    {
//        string llave;
//        in>>llave;
//        string path;
//        in>>path;
//        mapa_sprites[enumToInt(animacion)] = new vector<ALLEGRO_BITMAP*>();
//        while(path!="}")
//        {
//            mapa_sprites[enumToInt(animacion)]->push_back(al_load_bitmap(path.c_str()));
//            in>>path;
//        }
//    }


    al_register_event_source(event_queue, al_get_keyboard_event_source());
//    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    //init(personajes, disparos_principal, disparos_enemigos, obstaculos);
    this->event_queue = event_queue;
    init(personajes);
    setAnimacion(0);
}

void EnemigoNegro::act(ALLEGRO_EVENT* ev){
    detalles->y+=var;
    frame++;
}

EnemigoNegro::~EnemigoNegro()
{
    //dtor
}
