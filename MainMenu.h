#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "Tools.h"

class MainMenu
{
public:
    MainMenu()
    {
        initAllegro();
    }

    void show()
    {

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
                if(&ieffect)
                    al_stop_sample(&ieffect);
                al_play_sample(effect, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&ieffect);
                uPosy += espaciado;
            }
            else if(get_event && teclaDownEvent(&ev, ALLEGRO_KEY_W))
            {
                if(&ieffect)
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
                    //loopJuego();
                    al_play_sample(music, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&imusic);
                }
                else if (uPosy == uPosyOriginal+espaciado)
                {
                    //llamar el loop de instrucciones
                    //showInstrucciones();
                }
                else if(uPosy == uPosyOriginal+(espaciado*2))
                {
                    //llamar el loop de Scores
                    //readScores();
                    //showRanking();
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

    int initAllegro()
    {
        if(!al_init())
        {
            cout<<"failed to initialize allegro!\n"<<endl;
            return -1;
        }
        if(!al_install_joystick())
        {
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

        display = al_create_display(width, height);
        if(!display)
        {
            cout<<"failed to create display!\n"<<endl;
            return -1;
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
        if (initLogo()<0)
            return -1;
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


private:
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_JOYSTICK *joystick = NULL;

    Box *blogo = NULL;
    ALLEGRO_BITMAP  *logo   = NULL;
    ALLEGRO_BITMAP  *instru   = NULL;
    ALLEGRO_BITMAP  *fondo   = NULL;
    ALLEGRO_BITMAP  *pausa   = NULL;

//EVENTOS Y TIMERS
    ALLEGRO_EVENT ev;
    ALLEGRO_TIMEOUT timeout;
    ALLEGRO_TIMER *timer = NULL;

    ALLEGRO_SAMPLE *music = NULL;
    ALLEGRO_SAMPLE_ID imusic;
    ALLEGRO_SAMPLE *effect = NULL;
    ALLEGRO_SAMPLE_ID ieffect;
    ALLEGRO_SAMPLE *game = NULL;
    ALLEGRO_SAMPLE_ID igame;

    ALLEGRO_FONT *normalFont = NULL, *cartoonFont = NULL;
};


#endif // MAINMENU_H_INCLUDED
