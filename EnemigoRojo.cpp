#include "EnemigoRojo.h"

EnemigoRojo::EnemigoRojo(ALLEGRO_EVENT_QUEUE *event_queue, list<PersonajesAnimados *> *personajes, list<ObjetosAnimados*>*obstaculos, int level)
{
    velocity = 0.05;
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
    vidas = 50;

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
    string path = "GameFiles/assets/personajes/enemies/red/enemyRed" + toString(level) + ".png";
    mapa_sprites[0] = vector<ALLEGRO_BITMAP*>();
    mapa_sprites[0].push_back(al_load_bitmap(path.c_str()));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    this->event_queue = event_queue;
    init(personajes, obstaculos);
    setAnimacion(0);
    disparos = new list<ObjetosAnimados*>;//Inicializar disparos
}

void EnemigoRojo::act(ALLEGRO_EVENT* ev){
    detalles->y+=velocity;
    int randomEstado = rand() % 100000;

    if(randomEstado % 10 == 0){//Si es divisible entre x, entonces agregar el disparo
        al_stop_sample(&idsonido);
        al_play_sample(sonido, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&idsonido);
        disparos->push_back(new Disparos(1, detalles->x + 15, detalles->y + 40, 0));
    }

    randomizarMovimiento();

    frame++;
    if (detalles->y > 600 || vidas < 0)
        muerto = true;
}

void EnemigoRojo::randomizarMovimiento(){
    int randomNumber = rand() % 10000;
    if (randomNumber % 175 == 0){
        alternar = true;
    }else if (randomNumber % 125 == 0){
        alternar = false;
    }

    int moveBy = 5;

    if(alternar & detalles->x > 0){
        detalles->x -= moveBy;
    }else if (!alternar & detalles->x < 450){
        detalles->x += moveBy;
    }
}


EnemigoRojo::~EnemigoRojo()
{
    //dtor
}
