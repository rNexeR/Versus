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
