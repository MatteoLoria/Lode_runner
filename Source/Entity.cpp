#include "../Headers/Entity.hpp"
#include <iostream>
using namespace std;

Entity::Entity() {}
Entity::Entity(const int &x, const int &y) : init_x(x), init_y(y), x(x), y(y) {}
int Entity::getFrame() { return frame; }
int Entity::getInitX() { return init_x; }
int Entity::getInitY() { return init_y; }
int Entity::getX() { return x; }
int Entity::getY() { return y; }
bool Entity::getMirrorX() { return mirrorX; }
bool Entity::getMirrorY() { return mirrorY; }
bool Entity::getMirrorRope() { return mirrorRope; }
bool Entity::getFall() { return isFalling; }
void Entity::setMirrorX(const bool &mirrorX) { this->mirrorX = mirrorX; }
void Entity::setMirrorY(const bool &mirrorY) { this->mirrorY = mirrorY; }
void Entity::setMirrorRope(const bool &mirrorRope) { this->mirrorRope = mirrorRope; }
void Entity::setFall(const bool &isFalling) { this->isFalling = isFalling; }
void Entity::setX(const int &x) { this->x = x; }
void Entity::setY(const int &y) { this->y = y; }
void Entity::setInitX(const int &x)
{
    this->x = x;
    this->init_x = x;
}
void Entity::setInitY(const int &y)
{
    this->y = y;
    this->init_y = y;
}
void Entity::setFrame(const int &frame) { this->frame = frame; }
void Entity::moveRight(char map[16][28], const bool &red) //il bool riguarda il nemico e se quest'utlimo ha il cappello rosso, cioè ha raccolto una moneta
{
    if ((map[(getY() - 18) / 20][(getX() / 20) + 1] != '#' && map[getY() / 20][(getX() / 20) + 1] != '#') //controllo limite blocchi
        && (map[(getY() - 18) / 20][(getX() / 20) + 1] != '@' && map[getY() / 20][(getX() / 20) + 1] != '@'))
    {
        setX(getX() + 5);
        if (map[(getY() - 18) / 20][getX() / 20] == '-' && map[((getY()) / 20)][(getX() / 20)] == '-') //è su una corda, quindi si aggrappa
            if (getMirrorRope())
                setFrame(5);
            else
                setFrame((getFrame() % 3) + 5);
        else if (getMirrorX()) //si stava muovendo verso sinistra, quindi resettiamo il frame
        {
            red ? setFrame(8) : setFrame(0); //se è un nemico va gestito il cappello rosso(ha una moneta)
        }
        else
        { //gestione delle animazioni
            red ? setFrame(((getFrame() + 1) % 11)) : setFrame((getFrame() + 1) % 3);
            if (red && getFrame() < 8)
            {
                frame += 8;
            }
        }
        if (map[(getY() - 18) / 20][getX() / 20] == '-' && map[((getY()) / 20)][(getX() / 20)] == ' ' && map[((getY() - 5) / 20)][(getX() / 20)] == ' ') //se si sta avvicinando ad una corda, ma non è all'altezza giusta cade
        {
            red ? setFrame(11) : setFrame(4);
            setFall(true);
        }
        if (map[(getY() - 18) / 20][getX() / 20] == '-' && map[((getY()) / 20)][(getX() / 20)] == ' ' && map[((getY() - 5) / 20)][(getX() / 20)] == '-') //è all'altezza giusta, si aggrappa
            setY(getY() - 5);
        setMirrorX(false);
        setMirrorRope(false);
    }
    if ((map[(getY() + 5) / 20][(getX() / 20) + 1] == ' ' || map[(getY() + 5) / 20][((getX() + 10) / 20)] == ' ' || map[(getY() + 5) / 20][(getX() + 10) / 20] == 'S') && map[(getY() - 18) / 20][(getX() / 20) + 1] != '-' && map[(getY() - 18) / 20][(getX() / 20)] != '-' && map[(getY() + 5) / 20][(getX() / 20)] != 'H' && map[(getY() + 5) / 20][(getX() / 20)] != '#' && map[(getY() + 5) / 20][(getX() / 20)] != '@' && map[(getY() + 5) / 20][(getX() / 20)] != '}')
    { //caduta
        red ? setFrame(11) : setFrame(4);
        setFall(true);
    }
    if ((map[(getY() + 5) / 20][getX() / 20] == '-' || map[(getY() + 10) / 20][getX() / 20] == '-' || map[(getY() + 15) / 20][getX() / 20] == '-') && map[getY() / 20][getX() / 20] != 'H' && map[(getY() + 5) / 20][(getX() / 20)] != '}')
    { //caduta in presenza di una corda
        red ? setFrame(11) : setFrame(4);
        setFall(true);
    }
}

