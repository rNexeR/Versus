#ifndef ENEMIGOS_H
#define ENEMIGOS_H
#include "PersonajesAnimados.h"


class Enemigos : public PersonajesAnimados
{
    public:
        int firingRate; //paso al que disparará
        int variablesRandomEstado; //sugerible que sea >= 100,000
        int moveBy; //cuando se desplazará al azar
        int randomAlternative1, randomAlternative2; //valores para determinar la alternación de movimientos
        int laserDmg; //determinar el valor de daño del laser
        Enemigos();
        bool alternar = false; //determinará si se moverá al contrario o sentido que iba
        virtual void act(ALLEGRO_EVENT* ev);
        virtual int getTime();
        void randomizarMovimiento();//función para moverse al azar
        //virtual void determinarRandomMovimiento();
        virtual ~Enemigos();
    protected:
    private:
};

#endif // ENEMIGOS_H
