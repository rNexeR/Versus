#include <stdio.h>
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

//LIBRERIAS DE PROYECTO
#include "Box.h"
#include "PersonajesAnimados.h"
#include "ObjetosAnimados.h"
#include "Obstaculo.h"
#include "PerPrincipal.h"
#include "EnemigoNegro.h"

const float FPS = 60;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

//EVENTOS Y TIMERS
ALLEGRO_EVENT ev;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_TIMER *timer = NULL;

//Elementos Generales
Box *blogo = NULL;
ALLEGRO_BITMAP  *logo   = NULL;
ALLEGRO_SAMPLE *music = NULL;
ALLEGRO_SAMPLE_ID imusic;
ALLEGRO_SAMPLE *effect = NULL;
ALLEGRO_SAMPLE_ID ieffect;
ALLEGRO_FONT *normalFont = NULL, *cartoonFont = NULL;

//Constantes
int splashTime = 1;
int width = 500, height = 650;

//Listas
list<PersonajesAnimados*> *personajes = new list<PersonajesAnimados*>();
list<ObjetosAnimados*> *obstaculos =  new list<ObjetosAnimados*>();;

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
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

int initAllegro()
{
    if(!al_init())
    {
        cout<<"failed to initialize allegro!\n"<<endl;
        return -1;
    }

    if(!al_init_image_addon())
    {
        cout<<"Error: Failed to initialize al_init_image_addon!"<<endl;
        return -1;
    }

    display = al_create_display(width, height);
    if(!display)
    {
        cout<<"failed to create display!\n"<<endl;
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        cout<<"failed to create event_queue!\n"<<endl;
        al_destroy_display(display);
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        cout<<"failed to create timer!"<<endl;
    }

    if(!al_install_keyboard())
    {
        cout<<"failed to initialize the keyboard!"<<endl;
    }

    if(!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(2))
    {
        cout<<"failed to initialize Audio!"<<endl;
    }

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    normalFont = al_load_ttf_font("GameFiles/fonts/font.ttf",50,0 );
    cartoonFont = al_load_ttf_font("GameFiles/fonts/cartoon.ttf",50,0 );

    if (!normalFont || !cartoonFont)
    {
        cout<<"Failed to initialize the font"<<endl;
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_init_timeout(&timeout, 0.06);
    return 0;
}

bool changeSizenormalFont(int x)
{
    normalFont = al_load_ttf_font("GameFiles/fonts/font.ttf",x,0 );

    if (!normalFont)
    {
        return false;
    }
    return true;
}

bool changeSizeCartoonFont(int x)
{
    cartoonFont = al_load_ttf_font("GameFiles/fonts/cartoon.ttf",x,0 );

    if (!cartoonFont)
    {
        return false;
    }
    return true;
}

int initLogo()
{
    logo = al_load_bitmap("Versus.png");

    if(!logo)
    {
        cout<<"Error: Failed to load image!"<<endl;
        al_destroy_display(display);
        return -1;
    }
    blogo = new Box(0,0,al_get_bitmap_width(logo), al_get_bitmap_height(logo));
    blogo->x = (width-blogo->width)/2;
    blogo->y = (height-blogo->height)/2;
    return 0;
}

//OJO al mantener presionada, si funciona pero lo hace como 3 veces por frame
void teclaPresionada(int keycode, bool *variable)
{
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev.keyboard.keycode==keycode)
            *variable = true;
    }
    if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(ev.keyboard.keycode==keycode)
            *variable = false;
    }
}

bool teclaDownEvent(int keycode)
{
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev.keyboard.keycode==keycode)
            return true;
    }
    return false;
}

void showSplash()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(logo,blogo->x,blogo->y,0);
    al_flip_display();
    al_rest(splashTime);
}


string ingresarNombre()
{
    string name = "";
    changeSizenormalFont(20);
    while(1)
    {
        al_clear_to_color(al_map_rgb(0,0,0));
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(get_event && ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (teclaDownEvent(ALLEGRO_KEY_ESCAPE) || teclaDownEvent(ALLEGRO_KEY_ENTER))
                break;
            for(int x = 1; x <= 27; x++)
                if (teclaDownEvent(x))
                {
                    char e = x+64;
                    name+=e;
                }

            if (teclaDownEvent(ALLEGRO_KEY_BACKSPACE) && name.size()>0)
            {
                string temp = name;
                name = "";
                for(int x = 0; x<temp.size()-1; x++)
                    name+=temp[x];
            }
        }
        //cout<<hola<<endl;
        al_draw_text(normalFont, al_map_rgb(0,0,255), width/2, (height/2)-35,ALLEGRO_ALIGN_CENTER, "Ingrese su nombre:");
        al_draw_text(normalFont, al_map_rgb(255,255,255), width/2, height/2,ALLEGRO_ALIGN_CENTRE, name.c_str());
        al_flip_display();
    }
    return name;
}

void cleanPersonajes()
{
    for(list<PersonajesAnimados*>::iterator i = personajes->begin(); i!=personajes->end(); i++)
    {
        delete (*i);
    }
}

