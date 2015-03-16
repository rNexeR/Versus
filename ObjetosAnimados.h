#ifndef OBJETOSANIMADOS_H
#define OBJETOSANIMADOS_H
#include "Box.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <map>
using namespace std;

class ObjetosAnimados
{
    public:
        Box detalles();
        map<int, ALLEGRO_BITMAP*> mapa_sprites;
        ObjetosAnimados();
        virtual ~ObjetosAnimados();
    protected:
    private:
};

#endif // OBJETOSANIMADOS_H
