#include "../Headers/GameManager.hpp"
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define WINDOW_H 320
#define WINDOW_W 560

int main()
{
    al_init();
    al_init_image_addon();
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_install_mouse();
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
    int level = 0;
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    GraphicManager Gr(scaleW, scaleH, scaleX, scaleY, buffer, display);

    GameManager G(Gr);
    while (feedback != 2)
    {
        switch (feedback)
        {
        case 0:
            level = 0;
            feedback = Gr.drawMenu();
            break;
        case 1:
            ++level;
            feedback = G.run(level, display);
            break;
        case 3:
            //i credits poi li faccio
            break;
        }
        if (feedback == -1)
            return 0;
    }

    al_destroy_display(display);
    return 0;
}