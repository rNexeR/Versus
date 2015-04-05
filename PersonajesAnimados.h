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

#ifndef PERSONAJESANIMADOS_H
#define PERSONAJESANIMADOS_H

#include "Entidad.h"
#include "ObjetosAnimados.h"
#include "Disparos.h"


enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

enum Estados{
    IZQUIERDA,
    DERECHA,
    CENTRO
};

enum Animaciones{
    PARADO_DERECHA,
    PARADO_IZQUIERDA,
    CAMINANDO_DERECHA,
    CAMINANDO_IZQUIERDA,
    DISPARANDO_DERECHA,
    DISPARANDO_IZQUIERDA,
    SALTANDO_DERECHA,
    SALTANDO_IZQUIERDA,
    CAYENDO_DERECHA,
    CAYENDO_IZQUIERDA,
    MUERTO_DERECHA,
    MUERTO_IZQUIERDA
};

class PersonajesAnimados : public Entidad
{
    public:
        //estados del personaje
        int vidas;
        bool muerto;
        char orientacion;
        int mapa_actual;
        unsigned int animacion_actual = 0;

        bool key[6] = { false, false, false, false};

        int frame;
        float velocidad_y;
        float aceleracion_y;
        float gravedad;
        bool jump, down;

        map<int, vector<ALLEGRO_BITMAP*> > mapa_sprites;
        ALLEGRO_BITMAP *health;
        ALLEGRO_BITMAP *damage;
        ALLEGRO_SAMPLE *sonido;
        ALLEGRO_SAMPLE_ID idsonido;
        ALLEGRO_SAMPLE *stop;
        ALLEGRO_SAMPLE_ID idstop;
        list<PersonajesAnimados*>*personajes;
        list<ObjetosAnimados*>*obstaculos;
        list<ObjetosAnimados*>*disparos;

        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
        ALLEGRO_DISPLAY *display;

        PersonajesAnimados();
        string toString(int number);
        virtual int getTime() = 0;
        virtual void draw();
        void init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, ALLEGRO_DISPLAY *display);
        void detectColision();
        PersonajesAnimados* getPrincipal();
        void setAnimacion(int nombre);
        void teclaPresionada(int keycode, bool *variable);
        bool teclaDownEvent(int keycode);
        int enumToInt(string animacion);
        void limpiarEnemigos();

        virtual ~PersonajesAnimados();
    protected:
    private:
};

#endif // PERSONAJESANIMADOS_H