void Entity::moveLeft(char map[16][28], const bool &red) //stessa logica del moveRight, uniche differenze nelle operazioni con i pixel
{
    if (map[(getY() - 18) / 20][(getX() - 1) / 20] != '#' && map[getY() / 20][(getX() - 1) / 20] != '#' && map[(getY() - 18) / 20][(getX() - 1) / 20] != '@' && map[getY() / 20][(getX() - 1) / 20] != '@')
    {
        setX(getX() - 5);
        if (map[(getY() - 18) / 20][(getX() / 20) + 1] == '-' && map[getY() / 20][(getX() / 20) + 1] == '-')
            if (getMirrorRope())
                setFrame((getFrame() % 3) + 5);
            else
                setFrame(5);
        else if (getMirrorX())
        {
            red ? setFrame(((getFrame() + 1) % 11)) : setFrame((getFrame() + 1) % 3);
            if (red && getFrame() < 8)
            {
                frame = frame % 3;
                frame += 8;
            }
        }
        else
            red ? setFrame(8) : setFrame(0);
        if (map[(getY() - 18) / 20][(getX() / 20)] == '-' && map[((getY()) / 20)][(getX() / 20)] == ' ' && map[((getY() - 5) / 20)][(getX() / 20)] == ' ' && map[getY() / 20][(getX() + 18) / 20] != 'H')
        {
            red ? setFrame(11) : setFrame(4);
            setFall(true);
        }
        if (map[(getY() - 18) / 20][getX() / 20] == '-' && map[((getY()) / 20)][(getX() / 20)] == ' ' && map[((getY() - 5) / 20)][(getX() / 20)] == '-')
        {
            setY(getY() - 5);
        }
        setMirrorX(true);
        setMirrorRope(true);
    }
    if ((map[(getY() + 5) / 20][(getX() + 18) / 20] == ' ' || map[(getY() + 5) / 20][(getX() + 18) / 20] == '$' || map[(getY() + 5) / 20][(getX() + 18) / 20] == 'S') // aggiunto S
        && map[(getY() - 18) / 20][(getX() - 1) / 20] != '-' && map[(getY() - 18) / 20][(getX()) / 20] != '-' && map[(getY() + 5) / 20][(getX() / 20)] != 'H' && map[(getY() + 5) / 20][(getX() / 20)] != '#' && map[(getY() + 5) / 20][(getX() / 20)] != '@' && map[(getY() + 5) / 20][(getX() / 20)] != '}')
    {
        red ? setFrame(11) : setFrame(4);
        setFall(true);
    }
    if ((map[(getY() + 5) / 20][(getX() / 20) + 1] == '-' || map[(getY() + 10) / 20][(getX() / 20) + 1] == '-' || map[(getY() + 15) / 20][(getX() / 20) + 1] == '-') && map[getY() / 20][getX() / 20] != 'H')
    {
        red ? setFrame(11) : setFrame(4);
        setFall(true);
    }
}

void Entity::moveUp(char map[16][28], const bool &lastIsLeft, const bool &red)
{
    if (lastIsLeft) //va verso sinistra e cerca di salire
    {
        if (map[getY() / 20][(getX() + 10) / 20] == 'H') //la scala è alla sua sinistra
        {
            setX(((getX() + 10) / 20) * 20);
            setY(getY() - 5);
            setFrame(3);
            if (getMirrorY())
                setMirrorY(false);
            else
                setMirrorY(true);
        }
        else if (map[getY() / 20][(getX() + 5) / 20] == 'H') //la scala è alla sua destra
        {
            setX(((getX() + 5) / 20) * 20);
            setY(getY() - 5);
            setFrame(3);
            if (getMirrorY())
                setMirrorY(false);
            else
                setMirrorY(true);
        }
    }
    else //va verso destra e cerca di salire
    {
        if (map[getY() / 20][(getX() + 10) / 20] == 'H') //la scala è a destra
        {
            setX(((getX() + 10) / 20) * 20);
            setY(getY() - 5);
            setFrame(3);
            if (getMirrorY())
                setMirrorY(false);
            else
                setMirrorY(true);
        }
        else if (map[getY() / 20][(getX() + 15) / 20] == 'H') //la scala è a sinistra
        {
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

void Entity::moveDown(char map[16][28], const bool &red)
{
    if (map[(getY() / 20) + 1][(getX() + 10) / 20] == 'H' || map[(getY() / 20)][(getX() + 10) / 20] == 'H')
    { //scende dalla scala
        setX(((getX() + 10) / 20) * 20);
        if (map[((getY() + 5) / 20)][((getX()) / 20)] != '#' && map[((getY() + 5) / 20)][((getX()) / 20)] != '@')
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
    { //si butta(ad esempio da una corda)
        setFrame(4);
        setFall(true);
    }
}
