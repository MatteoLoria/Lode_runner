#include "Entity.hpp"
#include "Quadruple.hpp"
#include "Player.hpp"
#include <list>
using namespace std;
#ifndef ENEMY_H
#define ENEMY_H
class Enemy : public Entity
{
  private:
    ALLEGRO_BITMAP *sprite[12];
    int prevX = 0;
    int prevY = 0;
    double fallen = 0;
    bool hat = false;
    void releaseGold(char[16][28]);
    bool isInHole(list<Quadruple>, char[][28], bool);
    void setRedHat(bool hat);
    bool isRedHat();
  public:
    Enemy();
    Enemy(int, int, string[12]);
    ~Enemy();
    string getEntity();
    void update(char[16][28], list<Quadruple>, Player &, int &, int &);
    double getFallen();
    void setFallen(double);
};
#endif