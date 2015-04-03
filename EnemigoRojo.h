#ifndef ENEMIGOROJO_H
#define ENEMIGOROJO_H

#include "Enemigos.h"


class EnemigoRojo : public Enemigos
{
    public:
        EnemigoRojo(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, int level);
        void act(ALLEGRO_EVENT* ev);
        virtual void randomizarMovimiento();
        virtual ~EnemigoRojo();
    protected:
    private:
};

#endif // ENEMIGOROJO_H
