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
void SoundManager::playDie()
{
    al_play_sample(die, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}
void SoundManager::playWin()
{
    al_play_sample(win, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}
void SoundManager::playMenu()
{
    al_play_sample(menu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &idMenu);
}
void SoundManager::stopMenu()
{
    al_stop_sample(&idMenu);
}
void SoundManager::playCoin()
{
    al_play_sample(coin, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}
void SoundManager::playBackground()
{
    al_play_sample(background, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &idBackground);
}
void SoundManager::stopBackground()
{
    al_stop_sample(&idBackground);
}
void SoundManager::playDig()
{
    al_play_sample(this->dig, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}
void SoundManager::playClick()
{
    al_play_sample(clickMenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &idClic);
}
void SoundManager::stopClick()
{
    al_stop_sample(&idClic);
}
SoundManager::~SoundManager() {}