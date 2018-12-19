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
void Player::dig(char map[16][28], bool sx){
    if(!sx && (map[this->getY()/20][(this->getX()/20)+1] != '$' || map[this->getY()/20][(this->getX()/20)+1] != 'H' || map[this->getY()/20][(this->getX()/20)+1] != '0')){
        if(map[(this->getY()+5)/20][(this->getX()/20)+1] == '#'){
            map[(this->getY()+5)/20][(this->getX()/20)+1] = '1';
        }
    }
}
string Player::getEntity() {return "Player";}

int Player::getLives(){return lives;}
void Player::decreaseLives(){lives--;}
void Player::increaseLives(){lives++;}
