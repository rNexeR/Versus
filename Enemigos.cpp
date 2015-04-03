#include "Enemigos.h"

Enemigos::Enemigos()
{
    tipoObjeto = "Enemigo";
    detalles->x = rand()%450;
    detalles->y = 0;
    firingRate = 57;
    variablesRandomEstado = 100000;
    moveBy = 5;
}

int Enemigos::getTime(){
    return -1;
}

void Enemigos::act(ALLEGRO_EVENT* ev){
    detalles->y += velocity;
    int randomEstado = rand() % variablesRandomEstado;
    if(randomEstado % firingRate == 0){//Si es divisible entre firingRate, entonces agregar el disparo
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
