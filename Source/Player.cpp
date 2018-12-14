#include "../Headers/Player.hpp"

Player::Player() : Entity()
{
    for(int i = 0; i < 9; ++i)
        sprite[i] = NULL;
}

Player::Player(int x, int y, string sprite[9]) : Entity(x, y)
{
    for(int i = 0; i < 9; ++i)
        this->sprite[i] = al_load_bitmap(sprite[i].c_str()); 
}

Player::~Player()
{
    for(int i = 0; i < 9; ++i)
        al_destroy_bitmap(sprite[i]);
}

string Player::getEntity() {return "Player";}

int Player::getLives(){return lives;}
void Player::decreaseLives(){lives--;}
void Player::increaseLives(){lives++;}
