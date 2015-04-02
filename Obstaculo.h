#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "ObjetosAnimados.h"

class Obstaculo : public ObjetosAnimados
{
    public:
        Obstaculo(int variacion, list<ObjetosAnimados*>*obstaculos);
        bool alternar = true; //izquierda o derecha, si es obstaculo
        virtual void act(ALLEGRO_EVENT* ev);
        virtual ~Obstaculo();
    protected:
    private:
};

#endif // OBSTACULO_H