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
    int prevX = 0;
    int prevY = 0;
    double fallen = 0;
    bool hat = false;
    void releaseGold(char[16][28]);
    void setRedHat(bool hat);
    bool isRedHat();
  public:
    Enemy();
    Enemy(int, int);
    string getEntity();
    void update(char[16][28], list<Quadruple>, Player &, int &, int &);
    double getFallen();
    void setFallen(double);
    bool isInHole(list<Quadruple>, char[][28], bool);//l'ho messa public per usarla nel game manager
};
#endif