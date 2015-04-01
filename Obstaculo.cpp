#include "Obstaculo.h"

Obstaculo::Obstaculo(int variacion)
{
    if(!al_init_image_addon())//chequear si se pudo inicializar para las imágenes
    {
        cout<<"failed to initialize image addon!"<<endl;
    }
    //Inicialización de la posición de la cajita
    detalles->x = 200 + variacion;
    detalles->y = 550;
    tipoObjeto = "obstaculo";//declarar el tipo de ObjetoAnimado
    string path = "GameFiles/assets/fondos/Lift.png";
    sprite = al_load_bitmap(path.c_str());//cargar el sprite según el path dado.
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
