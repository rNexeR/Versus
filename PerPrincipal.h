#ifndef PERPRINCIPAL_H
#define PERPRINCIPAL_H
#include "PersonajesAnimados.h"
#include "ObjetosAnimados.h"


class PerPrincipal : public PersonajesAnimados
{
    public:
        PerPrincipal(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*disparos_principal, list<ObjetosAnimados*>*disparos_enemigos, list<ObjetosAnimados*>*obstaculos);
        virtual void act(ALLEGRO_EVENT* ev);
        virtual ~PerPrincipal();
    protected:
    private:
};

#endif // PERPRINCIPAL_H
