/**
	Versus is a PC game programmed in C++ using the Allegro 5.0.11 library.
	Copyright (C) 2015  Nexer Rodríguez (rnexer) and Ricardo A. Interiano (Raim)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    For contact information read the README.md file.
**/
#include <stdio.h>


//LIBRERIAS DE PROYECTO
#include "Box.h"
#include "PersonajesAnimados.h"
#include "ObjetosAnimados.h"
#include "Obstaculo.h"
#include "PerPrincipal.h"
#include "EnemigoNegro.h"
#include "EnemigoAzul.h"
#include "EnemigoRojo.h"
#include "EnemigoVerde.h"
#include "MainMenu.h"

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_JOYSTICK *joystick = NULL;

//EVENTOS Y TIMERS
ALLEGRO_EVENT ev;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_TIMER *timer = NULL;

//Elementos Generales
Box *blogo = NULL;
ALLEGRO_BITMAP  *logo   = NULL;
ALLEGRO_BITMAP  *instru   = NULL;
ALLEGRO_BITMAP  *fondo   = NULL;
ALLEGRO_BITMAP  *pausa   = NULL;

ALLEGRO_SAMPLE *music = NULL;
ALLEGRO_SAMPLE_ID imusic;
ALLEGRO_SAMPLE *effect = NULL;
ALLEGRO_SAMPLE_ID ieffect;
ALLEGRO_SAMPLE *game = NULL;
ALLEGRO_SAMPLE_ID igame;

ALLEGRO_FONT *normalFont = NULL, *cartoonFont = NULL;
//Listas
list<PersonajesAnimados*> *personajes = new list<PersonajesAnimados*>();
list<ObjetosAnimados*> *obstaculos =  new list<ObjetosAnimados*>();
//list<Entidad*> *entidades; //TO-DO, debe ser usada para reemplazar las listas anteriores

multimap<int, string> jugadores;//inicializar vector con la cantidad de scores necesarios para el ranking

/**
    Inicialización de las funciones de Allegro
**/
int initAllegro()
{
    if(!al_init())
    {
        cout<<"failed to initialize allegro!\n"<<endl;
        return -1;
    }
    if(!al_install_joystick()){
        cout<<"failed to initialize joystick!\n"<<endl;
        return -1;
    }
    al_reconfigure_joysticks();
    joystick=al_get_joystick(al_get_num_joysticks()-1);

    if(!al_init_image_addon())
    {
        cout<<"Error: Failed to initialize al_init_image_addon!"<<endl;
        return -1;
    }

    display = al_create_display(width, height);
    if(!display)
    {
        cout<<"failed to create display!\n"<<endl;
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        cout<<"failed to create event_queue!\n"<<endl;
        al_destroy_display(display);
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        cout<<"failed to create timer!"<<endl;
    }

    if(!al_install_keyboard())
    {
        cout<<"failed to initialize the keyboard!"<<endl;
    }

    if(!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(2))
    {
        cout<<"failed to initialize Audio!"<<endl;
    }

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    normalFont = al_load_ttf_font("GameFiles/fonts/kenvector_future_thin.ttf",50,0 );
    cartoonFont = al_load_ttf_font("GameFiles/fonts/kenpixel_blocks.ttf",50,0 );

    if (!normalFont || !cartoonFont)
    {
        cout<<"Failed to initialize the font"<<endl;
        return -1;
    }

    game = al_load_sample("GameFiles/music/Raining Bits.wav");
    instru = al_load_bitmap("GameFiles/assets/fondos/Instrucciones.png");
    fondo = al_load_bitmap("GameFiles/assets/fondos/fondo.png");
    pausa = al_load_bitmap("GameFiles/assets/fondos/pausa.png");

    al_register_event_source(event_queue, al_get_display_event_source(display));//registrar eventos del display
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//registrar eventos del timer
    al_register_event_source(event_queue, al_get_keyboard_event_source());//registrar eventos del teclado
    al_register_event_source(event_queue, al_get_joystick_event_source());//registrar eventos del joystick

    al_init_timeout(&timeout, 0.06);
    return 0;
    }

    /**
    Inicializar el logo
**/
int initLogo()
{
    logo = al_load_bitmap("Versus.png");

    if(!logo)
    {
        cout<<"Error: Failed to load image!"<<endl;
        al_destroy_display(display);
        return -1;
    }
    blogo = new Box(0,0,al_get_bitmap_width(logo), al_get_bitmap_height(logo));
    blogo->x = (width-blogo->width)/2;
    blogo->y = (height-blogo->height)/2;

    return 0;
}

/**
    Muestra la imagen inicial (comienzo del juego)
**/
void showSplash()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(logo,blogo->x,blogo->y,0);
    al_flip_display();
    al_rest(splashTime);
}

