#ifndef ENEMIGOVERDE_H
#define ENEMIGOVERDE_H

#include "Enemigos.h"


class EnemigoVerde : public Enemigos
{
    public:
        EnemigoVerde(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, int level);
        void act(ALLEGRO_EVENT* ev);
        virtual void randomizarMovimiento();
        virtual ~EnemigoVerde();
    protected:
    private:
};

#endif // ENEMIGOVERDE_H
