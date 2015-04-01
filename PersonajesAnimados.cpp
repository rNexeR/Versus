#include "PersonajesAnimados.h"

PersonajesAnimados::PersonajesAnimados()
{

}

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
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

void PersonajesAnimados::draw(){
    vector<ALLEGRO_BITMAP*> *vector_textura_actual_temp = mapa_sprites[mapa_actual];
    ALLEGRO_BITMAP* temp = (*vector_textura_actual_temp)[animacion_actual];
    if (frame%3==0){
        animacion_actual++;
        if (animacion_actual>=vector_textura_actual_temp->size())
            animacion_actual = 0;
    }

    if (temp)
        al_draw_bitmap(temp,detalles->x, detalles->y,0);
//    al_draw_scaled_bitmap(image[animacion],0,0,196,397,caja->x,caja->y,196,397,0);

    frame++;
    limpiarEnemigos();
}
void PersonajesAnimados::init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos){
    this->personajes = personajes;
    this->obstaculos = obstaculos;

    setAnimacion(PARADO_DERECHA);
    detalles->x = 50;
    detalles->y = 50;
    detalles->width = 50;
    detalles->height = 50;
    frame = 0;
    colisionado = false;
    muerto = false;
    orientacion = 'r';
    velocidad_y = 0;
    aceleracion_y = 0;
    gravedad = 0.5;
    al_init_timeout(&timeout, 0.06);
    //colisionado = false;
}

void PersonajesAnimados::init(list<PersonajesAnimados *> *personajes){
    this->personajes = personajes;
    disparos = NULL;
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
    al_init_timeout(&timeout, 0.06);
}

bool PersonajesAnimados::colision(Box* pCaja){
    if(pCaja->x + pCaja->width < detalles->x
        || pCaja->x > detalles->x + pCaja->width
        || pCaja->y + pCaja->height < detalles->y
        || pCaja->y > detalles->y + pCaja->height)
        return false;
    else
        return true;
}

void PersonajesAnimados::setAnimacion(int nombre){
    if(this->mapa_actual != nombre){
        this->mapa_actual = nombre;
        this->animacion_actual = 0;
    }
}

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

bool PersonajesAnimados::teclaDownEvent(int keycode)
{
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev.keyboard.keycode==keycode)
            return true;
    }
    return false;
}


void PersonajesAnimados::defenseCheck(){
//    if (clase=="principal"){
//        list<ObjetosAnimados*>::iterator i;
//        for(i=disparos_enemigos->begin(); i != disparos_enemigos->end(); i++){
//            if (colision((*i)->detalles))
//                colisionado =true;
//        }
//    }else if(clase=="enemigo"){
//        list<ObjetosAnimados*>::iterator i;
//        for(i=disparos_principal->begin(); i != disparos_principal->end(); i++){
//            if (colision((*i)->detalles))
//                colisionado =true;
//        }
//
//    }
}

int PersonajesAnimados::enumToInt(string animacion){
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
        else
            return -1;
}

PersonajesAnimados::~PersonajesAnimados()
{
    if (disparos != NULL && disparos->size() > 0)
        for(list<ObjetosAnimados*>::iterator i=disparos->begin(); i != disparos->end(); i++)
                delete (*i);

    for(int x = 0; x<mapa_sprites.size(); x++){
            vector<ALLEGRO_BITMAP*> *vector_temp = mapa_sprites[x];
            for(int y = 0; y<vector_temp->size();y++){
                al_destroy_bitmap((*vector_temp)[y]);
            }
            delete vector_temp;
    }
    delete detalles;
}

void PersonajesAnimados::limpiarEnemigos(){
    vector<list<PersonajesAnimados*>::iterator>borrar;
    for(list<PersonajesAnimados*>::iterator i=personajes->begin(); i != personajes->end(); i++){
        //cout<<"entro"<<endl;
        if ((*i)->clase == "Enemigo" && ((*i)->muerto == true || (*i)->detalles->y > 600)){
//            personajes->erase(i);
            borrar.push_back(i);
        }
    }
    for(int x = 0; x < borrar.size(); x++){
        personajes->erase(borrar[x]);
        delete (*borrar[x]);
    }
}
