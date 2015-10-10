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

#ifndef ENEMIGOS_H
#define ENEMIGOS_H
#include "PersonajesAnimados.h"


class Enemigos : public PersonajesAnimados
{
    public:
        int firingRate; //paso al que disparará
        int variablesRandomEstado; //sugerible que sea >= 100,000
        int moveBy; //cuando se desplazará al azar
        int randomAlternative1, randomAlternative2; //valores para determinar la alternación de movimientos
        int laserDmg; //determinar el valor de daño del laser
        Enemigos();
        bool alternar = false; //determinará si se moverá al contrario o sentido que iba
        virtual void act();
        virtual int getTime();
        void randomizarMovimiento();//función para moverse al azar
        virtual void determinarRandomMovimiento();
        virtual ~Enemigos();
    protected:
    private:
};

#endif // ENEMIGOS_H
