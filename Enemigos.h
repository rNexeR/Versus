#ifndef ENEMIGOS_H
#define ENEMIGOS_H
#include "PersonajesAnimados.h"


class Enemigos : public PersonajesAnimados
{
    public:
        Enemigos();
        bool alternar = false;
        virtual void act(ALLEGRO_EVENT* ev) = 0;
        virtual int getTime();
        virtual ~Enemigos();
    protected:
    private:
};

#endif // ENEMIGOS_H
