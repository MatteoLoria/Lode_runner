#include "../Headers/GameManager.hpp"
#include <iostream>
#define WINDOW_H 320
#define WINDOW_W 560

int main()
{
    al_init();
    al_init_image_addon();
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    
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
    int feedback = 1;
    int level = 0;
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    GraphicManager Gr(1, scaleW, scaleH, scaleX, scaleY, buffer, display);

    GameManager G(Gr);
    while(feedback != 2)
    {
        switch(feedback)
        {
            case 0:
                //da fare il menu
                break;
            case 1:
                ++level;
                Gr.setLevel(level);
                feedback = G.run(level, display);
                break;
        }
        if(feedback == -1)
            cout << "errore";
    }
    
    al_destroy_display(display);
    return 0;
}