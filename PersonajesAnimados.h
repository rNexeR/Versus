#ifndef PERSONAJESANIMADOS_H
#define PERSONAJESANIMADOS_H

#include "Entidad.h"
#include "ObjetosAnimados.h"
#include "Disparos.h"


enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
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

class PersonajesAnimados : public Entidad
{
    public:
        //estados del personaje
        int vidas;
        bool muerto;
        char orientacion;
        int mapa_actual;
        unsigned int animacion_actual = 0;

        bool key[6] = { false, false, false, false};

        int frame;
        float velocidad_y;
        float aceleracion_y;
        float gravedad;
        bool jump, down;

        map<int, vector<ALLEGRO_BITMAP*> > mapa_sprites;
        ALLEGRO_BITMAP *damage;
        list<PersonajesAnimados*>*personajes;
        list<ObjetosAnimados*>*obstaculos;
        list<ObjetosAnimados*>*disparos;

        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;

        PersonajesAnimados();
        string toString(int number);
        virtual int getTime() = 0;
        virtual void draw();
        void init(list<PersonajesAnimados *> *personajes);
        void init(list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos);
        bool colision(Box* pCaja);
        void defenseCheck();
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
