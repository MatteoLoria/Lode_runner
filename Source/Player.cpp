#include "../Headers/Player.hpp"

Player::Player() : Entity()
{
    for(int i = 0; i < 8; ++i)
        sprite[i] = NULL;
}

Player::Player(int x, int y, string sprite[8]) : Entity(x, y)
{
    for(int i = 0; i < 8; ++i)
        this->sprite[i] = al_load_bitmap(sprite[i].c_str()); 
}