#include "../Headers/Entity.hpp"
#include <iostream>
using namespace std;
Entity::Entity() {}
Entity::Entity(int x, int y) : init_x(x), init_y(y), x(x), y(y) {}
int Entity::getFrame() { return frame; }
int Entity::getInitX() { return init_x; }
int Entity::getInitY() { return init_y; }
int Entity::getX() { return x; }
int Entity::getY() { return y; }
bool Entity::getMirrorX() { return mirrorX; }
bool Entity::getMirrorY() { return mirrorY; }
bool Entity::getMirrorRope() { return mirrorRope; }
bool Entity::getFall() { return isFalling; }
void Entity::setMirrorX(bool mirrorX) { this->mirrorX = mirrorX; }
void Entity::setMirrorY(bool mirrorY) { this->mirrorY = mirrorY; }
void Entity::setMirrorRope(bool mirrorRope) { this->mirrorRope = mirrorRope; }
void Entity::setFall(bool isFalling) { this->isFalling = isFalling; }
void Entity::setX(int x) { this->x = x; }
void Entity::setY(int y) { this->y = y; }
void Entity::setFrame(int frame) { this->frame = frame; }

void Entity::moveRight(char map[16][28])
{
    if ((map[(getY() - 18) / 20][(getX() / 20) + 1] != '#' && map[getY() / 20][(getX() / 20) + 1] != '#') //controllo blocchi
        && (map[(getY() - 18) / 20][(getX() / 20) + 1] != '@' && map[getY() / 20][(getX() / 20) + 1] != '@'))
    { //TODO: da testare
        setX(getX() + 5);
        if (map[(getY() - 18) / 20][getX() / 20] == '-' && map[((getY()) / 20)][(getX() / 20)] == '-') //aggrappati
            if (getMirrorRope())
                setFrame(5);
            else
                setFrame((getFrame() % 3) + 5);
        else if (getMirrorX())
            setFrame(0);
        else
            setFrame((getFrame() + 1) % 3);
        if (map[(getY() - 18) / 20][getX() / 20] == '-' && map[((getY()) / 20)][(getX() / 20)] == ' ' && map[((getY() - 5) / 20)][(getX() / 20)] == ' ') //troppo lontano dalla corda. Cadi
        {
            setFrame(4);
            setFall(true);
        }
        if (map[(getY() - 18) / 20][getX() / 20] == '-' && map[((getY()) / 20)][(getX() / 20)] == ' ' && map[((getY() - 5) / 20)][(getX() / 20)] == '-') //sei vicino alla corda. Aggrappati
            setY(getY() - 5);
        setMirrorX(false);
        setMirrorRope(false);
    }
    if ((map[(getY() + 5) / 20][(getX() / 20) + 1] == ' ' || map[(getY() + 5) / 20][((getX() + 10) / 20)] == ' ') && map[(getY() - 18) / 20][(getX() / 20) + 1] != '-' && map[(getY() - 18) / 20][(getX() / 20) + 1] != 'S' && map[(getY() - 18) / 20][(getX() / 20) + 1] != 'H' && map[(getY() + 5) / 20][(getX() / 20)] != 'H' && map[(getY() + 5) / 20][(getX() / 20)] != '#' && map[(getY() + 5) / 20][(getX() / 20)] != '@')
    {
        setFrame(4);
        setFall(true);
    }
    if ((map[(getY() + 5) / 20][getX() / 20] == '-' || map[(getY() + 10) / 20][getX() / 20] == '-' || map[(getY() + 15) / 20][getX() / 20] == '-') && map[getY() / 20][getX() / 20] != 'H')
    {
        setFrame(4);
        setFall(true);
    }
}

