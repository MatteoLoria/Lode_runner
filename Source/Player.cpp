#include "../Headers/Player.hpp"
#include <iostream>
using namespace std;

string Player::getEntity() { return "Player"; }
int Player::getPoints(){return points;}
int Player::getLives() { return lives; }
void Player::decreaseLives() { lives--; }
void Player::increaseLives() { lives++; }
void Player::increasePoints() { points++; }
void Player::setPoints(int points) {this->points = points;}

Player::Player() : Entity() {}

Player::Player(int x, int y, string sprite[10]) : Entity(x, y) {}

bool Player::dig(char map[16][28], bool sx)
{
    if (!sx && (map[this->getY() / 20][(this->getX() + 39) / 20] != '$' && map[this->getY() / 20][(this->getX() + 39) / 20] != 'H' 
        && map[this->getY() / 20][(this->getX() + 39) / 20] != '0'))
    {
        if (map[(this->getY() + 5) / 20][(this->getX() + 39) / 20] == '#')
        {
            map[(this->getY() + 5) / 20][(this->getX() + 39) / 20] = '1';
            return true;
        }
    }
    if (sx && (map[this->getY() / 20][(this->getX() / 20) - 1] != '$' && map[this->getY() / 20][(this->getX() / 20) - 1] != 'H' 
        && map[this->getY() / 20][(this->getX() / 20) - 1] != '0'))
    {
        if (map[(this->getY() + 5) / 20][(this->getX() / 20) - 1] == '#')
        {
            map[(this->getY() + 5) / 20][(this->getX() / 20) - 1] = '1';
            return true;
        }
    }
    return false;
}