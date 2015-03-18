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
#include <list>
using namespace std;

enum Estados{
    AVANZAR,
    IZQUIERDA,
    DERECHA,
    CENTRO
};

enum Animaciones{
    PARADO,
    CAMINANDO,
    DISPARANDO,
    REC_DANO,
    PROTEGIDO,
    MUERTO
};

class PersonajesAnimados
{
    public:
        bool muerto;
        bool quitarVidas;
        Box detalles();
        map<int, ALLEGRO_BITMAP*> mapa_sprites;
        PersonajesAnimados();
        virtual void act() = 0;
        void draw(ALLEGRO_EVENT* ev);
        void init(list<PersonajesAnimados *> *personajes);
        bool Colision(Box* pCaja);
        virtual ~PersonajesAnimados();
    protected:
    private:
};

#endif // PERSONAJESANIMADOS_H
