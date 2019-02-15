#include "../Headers/SoundManager.hpp"
#include <iostream>
using namespace std;
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
/*void SoundManager::stopClick()
{
    al_stop_sample(&idClic);
}*/
SoundManager::~SoundManager()
{
    cout<<"1";
    
    if (fall!=0)
    {
        al_destroy_sample(fall);
        fall = 0;
    }
    if (die!=0)
    {
        al_destroy_sample(die);
        die = 0;
    }
    if (stairs!=0)
    {
        al_destroy_sample(stairs);
        stairs = 0;
    }
    if (win!=0)
    {
        al_destroy_sample(win);
        win = 0;
    }
    if (menu!=0)
    {
        al_destroy_sample(menu);
        menu = 0;
    }
    if (coin!=0)
    {
        al_destroy_sample(coin);
        coin = 0;
    }
    if (background!=0)
    {
        al_destroy_sample(background);
        background = 0;
    }
    if (dig!=0)
    {
        al_destroy_sample(dig);
        dig = 0;
    }
    if (clickMenu!=0)
    {
        al_destroy_sample(clickMenu);
        clickMenu = 0;
    }
    if (gameover!=0)
    {
        al_destroy_sample(gameover);
        gameover = 0;
    }
}