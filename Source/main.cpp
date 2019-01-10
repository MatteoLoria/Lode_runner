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
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    GraphicManager Gr(1, scaleW, scaleH, scaleX, scaleY, buffer, display);
    
    string sprite[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string Esprite[12] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
    Player P(14 * 20, (14 * 20) + 18, sprite);
    //Enemy e1(14 * 20, (9 * 20) + 18, Esprite);
    //Enemy e2(23 * 20, (6 * 20) + 18, Esprite);
    //Enemy e3(5 * 20, (6 * 20) + 18, Esprite);
    //Enemy e4(15 * 20, (14 * 20) + 18, Esprite);

    vector<Enemy> enemies;
    //enemies.push_back(e1);
    //enemies.push_back(e2);
    //enemies.push_back(e3);
    //enemies.push_back(e4);

    GameManager G(P, enemies, Gr);
    G.run(1, display);
    
    al_destroy_display(display);
    return 0;
}