#include "Entity.hpp"
#include <allegro5/allegro.h>
#include <string>
using namespace std;

#ifndef ENEMY_H
#define ENEMY_H
class Enemy : public Entity
{
    private:
        ALLEGRO_BITMAP * sprite[16];

    public:
        Enemy();
        Enemy(int, int, string[16]);
};
#endif