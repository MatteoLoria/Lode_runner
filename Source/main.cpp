/*
 @authors Matteo Notaro               &  Matteo Loria
 @github  https://github.com/MattNot     https://github.com/MatteoLoria

 19/02/2019
*/

#include "../Headers/GameManager.hpp"
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define WINDOW_H 320
#define WINDOW_W 560

int main()
{   //inizializzazione allegro
    if(!al_init())
    {
        cout<<"Fatal error, Allegro 5 failed to start";
        return -1;
    }
    if(!al_init_image_addon()){
        cout << "Fatal error, Allegro 5 failed to start";
        return -1;
    }
    if(!al_install_audio()){
        cout << "Fatal error, Allegro 5 failed to start";
        return -1;
    }
    if(!al_init_acodec_addon()){
        cout << "Fatal error, Allegro 5 failed to start";
        return -1;
    }
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    if (!al_install_mouse()){
        cout << "Fatal error, Allegro 5 failed to start";
        return -1;
    }
    if(!al_init_font_addon()){
        cout << "Fatal error, Allegro 5 failed to start";
        return -1;
    }
    if(!al_install_keyboard()){
        cout << "Fatal error, Allegro 5 failed to start";
        return -1;
    }
    if(!al_init_ttf_addon()){
        cout << "Fatal error, Allegro 5 failed to start";
        return -1;
    }
    //risoluzione dinamica
    ALLEGRO_DISPLAY *display = al_create_display(WINDOW_W, WINDOW_H);
    if(!display){
        cout << "Fatal error, unable to create a display";
        return -1;
    }
    ALLEGRO_BITMAP *buffer = al_create_bitmap(WINDOW_W, WINDOW_H);
    if(!buffer){
        cout << "Fatal error, unable to create a buffer";
        return -1;
    }
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