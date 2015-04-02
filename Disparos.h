#ifndef DISPAROS_H
#define DISPAROS_H

#include "ObjetosAnimados.h"


class Disparos : public ObjetosAnimados
{
    public:
        int dmg;//cantidad de daño que ejerce el disparo
        ALLEGRO_SAMPLE *sonido; //sonido a utilizar

        virtual void act(ALLEGRO_EVENT *ev);
        virtual void draw();
        Disparos(int dmg, int posX, int posY);
        virtual ~Disparos();
    protected:
    private:
};

#endif // DISPAROS_H
