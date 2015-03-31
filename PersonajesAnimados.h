#ifndef PERSONAJESANIMADOS_H
#define PERSONAJESANIMADOS_H
#include "Box.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "ObjetosAnimados.h"
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <fstream>
using namespace std;

enum Estados{
    IZQUIERDA,
    DERECHA,
    CENTRO
};

enum Animaciones{
    PARADO_DERECHA,
    PARADO_IZQUIERDA,
    CAMINANDO_DERECHA,
    CAMINANDO_IZQUIERDA,
    DISPARANDO_DERECHA,
    DISPARANDO_IZQUIERDA
};

class PersonajesAnimados
{
    public:
        int vidas;
        bool muerto;
        bool colisionado;
//        bool quitarVidas;
//        bool protegido;
        Box *detalles = new Box(0,0,0,0);
        int mapa_actual;
        int frame;
        int animacion_actual;
        string clase;
        map<int, vector<ALLEGRO_BITMAP*>*> mapa_sprites;
        list<PersonajesAnimados*>*personajes;
        list<ObjetosAnimados*>*obstaculos;
        ALLEGRO_TIMER *timer = NULL;

        PersonajesAnimados();
        virtual void act(ALLEGRO_EVENT* ev) = 0;
        void draw();
        void init(list<PersonajesAnimados *> *personajes);
        void init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos);
        void defenseCheck();
        bool colision(Box* pCaja);
        void setAnimacion(int nombre);
        int enumToInt(string animacion);
        virtual ~PersonajesAnimados();
    protected:
    private:
};

#endif // PERSONAJESANIMADOS_H
