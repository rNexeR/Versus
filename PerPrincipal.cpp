#include "PerPrincipal.h"

PerPrincipal::PerPrincipal(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*disparos_principal, list<ObjetosAnimados*>*disparos_enemigos, list<ObjetosAnimados*>*obstaculos)
{
    if(!al_install_keyboard()) {
      cout<<"failed to initialize the keyboard!"<<endl;
    }

    if(!al_init_image_addon()) {
      cout<<"failed to initialize image addon!"<<endl;
    }

    timer = al_create_timer(1.0 / 60);
    if(!timer) {
        cout<<"failed to create timer!"<<endl;
    }

    //carga de imagenes
    ifstream in("GameFiles/initImages/principal.txt");
    if(!in)
    {
        cout<<"Error no se encontro el archivo!"<<endl;
        return;
    }
    string animacion;
    while(in>>animacion)
    {
        string llave;
        in>>llave;
        string path;
        in>>path;
        mapa_sprites[enumToInt(animacion)] = new vector<ALLEGRO_BITMAP*>();
        while(path!="}")
        {
            cout<<path<<endl;
            mapa_sprites[enumToInt(animacion)]->push_back(al_load_bitmap(path.c_str()));
            in>>path;
        }
    }

    setAnimacion(PARADO_DERECHA);
    detalles->x = 50;
    detalles->y = 50;
    detalles->width = 50;
    detalles->height = 50;
    frame = 0;
    colisionado = false;
    muerto = false;
    cout<<"Creacion Finalizada"<<endl;


    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    //init(personajes, disparos_principal, disparos_enemigos, obstaculos);
    init(personajes);
}

void PerPrincipal::act(ALLEGRO_EVENT* ev){
    cout<<"Actuando"<<endl;
}

PerPrincipal::~PerPrincipal()
{
    //dtor
}
