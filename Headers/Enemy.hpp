#include "Entity.hpp"

#ifndef ENEMY_H
#define ENEMY_H
class Enemy : public Entity
{
    private:
        ALLEGRO_BITMAP * sprite[16];
        bool hat = false;

    public:
        Enemy();
        Enemy(int, int, string[16]);
        void redHat();
        bool isRedHat();
};
#endif