#ifndef KEYBOARDFUNC_H
#define KEYBOARDFUNC_H
#include <allegro5/allegro.h>

ALLEGRO_EVENT ev;

void teclaPresionada(int keycode, bool *variable);
bool teclaDownEvent(int keycode);

#endif // KEYBOARDFUNC_H
