#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Player.hpp"
#include "Enemy.hpp"
#include "SoundManager.hpp"
#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H
class GraphicManager
{
    private:
        int scale_w;      //risoluzione dinamica
        int scale_h;
        int scale_x;
        int scale_y;
        ALLEGRO_DISPLAY * display;
        ALLEGRO_BITMAP * buffer;
        ALLEGRO_FONT * font;
    public:
        GraphicManager();
        GraphicManager(const int&, const int& ,const int&, const int&, ALLEGRO_BITMAP *, ALLEGRO_DISPLAY *);
        ~GraphicManager();
        int drawMenu(SoundManager&);
        void drawMap(char [16][28], const int&);
        void drawEntity(Entity *);
        void drawFinalLadder(char [16][28]); //stampa la scala finale dopo aver raccolto tutte le monete
        void drawStats(const int& , const int&, const int&); //stampa le statistiche in tempo reale
        void drawYouDied(SoundManager&); //stampa la schermata della morte
        int drawFinal(SoundManager&);
        int drawCredits(SoundManager&);
        void setLevel(const int&);
        int getLevel();
};
#endif