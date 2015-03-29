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
using namespace std;

enum Estados{
    IZQUIERDA,
    DERECHA,
    CENTRO
};

enum Animaciones{
    PARADO,
    CAMINANDO_DERECHA,
    CAMINANDO_IZQUIERDA,
    DISPARANDO_DERECHA,
    DISPARANDO_IZQUIERDA,
    MUERTO
};

class PersonajesAnimados
{
    public:
        bool muerto;
        bool colisionado;
        bool quitarVidas;
        bool protegido;
        Box *detalles;
        int mapa_actual;
        int frame;
        int animacion_actual;
        string clase;
        map<int, vector<ALLEGRO_BITMAP*>*> mapa_sprites;
        list<PersonajesAnimados*>*personajes;
        list<ObjetosAnimados*>*disparos_principal;
        list<ObjetosAnimados*>*disparos_enemigos;
        list<ObjetosAnimados*>*obstaculos;

        PersonajesAnimados();
        virtual void act() = 0;
        void draw(ALLEGRO_EVENT* ev);
        void init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*disparos_principal, list<ObjetosAnimados*>*disparos_enemigos, list<ObjetosAnimados*>*obstaculos);
        void defenseCheck();
        bool colision(Box* pCaja);
        void setAnimacion(int nombre);
        int enumToInt();
        virtual ~PersonajesAnimados();
    protected:
    private:
};

#endif // PERSONAJESANIMADOS_H
