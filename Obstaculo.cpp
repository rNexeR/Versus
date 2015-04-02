#include "Obstaculo.h"

Obstaculo::Obstaculo(int variacion, list<ObjetosAnimados*>*obstaculos)
{
    if(!al_init_image_addon())//chequear si se pudo inicializar para las imágenes
    {
        cout<<"failed to initialize image addon!"<<endl;
    }
    //Inicialización de la posición de la cajita
    detalles->x = 200 + variacion;
    detalles->y = 550;
    detalles->width = 50;
    detalles->height = 25;
    tipoObjeto = "Obstaculo";//declarar el tipo de ObjetoAnimado
    string path = "GameFiles/assets/fondos/Lift.png";
    sprite = al_load_bitmap(path.c_str());//cargar el sprite según el path dado.
    //Validar carga del sprite
    if(!sprite){
        cout<<"ERROR AL CARGAR SPRITES!";
        return;
    }

    this->obstaculos = obstaculos;
}

/**
    El act del obstaculo; por mientras está rebotando de izquierda a derecha dependiendo de su posición
**/
void Obstaculo::act(ALLEGRO_EVENT* ev){
    if (detalles->x < 0){//si choca en la izquierda, alternar a derecha
        alternar = true;
    }
    else if (detalles->x > 450){//si choca en la derecha, alterna a izquierda
        alternar = false;
    }

    for(list<ObjetosAnimados*>::iterator i = obstaculos->begin(); i != obstaculos->end(); i++){
        if((*i)->tipoObjeto == "Obstaculo"){
            cout<<"Comparamos: "<<endl;
            if(colision( (*i)->detalles) ){
                cout<<"Whoo, we crashed!"<<endl;
                alternar = !alternar;
            }
        }
    }

    if(alternar){
        detalles->x += velocity;//aumentar, move right
    }else{
        detalles->x -= velocity;//aumentar, move left
    }
//    cout<<"X: "<<detalles->x<<endl;
}

Obstaculo::~Obstaculo()
{
    //dtor
}
