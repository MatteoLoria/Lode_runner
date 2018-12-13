#include "../Headers/Enemy.hpp"
<<<<<<< HEAD
=======

>>>>>>> 221460ff459d05af3c5bf6ebd6204055219f6589
Enemy::Enemy() : Entity()
{
    for(int i = 0; i < 16; ++i)
        sprite[i] = NULL;
}

Enemy::Enemy(int x, int y, string sprite[16]) : Entity(x, y)
{
    for(int i = 0; i < 16; ++i)
        this->sprite[i] = al_load_bitmap(sprite[i].c_str());
}

void Enemy::redHat() {hat = true;}

bool Enemy::isRedHat() {return hat;}