#include "Disparos.h"

Disparos::Disparos(int dmg, int posX, int posY)
{
    this->dmg = dmg;
    velocity = 10;
    //Inicializaciones de audio

    if(!al_init_image_addon())//chequear si se pudo inicializar para las imágenes
    {
        cout<<"failed to initialize image addon!"<<endl;
    }

    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        return;
    }

    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return;
    }

    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        return;
    }

    sonido = NULL;

    sonido = al_load_sample( "GameFiles/music/sfx_laser2.wav" );

    if(!sonido){
        printf( "Audio clip sample not loaded!\n" );
        return;
    }

    al_play_sample(sonido, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

    //Inicialización de la posición de la cajita
    detalles->x = posX;
    detalles->y = posY - 40;
    tipoObjeto = "Disparo";//declarar el tipo de ObjetoAnimado
    string path = "GameFiles/assets/lasers/laserBlue.png";
    sprite = al_load_bitmap(path.c_str());//cargar el sprite según el path dado

    if(!sprite)
        return;

    detalles->width = al_get_bitmap_width(sprite);
    detalles->height = al_get_bitmap_height(sprite);
}

Disparos::~Disparos()
{
    al_destroy_sample(sonido);
    //al_destroy_bitmap(sprite);
    delete detalles;
    //dtor
}

void Disparos::act(ALLEGRO_EVENT *ev){
    detalles->y -= velocity;
}

void Disparos::draw(){
    if (sprite)//si el sprite está cargado, dibujar
        al_draw_bitmap(sprite, detalles->x, detalles->y, 0);
//        al_draw_scaled_rotated_bitmap(sprite,
//            detalles->x, detalles->y, 1, 1, 1, 1, 0, 0);

        /*(ALLEGRO_BITMAP *bitmap,
            float cx, float cy, float dx, float dy, float xscale, float yscale,
            float angle, int flags)
        */
}





