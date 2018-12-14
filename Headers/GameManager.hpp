#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Player.hpp"
#include "Enemy.hpp"
#include "GraphicManager.hpp"
#include <vector>
using namespace std;
class GameManager
{
private:
    Player player;
    vector<Enemy> enemies;
    GraphicManager graphic;
    int points = 0;
public:
    GameManager(Player p, vector<Enemy> enemies, GraphicManager graphic);
    ~GameManager();
};
#endif