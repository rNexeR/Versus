#ifndef OBJETOSANIMADOS_H
#define OBJETOSANIMADOS_H

using namespace std;

class ObjetosAnimados : public Entidad
{
    public:
        bool colision;//ha chocado?
        string tipo;//obstáculo o disparo
        Box *detalles = new Box(0,0,0,0); //donde estará
//        vector<ALLEGRO_BITMAP*>* sprites;//
        ALLEGRO_BITMAP* sprite;
        int velocity = 1;
        ObjetosAnimados();//constructor
        virtual void act() = 0;
        void draw();//dibujo
        bool collision(Box* pCaja);//compara las colisiones entre objetos
        virtual ~ObjetosAnimados();
    protected:
    private:
};

#endif // OBJETOSANIMADOS_H
