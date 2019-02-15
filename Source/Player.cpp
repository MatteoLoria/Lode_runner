#include "../Headers/Player.hpp"
#include <iostream>
using namespace std;

string Player::getEntity() { return "Player"; }
int Player::getPoints(){return points;}
int Player::getLives() { return lives; }
void Player::decreaseLives() { lives--; }
void Player::setLives(const int& lives) { this->lives = lives; }
void Player::increasePoints() { points++; }
void Player::setPoints(const int& points) {this->points = points;}

Player::Player() : Entity() {}

Player::Player(const int& x, const int& y, string sprite[10]) : Entity(x, y) {}

bool Player::dig(char map[16][28], const bool& sx)
{
    if (!sx && (map[this->getY() / 20][(this->getX() + 39) / 20] != '$' && map[this->getY() / 20][(this->getX() + 39) / 20] != 'H' 
        && map[this->getY() / 20][(this->getX() + 39) / 20] != '#' && map[this->getY() / 20][(this->getX() + 39) / 20] != '@'))
    { //verifica se si può fare a destra
        if (map[(this->getY() + 5) / 20][(this->getX() + 39) / 20] == '#')
        {
            map[(this->getY() + 5) / 20][(this->getX() + 39) / 20] = '1';//codifica per la mappa
            return true;
        }
    }
    if (sx && (map[this->getY() / 20][(this->getX() / 20) - 1] != '$' && map[this->getY() / 20][(this->getX() / 20) - 1] != 'H' 
        && map[this->getY() / 20][(this->getX() / 20) - 1] != '#' && map[this->getY() / 20][(this->getX() / 20) - 1] != '@'))
    { //verifica se si può fare a sinistra
        if (map[(this->getY() + 5) / 20][(this->getX() / 20) - 1] == '#')
        {
            map[(this->getY() + 5) / 20][(this->getX() / 20) - 1] = '1';//codifica per la mappa
            return true;
        }
    }
    return false;
}