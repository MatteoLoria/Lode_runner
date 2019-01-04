#include "../Headers/Player.hpp"
#include <iostream>
using namespace std;
Player::Player() : Entity()
{
    for (int i = 0; i < 10; ++i)
        sprite[i] = NULL;
}

Player::Player(int x, int y, string sprite[10]) : Entity(x, y)
{
    for (int i = 0; i < 10; ++i)
        this->sprite[i] = al_load_bitmap(sprite[i].c_str());
}

Player::~Player()
{
    for (int i = 0; i < 10; ++i)
        al_destroy_bitmap(sprite[i]);
}
bool Player::dig(char map[16][28], bool sx)
{
    if (!sx && (map[this->getY() / 20][(this->getX() + 39) / 20] != '$' && map[this->getY() / 20][(this->getX() + 39) / 20] != 'H' && map[this->getY() / 20][(this->getX() + 39) / 20] != '0'))
    {
        if (map[(this->getY() + 5) / 20][(this->getX() + 39) / 20] == '#')
        {
            map[(this->getY() + 5) / 20][(this->getX() + 39) / 20] = '1';
            return true;
        }
    }
    if (sx && (map[this->getY() / 20][(this->getX() / 20) - 1] != '$' && map[this->getY() / 20][(this->getX() / 20) - 1] != 'H' && map[this->getY() / 20][(this->getX() / 20) - 1] != '0'))
    {
        if (map[(this->getY() + 5) / 20][(this->getX() / 20) - 1] == '#')
        {
            map[(this->getY() + 5) / 20][(this->getX() / 20) - 1] = '1';
            return true;
        }
    }
    return false;
}
string Player::getEntity() { return "Player"; }

int Player::getLives() { return lives; }
void Player::decreaseLives() { lives--; }
void Player::increaseLives() { lives++; }
