#ifndef ENTIDAD_H
#define ENTIDAD_H
//Librerías y archivos necesarios
#include "Box.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

class Entidad
{
    public:
        //Atributos
        bool colisionado;
        Box *detalles = new Box(0,0,0,0); //donde estará y de donde se comprueban las colisiones
        int velocity = 1; //cuanto se mueve
        string tipoObjeto = ""; //muestra que objeto es: obstacle, disparo, enemy, etc.
        virtual void act(ALLEGRO_EVENT* ev) = 0;
        virtual void draw() = 0;//dibujo de la figura
        bool colision(Box*detalles, Box* pCaja);//detectar colisiones con otros objetos
        Entidad();
        virtual ~Entidad();
    protected:
    private:
};

#endif // ENTIDAD_H
