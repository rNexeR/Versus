#ifndef ENEMIGOAZUL_H
#define ENEMIGOAZUL_H

#include "Enemigos.h"


class EnemigoAzul : public Enemigos
{
    public:
        EnemigoAzul(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, ALLEGRO_DISPLAY *display, int level);
        //virtual void act(ALLEGRO_EVENT* ev);
        virtual void determinarRandomMovimiento();
        virtual ~EnemigoAzul();
    protected:
    private:
};

#endif // ENEMIGOAZUL_H