void cleanObstaculos(){
    for(list<ObjetosAnimados*>::iterator i = obstaculos->begin(); i != obstaculos->end(); i++)
        delete (*i);
}

void initGame()
{
    cleanPersonajes();
    cleanObstaculos();//limpiar obstacles
    personajes->clear();
    obstaculos->clear();
    personajes->push_back(new PerPrincipal(event_queue, personajes, obstaculos));
    personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, 1));
    obstaculos->push_back(new Obstaculo(0));
    obstaculos->push_back(new Obstaculo(100));
}

void loopJuego()
{
    string nombre;
    int seg = 0;
    nombre = ingresarNombre();
    cout<<nombre<<endl;
    initGame();

    changeSizenormalFont(15);
    changeSizeCartoonFont(20);
    while(1)
    {
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(get_event && (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || teclaDownEvent(ALLEGRO_KEY_ESCAPE)))
        {
            break;
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_text(normalFont, al_map_rgb(255,255,255), 0, 0,ALLEGRO_ALIGN_LEFT, nombre.c_str());
        al_draw_text(cartoonFont, al_map_rgb(255,255,255), width, 5,ALLEGRO_ALIGN_RIGHT, toString(seg).c_str());
        for(list<PersonajesAnimados*>::iterator i = personajes->begin(); i!=personajes->end(); i++)
        {
            if ((*i)->tipoObjeto == "Principal")
                seg = (*i)->getTime();
            (*i)->draw();
            (*i)->act(&ev);
        }


        //OBJETOS ANIMADOS
        for(list<ObjetosAnimados*>::iterator i = obstaculos->begin(); i!=obstaculos->end(); i++)
        {
//            if ((*i)->clase == "Principal")
//                seg = (*i)->getTime();
            (*i)->draw();
            (*i)->act(NULL);
        }

        al_flip_display();
    }
}

void mainMenu()
{
    ALLEGRO_BITMAP *select = NULL, *options = NULL;
    music = al_load_sample("GameFiles/music/So, let see, what you can_0.wav");
    effect = al_load_sample("GameFiles/music/sfx_laser1.wav");
    al_play_sample(music, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&imusic);
    Box *bselect = NULL, *boptions = NULL;
    int uPosy, uPosyOriginal;

    select = al_load_bitmap("GameFiles/assets/menu/uselect.png");
    bselect = new Box(0,0,al_get_bitmap_width(select), al_get_bitmap_height(select));
    bselect->x = (width-bselect->width)/2;
    bselect->y = (height-bselect->height)/2;

    int espaciado = 35;
    options = al_load_bitmap("GameFiles/assets/menu/opciones.png");
    boptions = new Box(0,0,al_get_bitmap_width(options), al_get_bitmap_height(options));
    boptions->x = (width-boptions->width)/2;
    boptions->y = (height-boptions->height)/2;

    uPosyOriginal = (height/2)+60;
    uPosy = uPosyOriginal;

    if (!select || !options)
        return;

    while(true)
    {
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        if(get_event && teclaDownEvent(ALLEGRO_KEY_DOWN))
        {
            al_stop_sample(&ieffect);
            al_play_sample(effect, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&ieffect);
            uPosy += espaciado;
        }
        else if(get_event && teclaDownEvent(ALLEGRO_KEY_UP))
        {
            al_stop_sample(&ieffect);
            al_play_sample(effect, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&ieffect);
            uPosy -= espaciado;
        }
        else if(get_event && teclaDownEvent(ALLEGRO_KEY_ENTER))
        {
            if (uPosy == uPosyOriginal)
            {
                //llamar el loop del juego
                al_stop_samples();
                loopJuego();
                al_play_sample(music, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&imusic);
            }
            else if (uPosy == uPosyOriginal+espaciado)
            {
                //llamar el loop de instrucciones
                al_stop_samples();
                showSplash();
                al_play_sample(music, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&imusic);
            }
            else if(uPosy == uPosyOriginal+(espaciado*2))
            {
                //llamar el loop de Scores
                al_stop_samples();
                showSplash();
                al_play_sample(music, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&imusic);
            }else{
                break;
            }
        }
        if (uPosy>uPosyOriginal+(espaciado*3))
            uPosy = uPosyOriginal;
        if (uPosy<uPosyOriginal)
            uPosy = uPosyOriginal+(espaciado*3);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(logo,blogo->x,blogo->y - 100,0);
        al_draw_bitmap(options,boptions->x,boptions->y + 100,0);
        al_draw_bitmap(select, bselect->x, uPosy, 0);

        al_flip_display();
    }
    al_destroy_bitmap(options);
    al_destroy_bitmap(select);
    //delete options;
//    delete select;
//    delete boptions;
//    delete bselect;
}

int main(int argc, char **argv)
{
    if (initAllegro()<0 || initLogo()<0)
        return -1;
    showSplash();
    mainMenu();
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_sample(music);
    al_destroy_sample(effect);
    al_destroy_bitmap(logo);

    cleanPersonajes();
//    delete personajes;
//    delete obstaculos;
//    delete blogo;
//    delete logo;
//    delete music;
//    delete effect;

    return 0;
}
