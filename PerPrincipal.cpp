#include "PerPrincipal.h"

PerPrincipal::PerPrincipal(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos)
{
    if(!al_install_keyboard())
    {
        cout<<"failed to initialize the keyboard!"<<endl;
    }

    if(!al_init_image_addon())
    {
        cout<<"failed to initialize image addon!"<<endl;
    }

//    timer = al_create_timer(1.0 / 60);
//    if(!timer)
//    {
//        cout<<"failed to create timer!"<<endl;
//    }

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


    al_register_event_source(event_queue, al_get_keyboard_event_source());
//    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    //init(personajes, disparos_principal, disparos_enemigos, obstaculos);
    this->event_queue = event_queue;
    init(personajes);
}

void PerPrincipal::act(ALLEGRO_EVENT* ev)
{
    bool entro = false;
    validarTeclas(ev);
    if(key[KEY_UP])
    {
        //detalles->y -= var;
        setAnimacion(orientacion == 'r' ? DISPARANDO_DERECHA : DISPARANDO_IZQUIERDA);
        entro = true;
    }

    if(key[KEY_DOWN])
    {
        detalles->y += var;
        entro = true;
    }

    if(key[KEY_LEFT])
    {
        detalles->x -= var;
        setAnimacion(CAMINANDO_IZQUIERDA);
        orientacion = 'l';
        entro = true;
    }

    if(key[KEY_RIGHT])
    {
        detalles->x += var;
        setAnimacion(CAMINANDO_DERECHA);
        orientacion = 'r';
        entro = true;
    }
    if (!entro)
        setAnimacion(orientacion == 'r' ? PARADO_DERECHA : PARADO_IZQUIERDA);
}

void PerPrincipal::validarTeclas(ALLEGRO_EVENT* ev){
    if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(ev->keyboard.keycode)
        {
        case ALLEGRO_KEY_UP:
            key[KEY_UP] = true;
            break;

        case ALLEGRO_KEY_DOWN:
            key[KEY_DOWN] = true;
            break;

        case ALLEGRO_KEY_LEFT:
            key[KEY_LEFT] = true;
            break;

        case ALLEGRO_KEY_RIGHT:
            key[KEY_RIGHT] = true;
            break;
        }
    }
    if(ev->type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(ev->keyboard.keycode)
        {
        case ALLEGRO_KEY_UP:
            key[KEY_UP] = false;
            break;

        case ALLEGRO_KEY_DOWN:
            key[KEY_DOWN] = false;
            break;

        case ALLEGRO_KEY_LEFT:
            key[KEY_LEFT] = false;
            break;

        case ALLEGRO_KEY_RIGHT:
            key[KEY_RIGHT] = false;
            break;
        }
    }
}

PerPrincipal::~PerPrincipal()
{
    //dtor
}
