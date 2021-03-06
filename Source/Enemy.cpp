/*
 @authors Matteo Notaro               &  Matteo Loria
 @github  https://github.com/MattNot     https://github.com/MatteoLoria

 19/02/2019
*/

#include "../Headers/Enemy.hpp"

string Enemy::getEntity() { return "Enemy"; }
void Enemy::setRedHat(const bool &hat) { this->hat = hat; }
bool Enemy::isRedHat() { return hat; }
double Enemy::getFallen() { return fallen; }
void Enemy::setFallen(const double &fallen) { this->fallen = fallen; }

Enemy::Enemy() : Entity() {}
Enemy::Enemy(const int &x, const int &y) : Entity(x, y) {}

bool Enemy::isInHole(const list<HoleManager> &holes, char map[16][28], const bool &head)
{
    for (auto i : holes)
    {
        if (head)
        {
            if ((this->getY() - 18) / 20 == i.first && this->getX() / 20 == i.second) //entra qui dentro se la testa è nella buca
            {
                if (isRedHat()) //rilascia la moneta
                {
                    map[(this->getY() / 20) - 1][this->getX() / 20] = '$';
                    this->setRedHat(false);
                    this->setFrame(4);
                }
                if (map[i.first][i.second] == '#') //muore perchè si è riformato il blocco
                {
                    //respawn
                    fallen = 0;
                    this->setFall(false);
                    this->setX(this->getInitX());
                    this->setY(this->getInitY());
                    return true;
                }
                return true;
            }
        }
        else
        {
            if ((this->getY()) / 20 == i.first && this->getX() / 20 == i.second) //entra se i piedi sono nella buca
            {
                if (isRedHat()) //rilascia la moneta
                {
                    map[(this->getY() / 20) - 1][this->getX() / 20] = '$';
                    this->setRedHat(false);
                    this->setFrame(4);
                }
                if (map[i.first][i.second] == '#')
                {
                    //respawn
                    fallen = 0;
                    this->setFall(false);
                    this->setX(this->getInitX());
                    this->setY(this->getInitY());
                    return true;
                }
                map[getY() / 20][getX() / 20] = '}'; //cosi gli altri enemy o il player ci camminano sopra
                return true;
            }
        }
    }
    return false;
}
void Enemy::update(char map[16][28], const list<HoleManager> &holes, Player &p, const int &nextY, const int &nextX)
{
    bool headInHole = isInHole(holes, map, true);
    bool footInHole = isInHole(holes, map, false);
    if (this->getFall() && !headInHole) //gestisce la caduta(serve?)
    {
        this->setY(this->getY() + 5);
        if (map[((this->getY() + 5) / 20)][(this->getX() / 20)] == '#' || map[((this->getY() + 5) / 20)][(this->getX() / 20)] == 'H' || map[((this->getY() + 5) / 20)][(this->getX() / 20)] == '@')
        {
            this->setFall(false);
            if (this->isRedHat())
            {
                setRedHat(false);
                if (map[(this->getY() + 5) / 20][(this->getX() / 20) + 1] == ' ')
                    map[(this->getY() + 5) / 20][(this->getX() / 20) + 1] == '$';
                else
                    map[(this->getY() + 5) / 20][(this->getX() / 20) - 1] == '$';
            }
        }
        if (map[((this->getY() - 18) / 20)][(this->getX() / 20)] == '-' && map[((this->getY()) / 20)][(this->getX() / 20)] == '-')
        {
            this->setFall(false);
            this->setFrame(5);
        }
        if (map[((this->getY() - 18) / 20)][(this->getX() / 20)] == '-' && map[((this->getY() + 5) / 20)][(this->getX() / 20)] != '#')
        {
            this->setFall(true);
            this->setFrame(4);
        }
    }
    else
    {
        bool left = false;              // booleana che serve a capire da che lato sta approcciando una scala
        if (!footInHole && !headInHole) //se non è in una buca
        {
            if (this->getX() / 20 < nextX) //va a destra
            {
                this->moveRight(map, isRedHat());
                left = false;
            }
            if ((this->getX() + 18) / 20 > nextX) //va a sinistra
            {
                this->moveLeft(map, isRedHat());
                left = true;
            }
            if (this->getY() < (nextY * 20) + 18) //va sotto
                this->moveDown(map, isRedHat());
            if (this->getY() / 20 > nextY) //va sopra
                this->moveUp(map, left, isRedHat());
        }
    }
    if (map[getY() / 20][(getX()) / 20] == '$' && !isRedHat()) //raccoglie la moneta
    {
        setRedHat(true);
        map[getY() / 20][getX() / 20] = ' ';
    }
}
