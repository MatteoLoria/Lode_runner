#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Player.hpp"
#include "Enemy.hpp"
#include "GraphicManager.hpp"
#include <list>
#include <vector>
#include "Quadruple.hpp"
using namespace std;
class GameManager
{
private:
    Player player;
    vector<Enemy> enemies;
    GraphicManager graphic;
    list<Quadruple> holes;
    char map[16][28]; 
    int points = 0;
    void loadMap(string path);
    bool keys[6] = {false,false,false,false,false,false};
public:
    GameManager();
    GameManager(Player p, vector<Enemy> enemies, GraphicManager graphic);
    void run(int, ALLEGRO_DISPLAY *);
};
#endif