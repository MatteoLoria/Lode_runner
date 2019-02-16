#include "../Headers/SoundManager.hpp"
#include <iostream>
using namespace std;
/*
  Semplice classe che fa wrapper per i metodi di allegro.
*/
SoundManager::SoundManager()
{
    al_reserve_samples(10);
    this->fall = al_load_sample("../Assets/Sounds/fall.wav");
    this->stairs = al_load_sample("../Assets/Sounds/stairs.wav");
    this->die = al_load_sample("../Assets/Sounds/dead.wav");
    if (!die)
        exit(2);
    this->gameover = al_load_sample("../Assets/Sounds/gameover.wav");
    this->win = al_load_sample("../Assets/Sounds/pass.ogg");
    this->menu = al_load_sample("../Assets/Sounds/menu.wav");
    this->coin = al_load_sample("../Assets/Sounds/getGold.wav");
    this->background = al_load_sample("../Assets/Sounds/background.wav");
    this->dig = al_load_sample("../Assets/Sounds/dig.wav");
    this->clickMenu = al_load_sample("../Assets/Sounds/click.wav");
}

void SoundManager::playGameover()
{
    al_play_sample(this->gameover, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
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
void SoundManager::playStair()
{

    al_play_sample(stairs, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
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
    al_play_sample(menu, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &idMenu);
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
    al_play_sample(background, 0.3, 0.0, 1.3, ALLEGRO_PLAYMODE_LOOP, &idBackground);
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
    al_play_sample(clickMenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}
SoundManager::~SoundManager()
{
    al_destroy_sample(fall);
    al_destroy_sample(die);
    al_destroy_sample(stairs);
    al_destroy_sample(win);
    al_destroy_sample(menu);
    al_destroy_sample(coin);
    al_destroy_sample(background);
    al_destroy_sample(dig);
    al_destroy_sample(clickMenu);
    al_destroy_sample(gameover);
}