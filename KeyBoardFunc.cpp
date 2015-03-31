#include "KeyBoardFunc.h"

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

