#include <allegro5/allegro5.h>
#include <string>
using namespace std;

#ifndef ENTITY_H
#define ENTITY_H
class Entity
{
private:
    int x;                    //cordinate per il movimento
    int y;
    int init_x;               //cordinate spawn
    int init_y;
    int frame = 0;            //frame da stampare
    bool mirrorX = false;     //se è false si sta muovendo verso destra, serve per fare la stampa specchiata nel graphic manager
    bool mirrorY = false;     //serve per specchiare nella stampa
    bool mirrorRope = false;  //ragionamento analago di mirrorX, ma sulle corde
    bool isFalling = false;   //dice se il player sta cadendo

public:
    Entity(const int&, const int&);
    Entity();
    int getX();
    int getY();
    int getInitX();
    int getInitY();
    int getFrame();
    bool getMirrorX();
    bool getMirrorY();
    bool getMirrorRope();
    bool getFall();
    virtual string getEntity() = 0;
    void setX(const int&);
    void setY(const int&);
    void setInitX(const int&);
    void setInitY(const int&);
    void setFrame(const int&);
    void setMirrorX(const bool&);
    void setMirrorY(const bool&);
    void setMirrorRope(const bool&);
    void setFall(const bool&);
    void moveRight(char[][28], const bool&);                     //metodi per il movimento validi sia per il player che per enemy
    void moveLeft(char[][28], const bool&);
    void moveUp(char[][28], const bool&, const bool&);
    void moveDown(char[][28], const bool&);
};
#endif