#ifndef ENEMIGONEGRO_H
#define ENEMIGONEGRO_H
#include "Enemigos.h"


class EnemigoNegro : public Enemigos
{
    public:
        EnemigoNegro(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos,ALLEGRO_DISPLAY *display, int level);
        //virtual void act(ALLEGRO_EVENT* ev);
        virtual ~EnemigoNegro();
    protected:
    private:
};

#endif // ENEMIGONEGRO_H
