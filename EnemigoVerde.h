#ifndef ENEMIGOVERDE_H
#define ENEMIGOVERDE_H

#include "Enemigos.h"


class EnemigoVerde : public Enemigos
{
    public:
        EnemigoVerde(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes,
            list<ObjetosAnimados*>*obstaculos, int level);
        virtual ~EnemigoVerde();
    protected:
    private:
};

#endif // ENEMIGOVERDE_H
