#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Player.hpp"
#include "Enemy.hpp"
#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H
class GraphicManager
{
    private:
        int level;
        int scale_w;
        int scale_h;
        int scale_x;
        int scale_y;
        ALLEGRO_DISPLAY * display;
        ALLEGRO_BITMAP * buffer;
        ALLEGRO_FONT * font;
    public:
        GraphicManager();
        GraphicManager(int, int, int ,int, int, ALLEGRO_BITMAP *, ALLEGRO_DISPLAY *);
        int drawMenu();
        void drawMap(char [16][28]);
        void drawEntity(Entity *);
        void drawFinalLadder(char [16][28]);
        void setLevel(int);
        int getLevel();
};
#endif