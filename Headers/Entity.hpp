#include <allegro5/allegro5.h>
#include <string>
using namespace std;

#ifndef ENTITY_H
#define ENTITY_H
class Entity
{
private:
    int x;
    int y;
    int init_x;
    int init_y;
    int frame=0;
    bool mirrorX = false;
    bool mirrorY = false;
public:
    Entity(int, int);
    Entity();
    int getX();
    int getY();
    int getInitX();
    int getInitY();
    int getFrame();
    bool getMirrorX();
    bool getMirrorY();
    virtual string getEntity() = 0;
    void setX(int);
    void setY(int);
    void setFrame(int);
    void setMirrorX(bool);
    void setMirrorY(bool);
};
#endif