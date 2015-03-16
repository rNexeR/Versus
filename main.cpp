#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Box.h"
using namespace std;

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

//Constantes
int splashTime = 1;
int width = 500, height = 650;

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

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_init_timeout(&timeout, 0.06);
    return 0;
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

void mainMenu()
{
    ALLEGRO_BITMAP *select = NULL, *options = NULL;
    music = al_load_sample("music/So, let see, what you can_0.wav");
    effect = al_load_sample("music/sfx_laser1.wav");
    al_play_sample(music, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&imusic);
    Box *bselect = NULL, *boptions = NULL;
    int uPosy, uPosyOriginal;

    select = al_load_bitmap("GameFiles/assets/menu/uselect.png");
    bselect = new Box(0,0,al_get_bitmap_width(select), al_get_bitmap_height(select));
    bselect->x = (width-bselect->width)/2;
    bselect->y = (height-bselect->height)/2;

    options = al_load_bitmap("GameFiles/assets/menu/opciones.png");
    boptions = new Box(0,0,al_get_bitmap_width(options), al_get_bitmap_height(options));
    boptions->x = (width-boptions->width)/2;
    boptions->y = (height-boptions->height)/2;

    uPosyOriginal = (height/2)+50;
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
        if(teclaDownEvent(ALLEGRO_KEY_DOWN))
        {
            al_stop_sample(&ieffect);
            al_play_sample(effect, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&ieffect);
            cout<<"ABAJO"<<endl;
            uPosy += 50;
        }
        else if(teclaDownEvent(ALLEGRO_KEY_UP))
        {
            al_stop_sample(&ieffect);
            al_play_sample(effect, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&ieffect);
            cout<<"ARRIBA"<<endl;
            uPosy -= 50;
        }else if(teclaDownEvent(ALLEGRO_KEY_ENTER)){
            if (uPosy == uPosyOriginal)
                //llamar el loop del juego
                showSplash();
            else if (uPosy == uPosyOriginal+50)
                //llamar el loop de instrucciones
                showSplash();
            else if(uPosy == uPosyOriginal+100)
                //llamar el loop de Scores
                showSplash();
            else
                //salir del juego
                break;
        }
        if (uPosy>uPosyOriginal+150)
            uPosy = uPosyOriginal;
        if (uPosy<uPosyOriginal)
            uPosy = uPosyOriginal+150;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(logo,blogo->x,blogo->y - 100,0);
        al_draw_bitmap(options,boptions->x,boptions->y + 100,0);
        al_draw_bitmap(select, bselect->x, uPosy, 0);

        al_flip_display();
    }
}

int main(int argc, char **argv)
{
    if (initAllegro()<0 || initLogo()<0)
        return -1;
    showSplash();
    mainMenu();
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
