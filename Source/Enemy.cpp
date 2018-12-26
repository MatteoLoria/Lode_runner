#include "../Headers/Enemy.hpp"
string Enemy::getEntity() { return "Enemy"; }

void Enemy::setRedHat(bool hat) { this->hat = hat; }

bool Enemy::isRedHat() { return hat; }

void Enemy::die()
{
    this->setX(this->getInitX());
    this->setY(this->getInitY());
}

Enemy::Enemy() : Entity()
{
    for (int i = 0; i < 12; ++i)
        sprite[i] = NULL;
}

Enemy::Enemy(int x, int y, string sprite[12]) : Entity(x, y)
{
    for (int i = 0; i < 12; ++i)
        this->sprite[i] = al_load_bitmap(sprite[i].c_str());
}

Enemy::~Enemy()
{
    for (int i = 0; i < 12; ++i)
        al_destroy_bitmap(sprite[i]);
}
bool Enemy::isInHole(list<Quadruple> holes)
{
    for (auto i : holes)
    {
        if (this->getY() == i.first && this->getX() == i.second)
            return true;
    }
}
void Enemy::update(char map[16][28], list<Quadruple> holes, Player &p)
{
    if (this->getFall())
    {
        this->setY(this->getY() + 5);
        if (map[((this->getY() + 5) / 20)][(this->getX() / 20)] == '#' || map[((this->getY() + 5) / 20)][(this->getX() / 20)] == 'H' || map[((this->getY() + 5) / 20)][(this->getX() / 20)] == '@')
            this->setFall(false);
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
    if (this->isInHole(holes) && isRedHat())
    {
        map[(this->getY() / 20) - 1][this->getX() / 20] = '$';
        this->setRedHat(false);
    }
    else
    {
        if (this->getY() == p.getY())
        {
            if (this->getX() != p.getX())
            {
                if (map[this->getY() / 20][this->getX() / 20] != 'H' || map[(this->getY() / 20) + 1][this->getX() / 20] == '#' || map[this->getY() / 20][this->getX() / 20] == '-' || map[(this->getY() / 20) + 1][this->getX() / 20] == '-')
                {
                    if (this->getX() < p.getX())
                    {
                        moveRight(map);
                    }
                    else
                    {
                        moveLeft(map);
                    }
                }
            }
        }
        else if (this->getY() < p.getY())
        {
            if (map[this->getY() / 20][this->getX() / 20] == 'H' || map[(this->getY() / 20) + 1][this->getX() / 20] == 'H' || map[this->getY() / 20][this->getX() / 20] == '-' || map[(getY() / 20) + 1][getX() / 20] == ' ')
            {
                moveDown(map);
            }
            else
            {
                moveRight(map);
            }
        }
        else if (this->getY() > p.getY())
        {
            if (map[this->getY() / 20][this->getX() / 20] == 'H' || map[(this->getY() / 20) + 1][this->getX() / 20] == 'H' || map[this->getY() / 20][this->getX() / 20] == '-' || map[(getY() / 20) + 1][getX() / 20] == ' ')
            {
                moveUp(map, this->getMirrorX());
            }
            else
            {
                moveLeft(map);
            }
        }
    }
}
