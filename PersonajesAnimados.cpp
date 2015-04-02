#include "PersonajesAnimados.h"

PersonajesAnimados::PersonajesAnimados()
{

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
//    al_draw_scaled_bitmap(image[animacion],0,0,196,397,caja->x,caja->y,196,397,0);

    if (disparos)
    {
        for(list<ObjetosAnimados*>::iterator i = disparos->begin(); i != disparos->end(); i++)
        {
            (*i)->act(NULL);
            (*i)->draw();
        }
    }

    frame++;
    detectColision();
    limpiarEnemigos();
}

/**
    Función para inicializar los valores de un personaje
**/
void PersonajesAnimados::init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos)
{
    this->personajes = personajes;//settea el apuntador a la lista de personajes en el juego
    this->obstaculos = obstaculos;//settea el apuntador a la lista de obstaculos en el juego
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

/*
if(param.x + param.w < hitbox.x
            || param.x > hitbox.x + hitbox.w
            || param.y + param.h < hitbox.y
            || param.y > hitbox.y + hitbox.h)
*/

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
                cout<<"colision con "<<(*i)->tipoObjeto<<endl;
            else
            {
                //con las balas de otros
                for(list<ObjetosAnimados*>::iterator e = (*i)->disparos->begin(); e != (*i)->disparos->end(); e++)
                {
                    if ((*e)->tipoObjeto == "Disparo")
                    {
                        if (colision(detalles,(*e)->detalles))
                            cout<<"Colision con disparo"<<endl;
                    }
                }
            }

        }
    }

    //disparos contra obstaculos
    vector<list<ObjetosAnimados*>::iterator>borrar;
    for(list<ObjetosAnimados*>::iterator i = obstaculos->begin(); i != obstaculos->end(); i++)
    {
        if ((*i)->tipoObjeto == "Obstaculo")
        {
            for(list<ObjetosAnimados*>::iterator e = disparos->begin(); e != disparos->end(); e++)
                {
                    if ((*e)->tipoObjeto == "Disparo")
                    {
                        if (colision((*e)->detalles, (*i)->detalles)){
                            borrar.push_back(e);
                            al_stop_sample(&idstop);
                            al_play_sample(stop, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idstop);
                        }
                    }
                }
        }
    }
    for(int x = 0; x < borrar.size(); x++) //recorrer los que morirán
    {
        disparos->erase(borrar[x]);
        delete (*borrar[x]);
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
//            delete vector_temp; //eliminamos el apuntador del vector temporal
    }
    delete detalles;
    if(damage!=NULL)
        al_destroy_bitmap(damage);//Destruir el bitmap; innecesario el delete
    //al_destroy_sample(sonido);
}

/**
    Realiza la limpieza de todas las variables necesarias; evitamos problemas de SF
**/
void PersonajesAnimados::limpiarEnemigos()
{
    vector<list<PersonajesAnimados*>::iterator>borrar;
    for(list<PersonajesAnimados*>::iterator i=personajes->begin(); i != personajes->end(); i++)
    {
        //cout<<"entro"<<endl;
        if ((*i)->tipoObjeto == "Enemigo" && ((*i)->muerto == true || (*i)->detalles->y > 600)) //si está muerto o se paso
        {
//            personajes->erase(i);
            borrar.push_back(i);//añadir a los de borrar
        }
    }
    for(int x = 0; x < borrar.size(); x++) //recorrer los que morirán
    {
        personajes->erase(borrar[x]);
        delete (*borrar[x]);
    }
}
