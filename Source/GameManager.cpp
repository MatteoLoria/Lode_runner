#include "../Headers/GameManager.hpp"
enum MYKEYS{
        KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
GameManager::GameManager(Player p, vector<Enemy> enemies, GraphicManager graphic){
    this->player = p;
    for(auto i : enemies){
        this->enemies.push_back(i);
    }
    this->graphic = graphic;
    this->points = 0;
}

void GameManager::run(int level, ALLEGRO_DISPLAY * display){
    bool redraw=true;
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    ALLEGRO_TIMER * timer = al_create_timer(1.0/60);
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
    while(1){
        ALLEGRO_EVENT event;
        al_wait_for_event(queue,&event);
        if(event.type == ALLEGRO_EVENT_TIMER){
            //TODO: nemici (bellamerda)
            if(keys[KEY_RIGHT] && player.getX() < 300){
                player.setX(player.getX()+7);
            }
            if(keys[KEY_LEFT] && player.getX() > 0){
                player.setX(player.getX()-7);
            }
            if(keys[KEY_UP] && map[560/player.getY()][320/player.getX()] == 'H'){
                player.setY(player.getY()-7);
            }
            if(keys[KEY_DOWN] && map[560/player.getY()][320/player.getX()] == 'H'){
                player.setY(player.getY()+7);
            }
            redraw = true;
        }else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               keys[KEY_UP] = true;
               break;

            case ALLEGRO_KEY_DOWN:
               keys[KEY_DOWN] = true;
               break;

            case ALLEGRO_KEY_LEFT: 
               keys[KEY_LEFT] = true;
               break;

            case ALLEGRO_KEY_RIGHT:
               keys[KEY_RIGHT] = true;
               break;
         }
      }else if(event.type == ALLEGRO_EVENT_KEY_UP) {
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
          graphic.drawMap(map);
          graphic.drawEntity(&player);
          for(auto i : enemies){
              graphic.drawEntity(&i);
          }
      }
    }
}

void GameManager::loadMap(string path){
    //TODO: file implementation
}