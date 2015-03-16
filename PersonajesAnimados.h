#ifndef PERSONAJESANIMADOS_H
#define PERSONAJESANIMADOS_H
#include "Box.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <map>
using namespace std;

enum Estados{
    IZQUIERDA,
    DERECHA,
    CENTRO
};

enum Animaciones{
    CAMINANDO,
    DISPARANDO,
    REC_DANO,
    PROTEGIDO,
    MUERTO
};

class PersonajesAnimados
{
    public:
        Box detalles();
        map<int, ALLEGRO_BITMAP*> mapa_sprites;
        PersonajesAnimados();
        virtual ~PersonajesAnimados();
    protected:
    private:
};

#endif // PERSONAJESANIMADOS_H
