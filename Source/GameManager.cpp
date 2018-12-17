#include "../Headers/GameManager.hpp"
#include <iostream>
#include <fstream>
enum MYKEYS{
        KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

GameManager::GameManager(){}

GameManager::GameManager(Player p, vector<Enemy> enemies, GraphicManager graphic){
    this->player = p;
    for(auto i : enemies){
        this->enemies.push_back(i);
    }
    this->graphic = graphic;
    this->points = 0;
}

void GameManager::run(int level, ALLEGRO_DISPLAY * display){
    bool redraw=false;
    bool lastIsLeft = false;
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    ALLEGRO_TIMER * timer = al_create_timer(1.0/10);
    al_install_keyboard();
    al_register_event_source(queue,al_get_keyboard_event_source());
    al_register_event_source(queue,al_get_timer_event_source(timer));
    al_register_event_source(queue,al_get_display_event_source(display));
    if(level == 1){
        this->loadMap("../Assets/Maps/level1.txt");
    }else if (level == 2){
        this->loadMap("../Assets/Maps/level2.txt");
    }else{
        this->loadMap("../Assets/Maps/level3.txt");
    }
    al_start_timer(timer);
    bool close = false;
    while(!close){
        ALLEGRO_EVENT event;
        al_wait_for_event(queue,&event);
        if(event.type == ALLEGRO_EVENT_TIMER){
            //TODO: nemici (bellamerda)
            if(keys[KEY_RIGHT] && player.getX() < 540 && !player.getFall()){
                if(map[(player.getY()-18)/20][(player.getX()/20)+1] != '#' && map[player.getY()/20][(player.getX()/20)+1] != '#')//TODO: da testare
                {
                    player.setX(player.getX()+5);
                    if(map[(player.getY()-18)/20][player.getX()/20] == '-')
                        if(player.getMirrorRope())
                            player.setFrame(5);
                        else
                            player.setFrame((player.getFrame() % 3) + 5);
                    else
                        if(player.getMirrorX())
                            player.setFrame(0);
                        else
                            player.setFrame((player.getFrame() + 1) % 3);
                    player.setMirrorX(false);
                    player.setMirrorRope(false);
                }
                if(map[(player.getY()+5)/20][player.getX()/20] == ' ' && map[player.getY()/20][player.getX()/20] != '-'){
                    player.setFrame(4);
                    player.setFall(true);
                }
            }
            if(keys[KEY_LEFT] && player.getX() > 0 && !player.getFall()){
                if(map[(player.getY()-18)/20][(player.getX()-1)/20] != '#' && map[player.getY()/20][(player.getX()-1)/20] != '#')
                {
                    player.setX(player.getX()-5);
                    if(map[player.getY()/20][player.getX()/20] == '-')
                        if(player.getMirrorRope())
                            player.setFrame((player.getFrame() % 3) + 5);
                        else
                            player.setFrame(5);
                    else
                        if(player.getMirrorX())
                            player.setFrame((player.getFrame() + 1) % 3);
                        else
                            player.setFrame(0);
                    
                    player.setMirrorX(true);
                    player.setMirrorRope(true);
                }
                if(map[(player.getY()+5)/20][(player.getX()+18)/20] == ' ' && map[player.getY()/20][player.getX()/20] != '-'){
                    player.setFrame(4);
                    player.setFall(true);
                }
            }
            if(keys[KEY_UP] && !player.getFall()){
                //TODO: REFACTOR
                if(lastIsLeft){
                    if(map[player.getY()/20][(player.getX()+10)/20]=='H') //moving from right and the stair is at left
                    {
                        player.setX(((player.getX()+10)/20)*20);
                        player.setY(player.getY()-5);
                        player.setFrame(3);
                        if(player.getMirrorY())
                            player.setMirrorY(false);
                        else
                            player.setMirrorY(true);
                    }else if(map[player.getY()/20][(player.getX()+5)/20]=='H'){ //moving from right and the stair is at right
                        player.setX(((player.getX()+5)/20)*20);
                        player.setY(player.getY()-5);
                        player.setFrame(3);
                        if(player.getMirrorY())
                            player.setMirrorY(false);
                        else
                            player.setMirrorY(true);                    
                    }
                }else{
                    if(map[player.getY()/20][(player.getX()+10)/20]=='H') //moving from left and the stair is at right
                    {
                        player.setX(((player.getX()+10)/20)*20);
                        player.setY(player.getY()-5);
                        player.setFrame(3);
                        if(player.getMirrorY())
                            player.setMirrorY(false);
                        else
                            player.setMirrorY(true);
                    }else if(map[player.getY()/20][(player.getX()+15)/20]=='H'){ //moving from left and the stair is at left
                        player.setX(((player.getX()+15)/20)*20);
                        player.setY(player.getY()-5);
                        player.setFrame(3);
                        if(player.getMirrorY())
                            player.setMirrorY(false);
                        else
                            player.setMirrorY(true);   
                    }
                }
            }
            if(keys[KEY_DOWN]){
                if(map[(player.getY()/20)+1][(player.getX()+10)/20]== 'H'|| map[(player.getY()/20)][(player.getX()+10)/20]== 'H'){ // moving from right and stair is at left
                    player.setX(((player.getX()+10)/20)*20);
                    if(map[((player.getY()+5)/20)][(player.getX()/20)] != '#'){
                        player.setY(player.getY()+5);
                        player.setFrame(3);
                    if(player.getMirrorY())
                        player.setMirrorY(false);
                    else
                        player.setMirrorY(true);
                    }
                }
                if(map[(player.getY()/20)+1][player.getX()/20] == ' '){
                    player.setFrame(4);
                    player.setFall(true);
                }
            }
            redraw = true;
        }else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
         switch(event.keyboard.keycode) { 
            case ALLEGRO_KEY_UP:
               keys[KEY_UP] = true;
               break;

            case ALLEGRO_KEY_DOWN:
               keys[KEY_DOWN] = true;
               break;

            case ALLEGRO_KEY_LEFT: 
               keys[KEY_LEFT] = true;
               lastIsLeft = true;
               break;

            case ALLEGRO_KEY_RIGHT:
               keys[KEY_RIGHT] = true;
               lastIsLeft = false;
               break;

            case ALLEGRO_KEY_ESCAPE:
                close = true;
                break;
         }
      }else if(event.type == ALLEGRO_EVENT_KEY_UP) {
          player.setFrame(player.getFrame() == 3 ? 3:player.getFrame());
         switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               keys[KEY_UP] = false;
               break;

            case ALLEGRO_KEY_DOWN:
               keys[KEY_DOWN] = false;
               break;

            case ALLEGRO_KEY_LEFT: 
               keys[KEY_LEFT] = false;
               break;

            case ALLEGRO_KEY_RIGHT:
               keys[KEY_RIGHT] = false;
               break;
         }
      }
      if(redraw && al_is_event_queue_empty(queue)){
          redraw = false;
          if(player.getFall()){
              cout<<player.getY()<< " \n";
              player.setY(player.getY()+5);
              if(map[((player.getY()+5)/20)][(player.getX()/20)] == '#'){
                  cout<<player.getFall();
                  player.setFall(false);
              }
          }
          graphic.drawMap(map);
          graphic.drawEntity(&player);
          /*for(auto i : enemies){
              graphic.drawEntity(&i);
          }*/
          al_flip_display();
      }
    }
}

void GameManager::loadMap(string path){
    ifstream input(path);
    if(input.is_open()){
        for(int i=0; i<16; i++){
            for(int j=0; j<28; j++){
                char c = input.get();
                if(c != '\0'){
                    map[i][j] = c;
                }
            }
        }
    }else{
        cout<<"File "+path+" does not exist";
    }
}