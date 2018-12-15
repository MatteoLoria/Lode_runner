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
    char map[16][29]; 
    int points = 0;
    void loadMap(string path);
    bool keys[4] = {false,false,false,false};
public:
    GameManager(Player p, vector<Enemy> enemies, GraphicManager graphic, char [][29]);
    void run(int, ALLEGRO_DISPLAY *);
    ~GameManager();
};
#endif