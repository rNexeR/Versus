#ifndef PERPRINCIPAL_H
#define PERPRINCIPAL_H
#include "PersonajesAnimados.h"
#include "ObjetosAnimados.h"


class PerPrincipal : public PersonajesAnimados
{
    public:
        int piso;
        PerPrincipal(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos);
        virtual void act(ALLEGRO_EVENT* ev);
        virtual int getTime();
        void validarTeclas(ALLEGRO_EVENT* ev);
        int isOnSolidGround();
        virtual ~PerPrincipal();
    protected:
    private:
};

#endif // PERPRINCIPAL_H
