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

#ifndef ENTIDAD_H
#define ENTIDAD_H
//Librerías y archivos necesarios
#include "Box.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

class Entidad
{
    public:
        //Atributos
        bool colisionado;
        Box *detalles = new Box(0,0,0,0); //donde estará y de donde se comprueban las colisiones
        float velocity = 1; //cuanto se mueve
        string tipoObjeto = ""; //muestra que objeto es: obstacle, disparo, enemy, etc.
        virtual void act() = 0;
        virtual void draw() = 0;//dibujo de la figura
        bool colision(Box*detalles, Box* pCaja);//detectar colisiones con otros objetos
        Entidad();
        virtual ~Entidad();
    protected:
    private:
};

#endif // ENTIDAD_H
