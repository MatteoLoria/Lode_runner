#include "Entity.hpp"

#ifndef PLAYER_H
#define PLAYER_H
class Player : public Entity
{
    private:
        ALLEGRO_BITMAP * sprite[10];
        int lives=3;
        int points=0;
    public:
        Player();
        Player(int, int, string[10]);
        ~Player();
        int getLives();
        string getEntity();
        void increaseLives();
        void decreaseLives();
        void increasePoints();
        int getPoints();
        void setPoints(int);
        bool dig(char[16][28], bool);
};
#endif