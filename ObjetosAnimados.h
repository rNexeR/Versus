#ifndef OBJETOSANIMADOS_H
#define OBJETOSANIMADOS_H
#include "Box.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <vector>
using namespace std;

class ObjetosAnimados
{
    public:
        bool destroy;
        Box detalles();
        vector<ALLEGRO_BITMAP*>* sprites;
        ObjetosAnimados();
        virtual void act() = 0;
        void draw(ALLEGRO_EVENT* ev);
        virtual ~ObjetosAnimados();
    protected:
    private:
};

#endif // OBJETOSANIMADOS_H
