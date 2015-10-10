#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <iostream>
using namespace std;

//LIBRERIAS DE ALLEGRO
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <map>

const float width = 500, height = 650, FPS = 60;
const int CANTIDAD_SCORES = 6, SIZE_FORMATO = 14, splashTime = 1;

//OJO al mantener presionada, si funciona pero lo hace como 3 veces por frame
void teclaPresionada(ALLEGRO_EVENT *ev, int keycode, bool *variable)
{
    if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev->keyboard.keycode==keycode)
            *variable = true;
    }
    if(ev->type == ALLEGRO_EVENT_KEY_UP)
    {
        if(ev->keyboard.keycode==keycode)
            *variable = false;
    }
}

/**
    Detecta si una tecla ha sido presionada
**/
bool teclaDownEvent(ALLEGRO_EVENT *ev,int keycode)
{
    if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev->keyboard.keycode==keycode)
            return true;
    }
    return false;
}

/**
    TO-DO: especificaciones por NXR
**/
string toString(int number)
{
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0; i<(int)temp.length(); i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

/**
    Cambia el size del font
    **/
    bool changeSizeFont(ALLEGRO_FONT* font, int x)
    {
        font->height = x;
    }

/**
    función para ingresar el nombre al comienzo del juego
**/
string ingresarNombre(ALLEGRO_EVENT* ev, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_TIMEOUT* timeout, ALLEGRO_BITMAP* fondo)
{
    ALLEGRO_FONT* cartoonFont = al_load_ttf_font("GameFiles/fonts/kenpixel_blocks.ttf", 20, 0);
    ALLEGRO_FONT* normalFont = al_load_ttf_font("GameFiles/fonts/kenvector_future_thin.ttf",20,0 );

    if (!cartoonFont || !normalFont)
        return "";

    string name = "";
    while(1)
    {
        al_clear_to_color(al_map_rgb(0,0,0));
        bool get_event = al_wait_for_event_until(event_queue, ev, timeout);
        if(get_event && ev->type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (teclaDownEvent(ev, ALLEGRO_KEY_ESCAPE) || teclaDownEvent(ev, ALLEGRO_KEY_ENTER))
                break;
            for(int x = 1; x <= 27; x++)//for para obtener los valores de todas las letras
                if (teclaDownEvent(ev, x))//comparamos que tecla está siendo presionada
                {
                    char e = x+64; //de ser así, sumarle al valor ASCII equivalente
                    name+=e;//concatenarla al nombre
                }

            if (teclaDownEvent(ev, ALLEGRO_KEY_BACKSPACE) && name.size()>0)//comprar si vamos a borrar una letra
            {
                string temp = name;
                name = "";
                for(int x = 0; x<temp.size()-1; x++)
                    name+=temp[x];
            }
        }
        al_draw_bitmap(fondo,0,0,0);
        al_draw_text(normalFont, al_map_rgb(102,204,0), width/2, (height/2)-35,ALLEGRO_ALIGN_CENTER, "INGRESE SU NOMBRE:");
        al_draw_text(normalFont, al_map_rgb(255,255,255), width/2, height/2,ALLEGRO_ALIGN_CENTRE, name.c_str());//dibuja el nombre
        al_flip_display();//necesario para cambiar a la siguiente parte del buffer (que dibujará)
    }
    return name;
}

#endif // TOOLS_H_INCLUDED
