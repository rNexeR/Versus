#include "Jugador.h"

Jugador::Jugador(){

}

Jugador::Jugador(string name, int time)
{
    this->name = name;
    this->time = time;
}

string Jugador::getName(){
    return name;
}

int Jugador::getTime(){
    return time;
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
