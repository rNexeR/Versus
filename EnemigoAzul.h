#ifndef ENEMIGOAZUL_H
#define ENEMIGOAZUL_H

#include "Enemigos.h"


class EnemigoAzul : public Enemigos
{
    public:
        EnemigoAzul(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, int level);
        //virtual void act(ALLEGRO_EVENT* ev);
        virtual void randomizarMovimiento();
        virtual ~EnemigoAzul();
    protected:
    private:
};

#endif // ENEMIGOAZUL_H
