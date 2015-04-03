#include "EnemigoAzul.h"

EnemigoAzul::EnemigoAzul(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, int level)
{
    velocity = 0.5;

    if(!al_init_image_addon())
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

    if (!al_reserve_samples(2)){
        fprintf(stderr, "failed to reserve samples!\n");
        return;
    }

    sonido = NULL;
    stop = NULL;
    vidas = 5;

    sonido = al_load_sample( "GameFiles/music/sfx_laser2.wav" );
    stop = al_load_sample( "GameFiles/music/stop.wav" );

    if(!sonido || !stop){
        printf( "Audio clip sample not loaded!\n" );
        return;
    }
    al_play_sample(sonido, 0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idsonido);
    al_play_sample(stop, 0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idstop);

    alternar = false;
    //carga de imagenes
    string path = "GameFiles/assets/personajes/enemies/blue/enemyBlue" + toString(level) + ".png";
    mapa_sprites[0] = vector<ALLEGRO_BITMAP*>();
    mapa_sprites[0].push_back(al_load_bitmap(path.c_str()));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    this->event_queue = event_queue;
    init(personajes, obstaculos);
    setAnimacion(0);
    disparos = new list<ObjetosAnimados*>;//Inicializar disparos
}

/**
    El patrón de movimiento del enemigo
**/
void EnemigoAzul::randomizarMovimiento(){
    int randomNumber = rand() % 100000;
    if (randomNumber % 100 == 0){
        alternar = true;
    }else if (randomNumber % 155 == 0){
        alternar = false;
    }

    int moveBy = 3;

    if(alternar && detalles->x > 0){
        detalles->x -= moveBy;
        if(detalles->y > 100)
            detalles->y -= (moveBy);
    }else if (!alternar && detalles->x < 450){
        detalles->x += moveBy;
    }
}

EnemigoAzul::~EnemigoAzul()
{
    //dtor
}
