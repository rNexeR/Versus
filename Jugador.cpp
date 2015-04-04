#include "Jugador.h"

Jugador::Jugador(){

}

Jugador::Jugador(string name, int time)
{
    this->name = name;
    this->time = time;
}

int Jugador::getPosition(){
    return position;
}
string Jugador::getName(){
    return name;
}

int Jugador::getTime(){
    return time;
}

void Jugador::setPosition(int position){
    this->position = position;
}

void Jugador::setTime(int time){
    this->time = time;
}

void Jugador::setName(string name){
    this->name = name;
}

Jugador::~Jugador()
{
    //dtor
}
