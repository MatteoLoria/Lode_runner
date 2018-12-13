#include "allegro5/allegro5.h"
#include "Entity.hpp"
#include <string>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H
class Player : public Entity
{
    private:
        ALLEGRO_BITMAP * sprite[8];

    public:
        Player();
        Player(int, int, string[8]);
};
#endif