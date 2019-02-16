#include "../Headers/GameManager.hpp"
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define WINDOW_H 320
#define WINDOW_W 560
/*

    Lista:
    Pulizia cartelle V
    Suoni V
    Efficienza codice
     -Astar
     -Enemy V
     -Entity V
     -GameMan
     -Graphic V 
     -main
     -player V
     -HoleManager V
     -Sound V
    Commenti da aggiungere
     -Astar V
     -Enemy (da valutare isInhole e se il nemico potrà mai cadere)
     -Entity V
     -GameMan V
     -Graphic V(c'è poco da dire)
     -main
     -player V
     -HoleManager V
     -Sound V
    Schermata finale
    Schermata you died V
    Schermata crediti
    Colori
    Bonus (per ora nemico)
    Difficoltà
    Trollface (secondo livello)
    Decidere i livelli (quarto e quinto)
*/
int main()
{
    al_init();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    if(!al_install_mouse())
        exit(2);
    al_init_font_addon();
    al_install_keyboard();
    al_init_ttf_addon();
    ALLEGRO_DISPLAY *display = al_create_display(WINDOW_W, WINDOW_H);
    ALLEGRO_BITMAP *buffer = al_create_bitmap(WINDOW_W, WINDOW_H);
    int windowHeight = al_get_display_height(display);
    int windowWidth = al_get_display_width(display);
    float sx = windowWidth / float(WINDOW_W);
    float sy = windowHeight / float(WINDOW_H);
    int scale = std::min(sx, sy);
    int scaleW = WINDOW_W * scale;
    int scaleH = WINDOW_H * scale;
    int scaleX = (windowWidth - scaleW) / 2;
    int scaleY = (windowHeight - scaleH) / 2;
    int feedback = 0;
    int level = 2;
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    GraphicManager Gr(scaleW, scaleH, scaleX, scaleY, buffer, display);
    SoundManager Sm;

    GameManager G;
    while (feedback != 2)
    {
        switch (feedback)
        {
            case 0:
                level = 0;
                feedback = Gr.drawMenu(Sm);
                break;
            case 1:
                ++level;
                feedback = G.run(level, display, Sm, Gr);
                break;
            case 3:
                //i credits poi li faccio
                break;
            case -1:
                return 0;
                break;
        }
    }
    al_destroy_bitmap(buffer);
    al_uninstall_keyboard();
    al_uninstall_audio();
    al_uninstall_mouse();
    al_destroy_display(display);
    return 0;
}