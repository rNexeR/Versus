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

#ifndef PERPRINCIPAL_H
#define PERPRINCIPAL_H
#include "PersonajesAnimados.h"
#include "ObjetosAnimados.h"


class PerPrincipal : public PersonajesAnimados
{
    public:
        int piso;
        PerPrincipal(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, ALLEGRO_DISPLAY *display);
        virtual void act(ALLEGRO_EVENT* ev);
        virtual int getTime();
        void validarTeclas(ALLEGRO_EVENT* ev);
        int isOnSolidGround();
        virtual ~PerPrincipal();
    protected:
    private:
};

#endif // PERPRINCIPAL_H
