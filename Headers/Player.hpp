#include "Entity.hpp"

#ifndef PLAYER_H
#define PLAYER_H
class Player : public Entity
{
    private:
        ALLEGRO_BITMAP * sprite[8];
        int lives=3;
    public:
        Player();
        Player(int, int, string[8]);
        int getLives();
        void increaseLives();
        void decreaseLives();
};
#endif