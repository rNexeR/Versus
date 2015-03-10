#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
using namespace std;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP  *splash   = NULL;

int initAllegro(){
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

    display = al_create_display(1024, 480);
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

    al_register_event_source(event_queue, al_get_display_event_source(display));
    return 0;
}

int initSplash(){
    splash = al_load_bitmap("Versus.png");

    if(!splash)
    {
        cout<<"Error: Failed to load image!"<<endl;
        al_destroy_display(display);
        return -1;
    }
    return 0;
}

void mainMenu(){
    while(true){

    }
}

bool teclaPresionada(){
    //Codigo
    return false;
}

void showSplash(){
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(splash,300,150,0);
    al_flip_display();
    al_rest(5);
}

int main(int argc, char **argv)
{
    if (initAllegro()<0 || initSplash()<0)
        return -1;
    showSplash();
    while(true)
    {
        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);

        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        al_clear_to_color(al_map_rgb(0,0,0));

        al_flip_display();
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
