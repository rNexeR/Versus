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

enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_SHOOT
};

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
    DISPARANDO_IZQUIERDA,
    SALTANDO_DERECHA,
    SALTANDO_IZQUIERDA,
    CAYENDO_DERECHA,
    CAYENDO_IZQUIERDA,
    MUERTO_DERECHA,
    MUERTO_IZQUIERDA
};

class PersonajesAnimados
{
    public:
        //estados del personaje
        int vidas;
        bool muerto;
        bool colisionado;
        char orientacion;
        int mapa_actual;
        int animacion_actual;

        Box *detalles = new Box(0,0,0,0);
        bool key[6] = { false, false, false, false,false,false};

        int frame;
        int var = 6;
        string clase;
        float velocidad_y;
        float aceleracion_y;
        float gravedad;
        bool jump, down;

        map<int, vector<ALLEGRO_BITMAP*>*> mapa_sprites;
        ALLEGRO_BITMAP *damage;
        list<PersonajesAnimados*>*personajes;
        list<ObjetosAnimados*>*obstaculos;
        list<ObjetosAnimados*>*disparos;

        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;

        PersonajesAnimados();
        string toString(int number);
        virtual void act(ALLEGRO_EVENT* ev) = 0;
        virtual int getTime() = 0;
        void draw();
        void init(list<PersonajesAnimados *> *personajes);
        void init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos);
        void defenseCheck();
        bool colision(Box* pCaja);
        void setAnimacion(int nombre);
        void teclaPresionada(int keycode, bool *variable);
        bool teclaDownEvent(int keycode);
        int enumToInt(string animacion);
        void limpiarEnemigos();

        virtual ~PersonajesAnimados();
    protected:
    private:
};

#endif // PERSONAJESANIMADOS_H