void showPause()
{
    while (true){
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if (teclaDownEvent(&ev, ALLEGRO_KEY_ESCAPE))
            break;
        al_draw_bitmap(pausa,(width/2)- 150, (height/2)-100,0);
        al_flip_display();
    }
}

void showInstrucciones(){
    while(1){
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(get_event && (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || teclaDownEvent(&ev, ALLEGRO_KEY_ESCAPE)))
            break;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(instru,0,0,0);
        al_flip_display();
    }
}

void showRanking(){
    changeSizeFont(cartoonFont, 30);
    while(true){
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(get_event && (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || teclaDownEvent(&ev, ALLEGRO_KEY_ESCAPE)))//waiting to escape
            break;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fondo,0,0,0);

        //Load text
        al_draw_text(cartoonFont, al_map_rgb(102,204,0), width/2, (height/2)- 100,ALLEGRO_ALIGN_CENTER, "RANKING");
        /**/
        int scorePosition = 1;
        int y = 0;

        float scoreCoordinate = 5;
        //Print scores
        for(multimap<int, string>::iterator x = jugadores.begin();//initial value
            x != jugadores.end(); //limit
            x++){//increment
            //Initialize name
            string playerScore = toString(scorePosition);
            scorePosition++;
            playerScore += ". ";
            string playerName = (*x).second;
            playerScore += playerName;
            int timeScore = (*x).first;

            //Draw the position and name
            al_draw_textf(cartoonFont, al_map_rgb(255,255,255), 30, (height/2) + scoreCoordinate - 50,
                ALLEGRO_ALIGN_LEFT, playerScore.c_str());

            //Draw the time it took that person to finish all levels
            playerScore = "TIEMPO   ";
            playerScore += toString(timeScore);

            al_draw_textf(cartoonFont, al_map_rgb(255,255,255), 300, (height/2) + scoreCoordinate - 50,
                ALLEGRO_ALIGN_LEFT, playerScore.c_str());

            scoreCoordinate += 40;

            y++;
            if (y >= CANTIDAD_SCORES)//Get out if there are too much
                break;
        }
        /** **/
        al_flip_display();
    }
}

/**
    Obtener un apuntador al personaje principal
**/
PersonajesAnimados* getPrincipal(){
    for(list<PersonajesAnimados*>::iterator i = personajes->begin(); i!=personajes->end(); i++)
    {
        if ((*i)->tipoObjeto == "Principal")
            return (*i);
    }
}

/**
    Borra los personajes de la lista individualmente
**/
void cleanPersonajes()
{
    for(list<PersonajesAnimados*>::iterator i = personajes->begin(); i!=personajes->end(); i++)
    {
        if ((*i) != getPrincipal())
            delete (*i);
    }
}

/**
    Borra los obstáculos de la lista individualmente
**/
void cleanObstaculos()
{
    for(list<ObjetosAnimados*>::iterator i = obstaculos->begin(); i != obstaculos->end(); i++)
        delete (*i);
}

void cleanBullets(){
    if(getPrincipal()->disparos->size() > 0)
    for(list<ObjetosAnimados*>::iterator i = getPrincipal()->disparos->begin(); i != getPrincipal()->disparos->end(); i++)
        delete (*i);
    getPrincipal()->disparos->clear();
}

/**
    Inicialización del juego (main game)
**/
void resetGame()
{
    cleanPersonajes();
    cleanObstaculos();//limpiar obstacles
    obstaculos->clear();
}

/**
    Carga los recursos necesarios para el nivel especificado
**/
void loadLvl(int level){
    resetGame();
    obstaculos->push_back(new Obstaculo(0, obstaculos));
    obstaculos->push_back(new Obstaculo(200, obstaculos));
//    if(level != 1)
        cleanBullets();
    if (level == 1){
        //SOLO NEGROS
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 1));
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 2));
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 3));
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 4));
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 1));
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 2));

    }else if (level == 2){
        //NEGROS Y VERDES
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 3));
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 4));
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 1));

        personajes->push_back(new EnemigoVerde(event_queue, personajes, obstaculos, display, 1));
        personajes->push_back(new EnemigoVerde(event_queue, personajes, obstaculos, display, 2));
        personajes->push_back(new EnemigoVerde(event_queue, personajes, obstaculos, display, 3));

    }else if (level == 3){
        //NEGROS, VERDES Y AZULES
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 3));
        personajes->push_back(new EnemigoNegro(event_queue, personajes, obstaculos, display, 4));

        personajes->push_back(new EnemigoVerde(event_queue, personajes, obstaculos, display, 4));
        personajes->push_back(new EnemigoVerde(event_queue, personajes, obstaculos, display, 3));

        personajes->push_back(new EnemigoAzul(event_queue, personajes, obstaculos, display, 1));
        personajes->push_back(new EnemigoAzul(event_queue, personajes, obstaculos, display, 2));

    }else if (level == 4){
        //VERDES, AZULES Y ROJOS
        personajes->push_back(new EnemigoVerde(event_queue, personajes, obstaculos, display, 4));
        personajes->push_back(new EnemigoVerde(event_queue, personajes, obstaculos, display, 1));

        personajes->push_back(new EnemigoAzul(event_queue, personajes, obstaculos, display, 3));
        personajes->push_back(new EnemigoAzul(event_queue, personajes, obstaculos, display, 4));

        personajes->push_back(new EnemigoRojo(event_queue, personajes, obstaculos, display, 3));
        personajes->push_back(new EnemigoRojo(event_queue, personajes, obstaculos, display, 1));

    }
}

