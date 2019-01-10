#include "../Headers/GraphicManager.hpp"
#include <iostream>

GraphicManager::GraphicManager() {}

GraphicManager::GraphicManager(int level, int scale_w, int scale_h, int scale_x, int scale_y, ALLEGRO_BITMAP *buffer, ALLEGRO_DISPLAY *display)
{
    this->level = level;
    this->scale_h = scale_h;
    this->scale_w = scale_w;
    this->scale_x = scale_x;
    this->scale_y = scale_y;
    this->buffer = buffer;
    this->display = display;
}

void GraphicManager::drawMap(char map[16][28])
{
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    ALLEGRO_BITMAP *bitmap = NULL;
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 28; ++j)
        {
            switch (map[i][j])
            {
            case '#': //normal brick
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Tiles/normalBrick.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '@': //solid brick
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Tiles/solidBrick.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case 'H': //ladder
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Tiles/ladder.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '-': //rope
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Tiles/rope.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case 'X': //troll brick
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Tiles/normalBrick.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '$': //coins
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Tiles/coin.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '_':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Tiles/ground.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '1':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Hole/Destructions/0.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '2':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Hole/Destructions/1.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '3':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Hole/Destructions/2.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '4':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Hole/Destructions/3.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '5':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Hole/Destructions/4.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '6':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Hole/Destructions/5.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '7':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Hole/Destructions/6.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '/':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Hole/Creations/0.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '^':
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Hole/Creations/1.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '&':
                map[i][j]= ' ';
                break;
            default: //clean space
                break;
            }
        }
    }
    al_set_target_backbuffer(this->display);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(buffer, 0, 0, 560, 320, scale_x, scale_y, scale_w, scale_h, 0);
}

void GraphicManager::drawFinalLadder(char map[16][28]){
    for(int i=0; i<16; i++){
        for(int j=0; j<28; j++){
            if(map[i][j]=='S'){
                map[i][j] = 'H';
            }
        }
    }
}
void GraphicManager::drawEntity(Entity *E)
{
    al_set_target_bitmap(buffer);
    ALLEGRO_BITMAP *bitmap = al_load_bitmap(("../Assets/Characters/" + E->getEntity() + "/" + to_string(E->getFrame()) + ".png").c_str());
    if (E->getFrame() == 0 || E->getFrame() == 1 || E->getFrame() == 2 || E->getFrame() == 10)//frame 10?
        al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, E->getMirrorX()); // X e Y are always in pixel
    if(E->getFrame() == 8)
        al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, 0);
    if(E->getFrame() == 9)
        al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, 0);
    if (E->getFrame() == 3)
        al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, E->getMirrorY());
    if (E->getFrame() == 4 || E->getFrame() == 11)
        al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, E->getMirrorX());
    if (E->getFrame() == 5 || E->getFrame() == 6 || E->getFrame() == 7)
        al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, E->getMirrorRope());
    al_destroy_bitmap(bitmap);
    al_set_target_backbuffer(this->display);
    al_draw_scaled_bitmap(buffer, 0, 0, 560, 320, scale_x, scale_y, scale_w, scale_h, 0);
}