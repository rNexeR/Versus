/**
	Versus is a PC game programmed in C++ using the Allegro 5.0.11 library.
	Copyright (C) 2015  Nexer Rodríguez and Ricardo A. Interiano (Raim)

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

**/

#include "Obstaculo.h"

Obstaculo::Obstaculo(int variacion, list<ObjetosAnimados*>*obstaculos)
{
    if(!al_init_image_addon())//chequear si se pudo inicializar para las imágenes
    {
        cout<<"failed to initialize image addon!"<<endl;
    }
    //Inicialización de la posición de la cajita
    detalles->x = 200 + variacion;
    detalles->y = 550;
    detalles->width = 50;
    detalles->height = 25;
    tipoObjeto = "Obstaculo";//declarar el tipo de ObjetoAnimado
    string path = "GameFiles/assets/fondos/Lift.png";
    sprite = al_load_bitmap(path.c_str());//cargar el sprite según el path dado.
    //Validar carga del sprite
    if(!sprite){
        cout<<"ERROR AL CARGAR SPRITES!";
        return;
    }

    this->obstaculos = obstaculos;
}

/**
    El act del obstaculo; por mientras está rebotando de izquierda a derecha dependiendo de su posición
**/
void Obstaculo::act(ALLEGRO_EVENT* ev){
    if (detalles->x < 0){//si choca en la izquierda, alternar a derecha
        velocity *= -1;
    }
    else if (detalles->x > 450){//si choca en la derecha, alterna a izquierda
        velocity *= -1;
    }

    for(list<ObjetosAnimados*>::iterator i = obstaculos->begin(); i != obstaculos->end(); i++){
        if((*i)->tipoObjeto == "Obstaculo" && (*i) != this){
            if( colision(detalles, (*i)->detalles) ){
                velocity *= -1;
            }
        }
    }
    detalles->x+=velocity;
}

Obstaculo::~Obstaculo()
{
}
