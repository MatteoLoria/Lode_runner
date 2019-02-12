#include "../Headers/SoundManager.hpp"
#include <iostream>
using namespace std;
SoundManager::SoundManager()
{
    al_reserve_samples(10);
    this->fall = al_load_sample("../Assets/Sounds/fall.wav");
    if (!fall)
        exit(1);
    this->die = al_load_sample("../Assets/Sounds/dead.wav");
    this->win = al_load_sample("../Assets/Sounds/goldFinish1.mp3");
    //menu
    this->coin = al_load_sample("../Assets/Sounds/getGold.wav");
    //background
    this->dig = al_load_sample("../Assets/Sounds/dig.wav");
    //clickMenu
}

void SoundManager::playFall()
{
    if (!isPlaying)
    {
        isPlaying = true;
        al_play_sample(this->fall, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &idFall);
    }
}
void SoundManager::stopFall()
{
    if (isPlaying)
    {
        al_stop_sample(&idFall);
        isPlaying = false;
    }
}
SoundManager::~SoundManager() {}