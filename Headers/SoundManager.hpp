#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#ifndef SOUND_H
#define SOUND_H
class SoundManager
{
  private:
    ALLEGRO_SAMPLE *fall;
    ALLEGRO_SAMPLE_ID idFall;
    ALLEGRO_SAMPLE *die;
    ALLEGRO_SAMPLE *stairs;
    ALLEGRO_SAMPLE *win;
    ALLEGRO_SAMPLE *menu;
    ALLEGRO_SAMPLE_ID idMenu;
    ALLEGRO_SAMPLE *coin;
    ALLEGRO_SAMPLE *background;
    ALLEGRO_SAMPLE_ID idBackground;
    ALLEGRO_SAMPLE *dig;
    ALLEGRO_SAMPLE *clickMenu;
    ALLEGRO_SAMPLE_ID idClic;
    bool isPlaying;

  public:
    SoundManager();
    ~SoundManager();
    void playFall();
    void playStair();
    void playDie();
    void playWin();
    void playMenu();
    void playCoin();
    void playBackground();
    void playDig();
    void playClick();
    void stopFall();
    void stopMenu();
    void stopBackground();
    void stopClick();
};
#endif