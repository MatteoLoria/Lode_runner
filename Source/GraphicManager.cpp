#include "../Headers/GraphicManager.hpp"

GraphicManager::GraphicManager(){}

GraphicManager::GraphicManager(int level) {this->level = level;}

void GraphicManager::drawMap(char map[16][28])
{
    for(int i = 0; i < 16; ++i)
        for(int j = 0; j < 28; ++j)
            switch(map[i][j])
            {
                case '#'://normal brick
                    ALLEGRO_BITMAP * normalBrick = al_load_bitmap(("../Assets/Tiles/"+ to_string(level) + "/normalBrick.png").c_str());
                    al_draw_bitmap(normalBrick, i*20, j*20, 0);
                    break;
                /*case "@"://solid brick
                    al_draw_bitmap();
                    break;
                case "H"://ladder
                    al_draw_bitmap();
                    break;
                case "-"://rope
                    al_draw_bitmap();
                    break;
                case "X"://troll brick
                    al_draw_bitmap();
                    break;
                case "S"://final ladder
                    al_draw_bitmap();
                    break;
                case "$"://coins
                    al_draw_bitmap();
                    break;
                case "0"://guard
                    al_draw_bitmap();
                    break;
                case "&"://player
                    al_draw_bitmap();
                    break;
                default://ground
                    al_draw_bitmap();
                    break;*/
            }
}