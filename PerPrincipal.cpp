#include "PerPrincipal.h"

PerPrincipal::PerPrincipal(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos)
{
    tipoObjeto = "Principal";
    velocity = 5;
    init(personajes);
    if(!al_install_keyboard())
    {
        cout<<"failed to initialize the keyboard!"<<endl;
    }

    if(!al_init_image_addon())
    {
        cout<<"failed to initialize image addon!"<<endl;
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
    damage = al_load_bitmap("GameFiles/assets/personajes/principal/damage_flash.png");


    al_register_event_source(event_queue, al_get_keyboard_event_source());
//    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    //init(personajes, disparos_principal, disparos_enemigos, obstaculos);
    this->event_queue = event_queue;
    detalles->x = 250;
    detalles->y = 600;
}

int PerPrincipal::getTime()
{
    return frame/60;
}

void PerPrincipal::act(ALLEGRO_EVENT* ev)
{

    bool entro = false;
    validarTeclas(ev);

    //gravedad en el salto
    if (vidas<=0)
    {
        setAnimacion(orientacion == 'r' ? MUERTO_DERECHA : MUERTO_IZQUIERDA);
        entro = true;
    }
    else
    {

        if (detalles->y > 600)
        {
            detalles->y = 600;
            aceleracion_y = 0;
            setAnimacion(orientacion == 'r' ? PARADO_DERECHA : PARADO_IZQUIERDA);
            jump = false;
        }
        if(jump)
        {
            velocidad_y+=aceleracion_y;
            detalles->y+=velocidad_y;
            aceleracion_y+=gravedad;
            entro = true;
        }
        if(key[KEY_UP])
        {
            //detalles->y -= var;
            if(ev->type == ALLEGRO_EVENT_KEY_DOWN && ev->keyboard.keycode == ALLEGRO_KEY_P)
                cout<<"Disparando"<<endl;
            setAnimacion(orientacion == 'r' ? DISPARANDO_DERECHA : DISPARANDO_IZQUIERDA);
            entro = true;

        }
        if(ev->type == ALLEGRO_EVENT_KEY_DOWN && !jump && ev->keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            cout<<"Saltando"<<endl;
            velocidad_y = 0;
            aceleracion_y = -4.5;
            setAnimacion(orientacion == 'r' ? SALTANDO_DERECHA : SALTANDO_IZQUIERDA);
            jump = true;
            entro = true;
        }
        if (ev->type == ALLEGRO_EVENT_KEY_DOWN && !down && ev->keyboard.keycode == ALLEGRO_KEY_S)
        {
            //falta validar que este sobre una superficie
            cout<<"CAYENDO"<<endl;
        }

        if(key[KEY_LEFT] && detalles->x > 0)
        {
            detalles->x -= velocity;
            if(!jump && !down)
                setAnimacion(CAMINANDO_IZQUIERDA);
            orientacion = 'l';
            entro = true;
        }

        if(key[KEY_RIGHT] & detalles->x < 450)
        {
            detalles->x += velocity;
            if(!jump && !down)
                setAnimacion(CAMINANDO_DERECHA);
            orientacion = 'r';
            entro = true;
        }
        if (!entro)
            setAnimacion(orientacion == 'r' ? PARADO_DERECHA : PARADO_IZQUIERDA);
    }
}

void PerPrincipal::validarTeclas(ALLEGRO_EVENT* ev)
{
    if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(ev->keyboard.keycode)
        {
        case ALLEGRO_KEY_W:
            key[KEY_UP] = true;
            break;

        case ALLEGRO_KEY_S:
            key[KEY_DOWN] = true;
            break;

        case ALLEGRO_KEY_A:
            key[KEY_LEFT] = true;
            break;

        case ALLEGRO_KEY_D:
            key[KEY_RIGHT] = true;
            break;

//        case ALLEGRO_KEY_SPACE:
//            key[KEY_SPACE] = true;
//
//        case ALLEGRO_KEY_P:
//            key[KEY_SHOOT] = true;
        }
    }
    if(ev->type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(ev->keyboard.keycode)
        {
        case ALLEGRO_KEY_W:
            key[KEY_UP] = false;
            break;

        case ALLEGRO_KEY_S:
            key[KEY_DOWN] = false;
            break;

        case ALLEGRO_KEY_A:
            key[KEY_LEFT] = false;
            break;

        case ALLEGRO_KEY_D:
            key[KEY_RIGHT] = false;
            break;

//        case ALLEGRO_KEY_SPACE:
//            key[KEY_SPACE] = false;
//
//        case ALLEGRO_KEY_P:
//            key[KEY_SHOOT] = false;
        }
    }
}

PerPrincipal::~PerPrincipal()
{
    //dtor
}
