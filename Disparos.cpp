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

#include "Disparos.h"

Disparos::Disparos(int dmg, int posX, int posY, int dir)
{
    this->dmg = dmg;
    string path = "GameFiles/assets/lasers/laserGreen.png";
    if (dir>0){
        velocity = -10;
    }else{
        velocity = 10;
        path = "GameFiles/assets/lasers/laserRed.png";
    }
    //Inicializaciones de audio

    if(!al_init_image_addon())//chequear si se pudo inicializar para las imágenes
    {
        cout<<"failed to initialize image addon!"<<endl;
    }

    //Inicialización de la posición de la cajita
    detalles->x = posX;
    detalles->y = posY;
    tipoObjeto = "Disparo";//declarar el tipo de ObjetoAnimado
    sprite = al_load_bitmap(path.c_str());//cargar el sprite según el path dado
    colisionado = false;
    if(!sprite)
        return;

    detalles->width = al_get_bitmap_width(sprite);
    detalles->height = al_get_bitmap_height(sprite);
}

Disparos::~Disparos()
{
    delete detalles;
}

void Disparos::act(ALLEGRO_EVENT *ev){
    detalles->y += velocity;
    if (detalles->y > 650 || detalles->y <0 || detalles-> x < 0 || detalles->x > 500)
        colisionado = true;
}

void Disparos::draw(){
    if (sprite){//si el sprite está cargado, dibujar
        al_draw_bitmap(sprite, detalles->x, detalles->y, 0);
    }
}





