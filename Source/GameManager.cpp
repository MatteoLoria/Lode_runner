#include "../Headers/GameManager.hpp"

GameManager::GameManager(Player p, vector<Enemy> enemies, GraphicManager graphic){
    this->player = p;
    for(auto i : enemies){
        this->enemies.push_back(i);
    }
    this->graphic = graphic;
    this->points = 0;
}