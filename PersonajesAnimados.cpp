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

#include "PersonajesAnimados.h"

PersonajesAnimados::PersonajesAnimados()
{
    vidas = 3;
}


/**
    To-do: especificaciones por NXR
**/
string PersonajesAnimados::toString(int number)
{
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0; i<(int)temp.length(); i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

void PersonajesAnimados::draw()
{
    vector<ALLEGRO_BITMAP*> & vector_textura_actual_temp = mapa_sprites[mapa_actual];//setteamos un vector temporal
    //del mapa de sprites a dibujar según el mapa actual

    if(animacion_actual >= vector_textura_actual_temp.size())
    {
        animacion_actual = 0;
    }

    ALLEGRO_BITMAP* temp = (vector_textura_actual_temp)[animacion_actual]; //el bitmap a dibujar será igual al valor
    //que está apuntando la animación actual dentro del vector
    if (frame%3==0)
    {
        animacion_actual++;
        if (animacion_actual>=vector_textura_actual_temp.size())
            animacion_actual = 0;
    }

    if (temp) //mientras esté inicializado
    {
        int w, h;
        w = al_get_bitmap_width(temp);
        h = al_get_bitmap_height(temp);
        al_draw_scaled_bitmap(temp,0,0,w,h,detalles->x, detalles->y,50,50,0); //dibujar el bitmap
    }

    if (disparos)
    {
        for(list<ObjetosAnimados*>::iterator i = disparos->begin(); i != disparos->end(); i++)
        {
            (*i)->act(NULL);
            (*i)->draw();
        }
    }
    if (vidas>0)
    {
        int x = detalles->x, y = detalles->y - 10;
        int largo = vidas, ancho = 5;
        if(tipoObjeto == "Principal"){
            x = 0;
            largo = vidas * 500 / 50;
            y = 0;
        }else{

        }
        health = al_create_bitmap(largo, ancho);
        al_set_target_bitmap(health);

        al_clear_to_color(al_map_rgb(255, 0, 0));

        al_set_target_bitmap(al_get_backbuffer(display));
        al_draw_bitmap(health, x, y,0);
    }

    frame++;
    detectColision();
    limpiarEnemigos();
}

/**
    Función para inicializar los valores de un personaje
**/
void PersonajesAnimados::init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, ALLEGRO_DISPLAY *display)
{
    this->display = display;
    this->personajes = personajes;//settea el apuntador a la lista de personajes en el juego
    this->obstaculos = obstaculos;//settea el apuntador a la lista de obstaculos en el juego

    if(!al_init_image_addon())
    {
        cout<<"failed to initialize image addon!"<<endl;
    }

    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        return;
    }

    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return;
    }

    if (!al_reserve_samples(5)){
        fprintf(stderr, "failed to reserve samples!\n");
        return;
    }

    sonido = NULL;
    stop = NULL;

    sonido = al_load_sample( "GameFiles/music/sfx_laser2.wav" );
    stop = al_load_sample( "GameFiles/music/stop.wav" );

    if(!sonido || !stop){
        printf( "Audio clip sample not loaded!\n" );
        return;
    }
    al_play_sample(sonido, 0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idsonido);
    al_play_sample(stop, 0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idstop);

    disparos = NULL;
    animacion_actual = 0;
    mapa_actual = 0;
    setAnimacion(PARADO_DERECHA);
    detalles->width = 50;
    detalles->height = 50;
    frame = 0;
    colisionado = false;
    muerto = false;
    orientacion = 'r';
    velocidad_y = 0;
    aceleracion_y = 0;
    gravedad = 0.8;
    jump = false;
    down = false;
    damage = NULL;
    al_init_timeout(&timeout, 0.06);//tiempo de espera para eventos
}

/**
    Settea la animación del personaje según el nombre de esta misma;
    si el valor del mapa_actual es distinto entonces cambia el mapa
    y settea las animaciones desde 0 para evitar problemas
**/
void PersonajesAnimados::setAnimacion(int nombre)
{
    if(this->mapa_actual != nombre)
    {
        this->mapa_actual = nombre;
        this->animacion_actual = 0;
    }
}

/**
    Determina si una tecla está siendo presionada o no
**/
void PersonajesAnimados::teclaPresionada(int keycode, bool *variable)
{
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev.keyboard.keycode==keycode)
            *variable = true;
    }
    if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(ev.keyboard.keycode==keycode)
            *variable = false;
    }
}

/**
    Comprueba que valor es el de la tecla que se ha presionado.
    Recibe el keycode (int) y los compara
**/
bool PersonajesAnimados::teclaDownEvent(int keycode)
{
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev.keyboard.keycode==keycode)
            return true;
    }
    return false;
}


