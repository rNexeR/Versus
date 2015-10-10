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

#include "Enemigos.h"

Enemigos::Enemigos()
{
    tipoObjeto = "Enemigo";
    detalles->x = rand() % 450;
    detalles->y = 0;
    firingRate = 57;
    variablesRandomEstado = 100000;
    moveBy = 5;
    laserDmg = 1;
    randomAlternative1 = 175;
    randomAlternative2 = 125;
}

int Enemigos::getTime(){
    return -1;
}

void Enemigos::act(){
    detalles->y += velocity;

    int randomEstado = rand() % variablesRandomEstado;

    if(randomEstado % firingRate == 0){//Si es divisible entre firingRate, entonces agregar el disparo
        al_stop_sample(&idsonido);
        al_play_sample(sonido, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idsonido);
        disparos->push_back(new Disparos(laserDmg, detalles->x + 15, detalles->y + 40, 0));
    }

    randomizarMovimiento();

    frame++;
    if (detalles->y > 600 || vidas < 0)
        muerto = true;
}

/**
    Determina el patrón de movimiento del enemigo
**/
void Enemigos::randomizarMovimiento(){
    int randomNumber = rand() % 10000;
    if (randomNumber % randomAlternative1 == 0){
        alternar = true;
    }else if (randomNumber % randomAlternative2 == 0){
        alternar = false;
    }

    determinarRandomMovimiento();
}

/**
    Especifica el patrón de movimiento del personaje
**/
void Enemigos::determinarRandomMovimiento(){
    if(alternar & detalles->x > 0){
        detalles->x -= moveBy;
    }else if (!alternar & detalles->x < 450){
        detalles->x += moveBy;
    }
}

Enemigos::~Enemigos()
{
}
