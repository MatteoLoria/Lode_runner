#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Player.hpp"
#include "Enemy.hpp"
#include "GraphicManager.hpp"
#include "AStar.hpp"
#include "HoleManager.hpp"
#include "SoundManager.hpp"
#include <list>
#include <vector>
using namespace std;
using namespace AStar;
class GameManager
{
private:
    Player player;             //giocatore
    vector<Enemy> enemies;     //vettore di nemici
    list<HoleManager> holes;     //se il dig si può fare la buca da distruggere e ricreare viene aggiunta qui dentro
    Generator pathFinder;      //Astar
    char map[16][28];
    void loadMap(string path);  //mappa da leggere dal file di testo
    void createEntities(const int&); //spawn dei nemici in base al livello
    void restart();
    bool keys[6] = {false,false,false,false,false,false};//vari input
    bool avaibleSpot(const int& x, const int& y);   //controlla se la pos(x,y) è già occupata da un nemico
    int coins = 0;  //monete presente nella mappa
public:
    GameManager();
    int run(const int&, ALLEGRO_DISPLAY *, SoundManager&, GraphicManager&); //gestisce il gioco(input, ecc.)
};
#endif