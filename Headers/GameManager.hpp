#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Player.hpp"
#include "Enemy.hpp"
#include "GraphicManager.hpp"
#include "AStar.hpp"
#include "Quadruple.hpp"
#include "SoundManager.hpp"
#include <list>
#include <vector>
using namespace std;
using namespace AStar;
class GameManager
{
private:
    Player player;
    vector<Enemy> enemies;
    GraphicManager graphic;
    list<Quadruple> holes;
    Generator pathFinder;
    char map[16][28];
    void loadMap(string path);
    void createEntities(const int&);
    void restart();
    bool keys[6] = {false,false,false,false,false,false};
    bool avaibleSpot(const int& x, const int& y);
    int coins = 0;
public:
    GameManager();
    GameManager(GraphicManager&);
    int run(const int&, ALLEGRO_DISPLAY *, SoundManager&);
};
#endif