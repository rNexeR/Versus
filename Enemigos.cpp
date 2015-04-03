#include "Enemigos.h"

Enemigos::Enemigos()
{
    tipoObjeto = "Enemigo";
    detalles->x = rand()%450;
    detalles->y = 0;
}

int Enemigos::getTime(){
    return -1;
}

void Enemigos::act(ALLEGRO_EVENT* ev){
    detalles->y+=velocity;
    int randomEstado = rand() % 100000;
    if(randomEstado % 57 == 0){//Si es divisible entre 31, entonces agregar el disparo
        al_stop_sample(&idsonido);
        al_play_sample(sonido, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idsonido);
        disparos->push_back(new Disparos(1, detalles->x + 15, detalles->y + 40, 0));
    }

    randomizarMovimiento();

    frame++;
    if (detalles->y > 600 || vidas < 0)
        muerto = true;
}

Enemigos::~Enemigos()
{
}
