#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "ObjetosAnimados.h"


class Obstaculo : public ObjetosAnimados
{
    public:
        Obstaculo();
        bool alternar = false; //izquierda o derecha, si es obstaculo
        virtual void act();
        virtual ~Obstaculo();
    protected:
    private:
};

#endif // OBSTACULO_H
