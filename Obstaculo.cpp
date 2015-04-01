#include "Obstaculo.h"

Obstaculo::Obstaculo()
{
    if(!al_init_image_addon())//chequear si se pudo inicializar para las imágenes
    {
        cout<<"failed to initialize image addon!"<<endl;
    }
    //Inicialización de la posición de la cajita
    detalles->x = 200;
    detalles->y = 575;
    tipo = "obstaculo";//declarar el tipo de ObjetoAnimado
    string path = "GameFiles/assets/fondos/Lift.png";
    sprite = al_load_bitmap(path.c_str());//cargar el sprite según el path dado.
}

void Obstaculo::act(){
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
