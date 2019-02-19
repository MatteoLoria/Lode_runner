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
    Efficienza codice V
     -Astar V
     -Enemy V
     -Entity V
     -GameMan V
     -Graphic V 
     -main V
     -player V
     -HoleManager V
     -Sound V
    Commenti da aggiungere V
     -Astar V
     -Enemy V
     -Entity V
     -GameMan V
     -Graphic V
     -main V
     -player V
     -HoleManager V
     -Sound V
    Decidere i livelli (quarto e quinto) V
    Schermata you died V
    Schermata finale V
    Schermata crediti V
    Colori V
    Difficoltà V
    Bonus (per ora nemico)
*/
int main()
{   //inizializzazione allegro
    al_init();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    if (!al_install_mouse())
        exit(2);
    al_init_font_addon();
    al_install_keyboard();
    al_init_ttf_addon();
    //risoluzione dinamica
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
    int level = 0;
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //creazione oggetti
    GraphicManager Gr(scaleW, scaleH, scaleX, scaleY, buffer, display);
    SoundManager Sm;

    GameManager G;
    //gestione dei feedback ricevuti durante l'esecuzione del gioco
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
            if (level == 6)
            {
                feedback = Gr.drawFinal(Sm);
            }
            else
            {
                feedback = G.run(level, display, Sm, Gr);
            }
            break;
        case 4:
            G.setDiffulty(Gr.drawOptions(Sm));
            feedback = 0;
            break;
        case 3:
            feedback = Gr.drawCredits(Sm);
            break;
        case -1:
            return 0;
        }
    }
    //distruzione allegro
    al_destroy_bitmap(buffer);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_destroy_display(display);
    return 0;
}