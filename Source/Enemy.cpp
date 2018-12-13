#include "../Headers/Enemy.hpp"
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