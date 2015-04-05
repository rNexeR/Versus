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

#include "EnemigoRojo.h"

EnemigoRojo::EnemigoRojo(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, ALLEGRO_DISPLAY *display, int level)
{
    velocity = 0.05;
    firingRate = 20;
    moveBy = 5;
    laserDmg = 5;
    randomAlternative1 =  150;
    randomAlternative2 = 125;

    vidas = 50;

    alternar = false;
    //carga de imagenes
    string path = "GameFiles/assets/personajes/enemies/red/enemyRed" + toString(level) + ".png";
    mapa_sprites[0] = vector<ALLEGRO_BITMAP*>();
    mapa_sprites[0].push_back(al_load_bitmap(path.c_str()));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    this->event_queue = event_queue;
    init(personajes, obstaculos, display);
    setAnimacion(0);
    disparos = new list<ObjetosAnimados*>;//Inicializar disparos
}

void EnemigoRojo::determinarRandomMovimiento()
{
    Box tem(detalles->x-5, detalles->y, detalles->width+5, detalles->height+50);
    PersonajesAnimados *temp = getPrincipal();
    cout<<"\t"<<temp->disparos->size()<<endl;
    bool entro = false;
    for (list<ObjetosAnimados*>::iterator i = temp->disparos->begin(); i != temp->disparos->end(); i++)
    {
        //al_rest(1);
        if (colision((*i)->detalles, &tem))
        {
            //al_rest(1);
            entro = true;
            int cy = detalles->x + (detalles->width/2);
            if (cy < 250)
                detalles->x += moveBy;
            else
                detalles->x -= moveBy;
        }
    }
    temp = NULL;
    delete temp;
    if (!entro)
    {
        if(alternar)
        {
            detalles->x -= moveBy;
            if(detalles->x < 0)
                detalles->x -= (moveBy * -1);
        }
        else if (!alternar)
        {
            detalles->x += moveBy;
            if(detalles->x > 450)
                detalles->x += (moveBy * -1);
        }
    }
}


EnemigoRojo::~EnemigoRojo()
{
    //dtor
}
