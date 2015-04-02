#include "PerPrincipal.h"

PerPrincipal::PerPrincipal(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos)
{
    tipoObjeto = "Principal";
    velocity = 5;
    vidas = 5;
    piso = 580;
    init(personajes, obstaculos);
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
        mapa_sprites[enumToInt(animacion)] = vector<ALLEGRO_BITMAP*>();
        while(path!="}")
        {
            mapa_sprites[enumToInt(animacion)].push_back(al_load_bitmap(path.c_str()));
            in>>path;
        }
    }
    damage = al_load_bitmap("GameFiles/assets/personajes/principal/damage_flash.png");


    al_register_event_source(event_queue, al_get_keyboard_event_source());

    this->event_queue = event_queue;
    detalles->x = 250;
    detalles->y = piso;
    disparos = new list<ObjetosAnimados*>;
}

int PerPrincipal::getTime()
{
    return frame/60;
}

int PerPrincipal::isOnSolidGround()
{
    if (detalles->y > piso)
        return piso+detalles->height+1;
    for(list<ObjetosAnimados*>::iterator i = obstaculos->begin(); i!=obstaculos->end(); i++)
    {
        if ((*i)->tipoObjeto == "Obstaculo")
        {
            if (colision((*i)->detalles))
            {
                Box temp((*i)->detalles->x-5,(*i)->detalles->y,(*i)->detalles->width-5, 0);
                if (colision(&temp)){
                    detalles->x+=(*i)->velocity;
                    return temp.y;
                }
            }
        }

    }
    return -1;
}

void PerPrincipal::act(ALLEGRO_EVENT* ev)
{
    bool entro = false;
    validarTeclas(ev);
    if (!jump && detalles->y < piso && isOnSolidGround()==-1){
        down = true;
        setAnimacion(orientacion == 'r' ? CAYENDO_DERECHA : CAYENDO_IZQUIERDA);
    }

    if (vidas<=0)
    {
        setAnimacion(orientacion == 'r' ? MUERTO_DERECHA : MUERTO_IZQUIERDA);
        entro = true;
    }
    else
    {


        if(jump)
        {
            velocidad_y+=aceleracion_y;
            detalles->y+=velocidad_y;
            aceleracion_y+=gravedad;
            entro = true;
            int pos = isOnSolidGround();
            if (pos>0)
            {
                detalles->y = pos-detalles->height-1;
                aceleracion_y = 0;
                setAnimacion(orientacion == 'r' ? PARADO_DERECHA : PARADO_IZQUIERDA);
                jump = false;
            }
        }else if (down){
            velocidad_y+=aceleracion_y;
            detalles->y+=velocidad_y;
            aceleracion_y+=gravedad;
            entro = true;
            int pos = isOnSolidGround();
            if (pos>0)
            {
                detalles->y = pos-detalles->height-1;
                aceleracion_y = 0;
                setAnimacion(orientacion == 'r' ? PARADO_DERECHA : PARADO_IZQUIERDA);
                down = false;
            }
        }

        if(key[KEY_UP])
        {
            if(ev->type == ALLEGRO_EVENT_KEY_DOWN && ev->keyboard.keycode == ALLEGRO_KEY_P){
                cout<<"Disparando"<<endl;
                disparos->push_back(new Disparos(5, detalles->x, detalles->y, 1));

            }
            setAnimacion(orientacion == 'r' ? DISPARANDO_DERECHA : DISPARANDO_IZQUIERDA);
            entro = true;

        }
        if(ev->type == ALLEGRO_EVENT_KEY_DOWN && !jump && ev->keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            velocidad_y = 0;
            aceleracion_y = -4.5;
            setAnimacion(orientacion == 'r' ? SALTANDO_DERECHA : SALTANDO_IZQUIERDA);
            jump = true;
            entro = true;
        }
//        if (ev->type == ALLEGRO_EVENT_KEY_DOWN && !down && ev->keyboard.keycode == ALLEGRO_KEY_S)
//        {
//            if (detalles->y < piso)
//            {
//                setAnimacion(orientacion == 'r' ? CAYENDO_DERECHA : CAYENDO_IZQUIERDA);
//                down = true;
////                aceleracion_y = 0.1;
//            }
//        }

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
