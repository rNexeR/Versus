#ifndef ENEMIGOROJO_H
#define ENEMIGOROJO_H

#include "Enemigos.h"


class EnemigoRojo : public Enemigos
{
    public:
        EnemigoRojo(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes,
            list<ObjetosAnimados*>*obstaculos,ALLEGRO_DISPLAY *display, int level);
        virtual void determinarRandomMovimiento();
        virtual ~EnemigoRojo();
    protected:
    private:
};

#endif // ENEMIGOROJO_H
