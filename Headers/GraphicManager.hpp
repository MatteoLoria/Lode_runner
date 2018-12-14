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

    public:
        GraphicManager();
        GraphicManager(int);
        void drawMap(char [16][29]);
        void drawEntity(Entity *);
};
#endif