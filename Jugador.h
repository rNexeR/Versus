#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
using namespace std;

class Jugador
{
    public:
        int getPosition();
        string getName();
        int getTime();
        void setPosition(int position);
        void setTime(int time);
        void setName(string name);
        Jugador();
        Jugador(string name, int time);
        virtual ~Jugador();
    protected:
    private:
        string name;
        int time;
        int position;
};

#endif // JUGADOR_H
