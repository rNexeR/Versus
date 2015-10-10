/**
	Versus is a PC game programmed in C++ using the Allegro 5.0.11 library.
	Copyright (C) 2015  Nexer Rodríguez (rnexer) and Ricardo A. Interiano (Raim)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    For contact information read the README.md file.
**/

#include "PerPrincipal.h"

PerPrincipal::PerPrincipal(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, ALLEGRO_DISPLAY *display)
{
    tipoObjeto = "Principal";
    velocity = 5;
    vidas = 50;
    piso = 580;
    init(personajes, obstaculos, display);
    if(!al_install_keyboard())
    {
        cout<<"failed to initialize the keyboard!"<<endl;
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

//    event_queue = al_create_event_queue();
//    if(!event_queue)
//    {
//        cout<<"failed to create event_queue!\n"<<endl;
//        al_destroy_display(display);
//    }

    timer = al_create_timer(1.0 / 60);
    if(!timer)
    {
        cout<<"failed to create timer!"<<endl;
    }


    al_register_event_source(event_queue, al_get_timer_event_source(timer));//registrar eventos del timer
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    this->event_queue = event_queue;
    al_init_timeout(&timeout, 0.06);
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
            if (colision(detalles,(*i)->detalles))
            {
                Box temp((*i)->detalles->x-5,(*i)->detalles->y,(*i)->detalles->width-5, 15);
                if (colision(detalles,&temp))
                {
                    detalles->x+=(*i)->velocity;
                    return temp.y;
                }
            }
        }

    }
    return -1;
}

void PerPrincipal::act()
{
    cout<<"estoy actuando"<<endl;
    bool entro = false;
    bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
    if(get_event)
        validarTeclas();
    if (!jump && detalles->y < piso && isOnSolidGround()==-1)
    {
        down = true;
        setAnimacion(orientacion == 'r' ? CAYENDO_DERECHA : CAYENDO_IZQUIERDA);
    }

    if (vidas<=0)
    {
        setAnimacion(orientacion == 'r' ? MUERTO_DERECHA : MUERTO_IZQUIERDA);
        if (vidas<=-1)
        {
            muerto = true;
            al_rest(1);
        }
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
        }
        else if (down)
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
                down = false;
            }
        }

        if(key[KEY_UP] && !down && !key[KEY_LEFT] && !key[KEY_RIGHT] )
        {
            if(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_P )
            {
                int dx, dy;
                dx = orientacion == 'r' ? 15 : 25;
                dx = detalles->x + dx;
                dy = detalles->y-20;
                al_stop_sample(&idsonido);
                al_play_sample(sonido, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idsonido);
                disparos->push_back(new Disparos(5, dx, dy, 1));

            }
            setAnimacion(orientacion == 'r' ? DISPARANDO_DERECHA : DISPARANDO_IZQUIERDA);
            entro = true;

        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN && !jump && ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            velocidad_y = 0;
            aceleracion_y = -4.5;
            setAnimacion(orientacion == 'r' ? SALTANDO_DERECHA : SALTANDO_IZQUIERDA);
            jump = true;
            entro = true;
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

void PerPrincipal::validarTeclas()
{
    velocity = 5;
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(ev.keyboard.keycode)
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
    else if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(ev.keyboard.keycode)
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
        }
    }
//
//    else if (ev->type == ALLEGRO_EVENT_JOYSTICK_AXIS)
//    {
//        cout<<"JOYSTICK "<<frame<<endl;
//        if (ev->joystick.axis == 0)
//        {
//            int ax = ev->joystick.pos*10;
//            if(ax > 0)
//            {
//                key[KEY_RIGHT] = true;
//                velocity = ax;
//            }
//            else
//            {
//                key[KEY_LEFT] = true;
//                velocity = -ax;
//            }
//        }
//    }
}

PerPrincipal::~PerPrincipal()
{
}
