#include "Entity.hpp"
#include "HoleManager.hpp"
#include "Player.hpp"
#include <list>
using namespace std;
#ifndef ENEMY_H
#define ENEMY_H
class Enemy : public Entity
{
  private:
    double fallen = 0;                       //serve per capire a che punto della caduta in una buca è
    bool hat = false;                        //se è true ha raccolto una moneta
  public:
    Enemy();
    Enemy(const int&, const int&);
    string getEntity();               //override, restituisce il nome dell'entità di cui stiamo parlando
    void update(char[16][28], const list<HoleManager>&, Player&, const int&, const int&); //fa muovere il nemico
    double getFallen();                  
    void setFallen(const double&);
    bool isInHole(const list<HoleManager>&, char[][28], const bool&);   //dice se il nemico è nella buca, il bool serve per capire se si vuole sapere se la testa o il piede è nella buca
    void setRedHat(const bool&);
    bool isRedHat();
};
#endif