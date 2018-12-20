#include "Entity.hpp"

#ifndef PLAYER_H
#define PLAYER_H
class Player : public Entity
{
    private:
        ALLEGRO_BITMAP * sprite[10];
        int lives=3;
    public:
        Player();
        Player(int, int, string[10]);
        ~Player();
        int getLives();
        string getEntity();
        void increaseLives();
        void decreaseLives();
        bool dig(char[16][28],bool);
};
#endif