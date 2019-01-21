#include "Entity.hpp"

#ifndef PLAYER_H
#define PLAYER_H
class Player : public Entity
{
    private:
        int lives=3;
        int points=0;
    public:
        Player();
        Player(int, int, string[10]);
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