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

#ifndef DISPAROS_H
#define DISPAROS_H

#include "ObjetosAnimados.h"


class Disparos : public ObjetosAnimados
{
    public:
        int dmg;//cantidad de daño que ejerce el disparo

        virtual void act(ALLEGRO_EVENT *ev);
        virtual void draw();
        Disparos(int dmg, int posX, int posY, int dir);
        virtual ~Disparos();
    protected:
    private:
};

#endif // DISPAROS_H