void Entity::moveLeft(char map[16][28])
{
    if (map[(getY() - 18) / 20][(getX() - 1) / 20] != '#' && map[getY() / 20][(getX() - 1) / 20] != '#')
    { //controllo blocchi
        setX(getX() - 5);
        if (map[(getY() - 18) / 20][(getX() / 20) + 1] == '-' && map[getY() / 20][(getX() / 20) + 1] == '-')
            if (getMirrorRope())
                setFrame((getFrame() % 3) + 5);
            else
                setFrame(5);
        else if (getMirrorX())
            setFrame((getFrame() + 1) % 3);
        else
            setFrame(0);
        if (map[(getY() - 18) / 20][(getX() / 20)] == '-' && map[((getY()) / 20)][(getX() / 20)] == ' ' && map[((getY() - 5) / 20)][(getX() / 20)] == ' ' && map[getY() / 20][getX() / 20] != 'H')
        {
            setFrame(4);
            setFall(true);
        }
        if (map[(getY() - 18) / 20][getX() / 20] == '-' && map[((getY()) / 20)][(getX() / 20)] == ' ' && map[((getY() - 5) / 20)][(getX() / 20)] == '-')
            setY(getY() - 5);
        setMirrorX(true);
        setMirrorRope(true);
    }
    if (map[(getY() + 5) / 20][(getX() + 18) / 20] == ' ' && map[(getY() - 18) / 20][(getX() - 1) / 20] != '-' && map[(getY() - 18) / 20][(getX() - 1) / 20] != 'H' && map[(getY()) / 20][(getX() / 20)] != 'H' && map[(getY() + 5) / 20][(getX() / 20)] != '#' && map[(getY() + 5) / 20][(getX() / 20)] != '@')
    {
        setFrame(4);
        setFall(true);
    }
    if ((map[(getY() + 5) / 20][(getX() / 20) + 1] == '-' || map[(getY() + 10) / 20][(getX() / 20) + 1] == '-' || map[(getY() + 15) / 20][(getX() / 20) + 1] == '-') && map[getY() / 20][getX() / 20] != 'H')
    {
        setFrame(4);
        setFall(true);
    }
}

void Entity::moveUp(char map[16][28], bool lastIsLeft)
{
    if (lastIsLeft)
    {
        if (map[getY() / 20][(getX() + 10) / 20] == 'H') //moving from right and the stair is at left
        {
            setX(((getX() + 10) / 20) * 20);
            setY(getY() - 5);
            setFrame(3);
            if (getMirrorY())
                setMirrorY(false);
            else
                setMirrorY(true);
        }
        else if (map[getY() / 20][(getX() + 5) / 20] == 'H')
        { //moving from right and the stair is at right
            setX(((getX() + 5) / 20) * 20);
            setY(getY() - 5);
            setFrame(3);
            if (getMirrorY())
                setMirrorY(false);
            else
                setMirrorY(true);
        }
    }
    else
    {
        if (map[getY() / 20][(getX() + 10) / 20] == 'H') //moving from left and the stair is at right
        {
            setX(((getX() + 10) / 20) * 20);
            setY(getY() - 5);
            setFrame(3);
            if (getMirrorY())
                setMirrorY(false);
            else
                setMirrorY(true);
        }
        else if (map[getY() / 20][(getX() + 15) / 20] == 'H')
        { //moving from left and the stair is at left
            setX(((getX() + 15) / 20) * 20);
            setY(getY() - 5);
            setFrame(3);
            if (getMirrorY())
                setMirrorY(false);
            else
                setMirrorY(true);
        }
    }
}

void Entity::moveDown(char map[16][28])
{
    if (map[(getY() / 20) + 1][(getX() + 10) / 20] == 'H' || map[(getY() / 20)][(getX() + 10) / 20] == 'H')
    { //moving from right and stair is at left
        setX(((getX() + 10) / 20) * 20);
        if (map[((getY() + 5) / 20)][((getX()) / 20)] != '#')
        {
            setY(getY() + 5);
            setFrame(3);
            if (getMirrorY())
                setMirrorY(false);
            else
                setMirrorY(true);
        }
    }
    if (map[(getY() / 20) + 1][getX() / 20] == ' ' && map[(getY() / 20) + 1][getX() / 20] != 'H' && map[(getY() / 20) + 1][getX() / 20] != '#' && map[(getY() / 20) + 1][(getX() + 18) / 20] != '#')
    {
        setFrame(4);
        setFall(true);
    }
}
