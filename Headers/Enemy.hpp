#include "Entity.hpp"

#ifndef ENEMY_H
#define ENEMY_H
class Enemy : public Entity
{
    private:
        ALLEGRO_BITMAP * sprite[12];
        bool hat = false;

    public:
        Enemy();
        Enemy(int, int, string[12]);
        ~Enemy();
        string getEntity();
        void redHat();
        bool isRedHat();
};
#endif