/**
    ???
**/
void PersonajesAnimados::detectColision()
{
    //con otros personajes
    for(list<PersonajesAnimados*>::iterator i = personajes->begin(); i!=personajes->end(); i++)
    {
        if ((*i)->tipoObjeto != tipoObjeto)
        {
            if (colision(detalles,(*i)->detalles))
                if (tipoObjeto == "Enemigo")
                {
                    muerto = true;
                    getPrincipal()->vidas -= 10;
                }
        }
    }

    for(list<ObjetosAnimados*>::iterator e = obstaculos->begin(); e != obstaculos->end(); e++)
            {
                if ((*e)->tipoObjeto == "Disparo")
                {

                    if(((*e)->velocity > 0 && tipoObjeto == "Principal") || ((*e)->velocity < 0 && tipoObjeto != "Principal"))
                    if (colision(detalles,(*e)->detalles))
                    {
                        if (tipoObjeto == "Principal")
                            al_draw_bitmap(damage, detalles->x-10, detalles->y-10,0);
                        this->vidas -= ((Disparos*)(*e))->dmg;//Casting a Disparos* porque dmg es un atributo de clase hija
                        (*e)->colisionado = true;
                    }
                }
            }

    //disparos contra obstaculos
    for(list<ObjetosAnimados*>::iterator i = obstaculos->begin(); i != obstaculos->end(); i++)
    {
        if ((*i)->tipoObjeto == "Obstaculo")
        {
            for(list<ObjetosAnimados*>::iterator e = obstaculos->begin(); e != obstaculos->end(); e++)
            {
                if ((*e)->tipoObjeto == "Disparo")
                {
                    if (colision((*e)->detalles, (*i)->detalles))
                    {
                        (*e)->colisionado = true;
                        //borrar.push_back(e);
                        al_stop_sample(&idstop);
                        al_play_sample(stop, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idstop);
                    }
                }
            }
        }
    }
}

/**
    Devuelve él valor int de la animación según su string en el enum
**/
int PersonajesAnimados::enumToInt(string animacion)
{
    if (animacion=="PARADO_DERECHA")
        return 0;
    else if (animacion == "PARADO_IZQUIERDA")
        return 1;
    else if (animacion=="CAMINANDO_DERECHA")
        return 2;
    else if (animacion=="CAMINANDO_IZQUIERDA")
        return 3;
    else if (animacion=="DISPARANDO_DERECHA")
        return 4;
    else if (animacion=="DISPARANDO_IZQUIERDA")
        return 5;
    else if (animacion=="SALTANDO_DERECHA")
        return 6;
    else if (animacion=="SALTANDO_IZQUIERDA")
        return 7;
    else if (animacion=="CAYENDO_DERECHA")
        return 8;
    else if (animacion=="CAYENDO_IZQUIERDA")
        return 9;
    else if (animacion=="MUERTO_DERECHA")
        return 10;
    else if (animacion=="MUERTO_IZQUIERDA")
        return 11;
    else
        return -1;
}

/**
    Destructor de PersonajesAnimados; aqui eliminamos los recursos una vez hayamos terminado
**/
PersonajesAnimados::~PersonajesAnimados()
{
    if (disparos != NULL && disparos->size() > 0)
        for(list<ObjetosAnimados*>::iterator i=disparos->begin(); i != disparos->end(); i++)
            delete (*i);

    for(int x = 0; x<mapa_sprites.size(); x++) //recorrremos el mapa de sprites
    {
        vector<ALLEGRO_BITMAP*> &vector_temp = mapa_sprites[x];//obtenemos el vector en esa posición
        for(int y = 0; y < vector_temp.size(); y++) //recorremos el vector
        {
            al_destroy_bitmap((vector_temp)[y]);//destruimos los bitmaps en esta posición
        }
    }
    delete detalles;
    if(damage!=NULL)
        al_destroy_bitmap(damage);//Destruir el bitmap; innecesario el delete
    al_destroy_sample(sonido);
    al_destroy_sample(stop);
    al_destroy_bitmap(health);
}

PersonajesAnimados* PersonajesAnimados::getPrincipal()
{
    for(list<PersonajesAnimados*>::iterator i = personajes->begin(); i!=personajes->end(); i++)
    {
        if ((*i)->tipoObjeto == "Principal")
            return (*i);
    }
}

/**
    Realiza la limpieza de todas las variables necesarias; evitamos problemas de SF
**/
void PersonajesAnimados::limpiarEnemigos()
{
    for(list<PersonajesAnimados*>::iterator i=personajes->begin(); i != personajes->end(); i++)
    {
        //Comparar que no tenga vida el personaje tampoco
        if ((*i)->tipoObjeto == "Enemigo" && (*i)->detalles->y > 600) //si está muerto o se paso
        {
            getPrincipal()->vidas -= 10;//añadir a los de borrar
        }
    }
    vector<list<ObjetosAnimados*>::iterator>bdisparos;
    for(list<ObjetosAnimados*>::iterator e = obstaculos->begin(); e != obstaculos->end(); e++)
    {
        if ((*e)->tipoObjeto == "Disparo" && (*e)->colisionado)
            bdisparos.push_back(e);
    }
    for(int x = 0; x < bdisparos.size(); x++) //recorrer los que morirán
    {
        disparos->erase(bdisparos[x]);
        delete (*bdisparos[x]);
    }
}