/**
    Ejecuta el nivel
**/
int nivel(string nombre, int level){
    /*
        CREACION DE PERSONAJES, ENEMIGOS Y OBSTÁCULOS
    */
    changeSizeFont(cartoonFont, 50);
    al_clear_to_color(al_map_rgb(0,0,0));
    string path = "LVL "+toString(level);
    al_draw_text(cartoonFont, al_map_rgb(255,255,255), width/2, height/2,ALLEGRO_ALIGN_CENTRE, path.c_str());
    al_flip_display();
    loadLvl(level);
    al_rest(3);
    int seg = 0;
    changeSizeFont(normalFont, 15);
    changeSizeFont(cartoonFont, 20);
    ALLEGRO_BITMAP *mes;
    while(1)
    {
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(getPrincipal()->muerto || (get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
        {
            seg = -1;
            mes = al_load_bitmap("GameFiles/assets/fondos/Lose.png");
            break;
        }
        if (teclaDownEvent(&ev, ALLEGRO_KEY_ESCAPE))
            showPause();
        if (personajes->size()<=1 && getPrincipal()->vidas > 0){
            mes = al_load_bitmap("GameFiles/assets/fondos/Win.png");
            break;
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_text(normalFont, al_map_rgb(255,255,255), 0, 0,ALLEGRO_ALIGN_LEFT, nombre.c_str());
        al_draw_text(cartoonFont, al_map_rgb(255,255,255), width, 0,ALLEGRO_ALIGN_RIGHT, toString(seg).c_str());
        /*
            CICLOS DE LAS LISTAS DE PERSONAJES, ENEMIGOS Y OBJETOS
            SE USAN SUS DRAWS Y ACTS
        */
        for(list<PersonajesAnimados*>::iterator i = personajes->begin(); i!=personajes->end(); i++)
        {
            if ((*i)->tipoObjeto == "Principal")
                seg = (*i)->getTime();
            (*i)->act();
            (*i)->draw();
        }

        vector<list<PersonajesAnimados*>::iterator>borrar;
        for(list<PersonajesAnimados*>::iterator i=personajes->begin(); i != personajes->end(); i++)
        {
            if ((*i)->tipoObjeto == "Enemigo" && ((*i)->muerto == true || (*i)->detalles->y > 600 || (*i)->vidas <= 0)) //si está muerto o se paso
            {
                borrar.push_back(i);//añadir a los de borrar
            }
        }
        for(int x = 0; x < borrar.size(); x++) //recorrer los que morirán
        {
            personajes->erase(borrar[x]);
            delete (*borrar[x]);
        }


        //OBJETOS ANIMADOS
        for(list<ObjetosAnimados*>::iterator i = obstaculos->begin(); i!=obstaculos->end(); i++)
        {
            (*i)->draw();
            (*i)->act();
        }

        al_flip_display();
    }
    al_draw_bitmap(mes, 75,200,0);
    al_flip_display();
    al_rest(2);
    al_destroy_bitmap(mes);
    return seg;
}

/**
    Leer todos los scores en el archivo
    y guardarlos en un vector
**/
void readScores(){
    //xff3d
    ifstream in("scores.vrs");
    if (!in)
        return;
    in.seekg(0, ios::end);
    int tamano = in.tellg();
    int cant = tamano / SIZE_FORMATO;
    in.seekg(0, ios::beg);
    jugadores.clear();//limpiar multimap
    for (int x = 0; x < cant; x++){
        string nombre;
        char* n = new char[10];
        int time;
        in.read((char*)&time, 4);
        in.read(n, 10);
        nombre = n;
        jugadores.insert(pair<int, string>(time, nombre));
    }


    in.close();
}

/**
    Guardar Scores
**/
void writeScore(string nombre, int seg){
    string archivo = "scores.vrs";
    ofstream out(archivo.c_str());
    int y = 0;
    jugadores.insert(pair<int, string>(seg, nombre));
    for(multimap<int, string>::iterator x = jugadores.begin(); x != jugadores.end(); x++){
        int time = (int)(*x).first;
        string name = (*x).second;
        out.write((char*)&time, 4);
        out.write(name.c_str(), 10);
        y++;
        if (y >= CANTIDAD_SCORES)
            break;
    }
    out.close();
}

/**
    Ciclo principal del juego
**/
void loopJuego()
{
    al_play_sample(game, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &igame);
    string nombre;
    nombre = ingresarNombre(&ev, event_queue, &timeout, fondo);
    resetGame();
    personajes->push_back(new PerPrincipal(event_queue, personajes, obstaculos, display));
    if (nivel(nombre,1) > 0){
        if(nivel(nombre,2) > 0){
            if(nivel(nombre,3) > 0){
                int seg = nivel(nombre,4);
                if(seg > 0){
                    writeScore(nombre, seg);
                    }//lvl 4
                }//lvl 3
            }//lvl 2
    }//lvl 1
    al_stop_sample(&igame);
    delete getPrincipal();
    personajes->clear();
}

/**
    Ciclo principal del menú
**/
void mainMenu()
{
    readScores();
    ALLEGRO_BITMAP *select = NULL, *options = NULL;
    music = al_load_sample("GameFiles/music/So, let see, what you can_0.wav");
    effect = al_load_sample("GameFiles/music/sfx_laser1.wav");
    al_play_sample(music, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&imusic);//Ejecutar sonido de musica
    Box *bselect = NULL, *boptions = NULL;
    int uPosy, uPosyOriginal;

    select = al_load_bitmap("GameFiles/assets/menu/uselect.png");
    bselect = new Box(0,0,al_get_bitmap_width(select), al_get_bitmap_height(select));
    bselect->x = (width-bselect->width)/2;
    bselect->y = (height-bselect->height)/2;

    int espaciado = 35;
    options = al_load_bitmap("GameFiles/assets/menu/opciones.png");
    boptions = new Box(0,0,al_get_bitmap_width(options), al_get_bitmap_height(options));
    boptions->x = (width-boptions->width)/2;
    boptions->y = (height-boptions->height)/2;

    uPosyOriginal = (height/2)+60;
    uPosy = uPosyOriginal;

    if (!select || !options)
        return;

    while(true)
    {
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        if(get_event && teclaDownEvent(&ev, ALLEGRO_KEY_S))
        {
            al_stop_sample(&ieffect);
            al_play_sample(effect, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&ieffect);
            uPosy += espaciado;
        }
        else if(get_event && teclaDownEvent(&ev, ALLEGRO_KEY_W))
        {
            al_stop_sample(&ieffect);
            al_play_sample(effect, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&ieffect);
            uPosy -= espaciado;
        }
        else if(get_event && teclaDownEvent(&ev, ALLEGRO_KEY_ENTER))
        {
            if (uPosy == uPosyOriginal)
            {
                //llamar el loop del juego
                al_stop_samples();
                loopJuego();
                al_play_sample(music, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&imusic);
            }
            else if (uPosy == uPosyOriginal+espaciado)
            {
                //llamar el loop de instrucciones
                showInstrucciones();
            }
            else if(uPosy == uPosyOriginal+(espaciado*2))
            {
                //llamar el loop de Scores
                readScores();
                showRanking();
            }
            else
            {
                break;
            }
        }
        if (uPosy>uPosyOriginal+(espaciado*3))
            uPosy = uPosyOriginal;
        if (uPosy<uPosyOriginal)
            uPosy = uPosyOriginal+(espaciado*3);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fondo,0,0,0);
        al_draw_bitmap(logo,blogo->x,blogo->y - 100,0);
        al_draw_bitmap(options,boptions->x,boptions->y + 100,0);
        al_draw_bitmap(select, bselect->x, uPosy, 0);

        al_flip_display();
    }
    al_destroy_bitmap(options);//destruir bitmaps de opciones una vez no se ocupen
    al_destroy_bitmap(select);//destruir bitmaps de select
}

int main(int argc, char **argv)
{
    //readScores();
    if (initAllegro()<0 || initLogo()<0)
        return -1;
    showSplash();

    MainMenu menu;
    cout<<"Llego aki 1"<<endl;
    menu.show(display);
    cout<<"Llego aki 2"<<endl;
//    mainMenu();
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_sample(music);
    al_destroy_sample(effect);
    al_destroy_sample(game);
    al_destroy_bitmap(logo);
    al_destroy_bitmap(instru);
    al_destroy_bitmap(fondo);
    al_destroy_bitmap(pausa);

    cleanPersonajes();
    return 0;
}
