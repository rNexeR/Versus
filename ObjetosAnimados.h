#ifndef OBJETOSANIMADOS_H
#define OBJETOSANIMADOS_H

#include "Entidad.h"

class ObjetosAnimados : public Entidad{
    public:
//        vector<ALLEGRO_BITMAP*>* sprites;//
        ALLEGRO_BITMAP* sprite;
        virtual void draw();//dibujo
        ObjetosAnimados();//constructor
        list<ObjetosAnimados*>*obstaculos;
        virtual ~ObjetosAnimados();
    protected:
    private:
};

#endif // OBJETOSANIMADOS_H
