#include "../Headers/GraphicManager.hpp"

GraphicManager::GraphicManager(){}

GraphicManager::GraphicManager(int level) {this->level = level;}

void GraphicManager::drawMap(char map[16][28])
{
    ALLEGRO_BITMAP * bitmap = NULL;
    for(int i = 0; i < 16; ++i)
        for(int j = 0; j < 28; ++j)
            switch(map[i][j])
            {
                case '#'://normal brick
                    bitmap = al_load_bitmap(("../Assets/Tiles/"+ to_string(level) + "/normalBrick.png").c_str());
                    al_draw_bitmap(bitmap, i*20, j*20, 0);
                    break;
                case '@'://solid brick
                    bitmap = al_load_bitmap(("../Assets/Tiles/"+ to_string(level) + "/solidBrick.png").c_str());
                    al_draw_bitmap(bitmap, i*20, j*20, 0);
                    break;
                case 'H'://ladder
                    bitmap = al_load_bitmap(("../Assets/Tiles/"+ to_string(level) + "/ladder.png").c_str());
                    al_draw_bitmap(bitmap, i*20, j*20, 0);
                    break;
                case '-'://rope
                    bitmap = al_load_bitmap(("../Assets/Tiles/"+ to_string(level) + "/rope.png").c_str());
                    al_draw_bitmap(bitmap, i*20, j*20, 0);
                    break;
                case 'X'://troll brick
                    bitmap = al_load_bitmap(("../Assets/Tiles/"+ to_string(level) + "/normalBrick.png").c_str());
                    al_draw_bitmap(bitmap, i*20, j*20, 0);
                    break;
                case '$'://coins
                    bitmap = al_load_bitmap(("../Assets/Tiles/"+ to_string(level) + "/coin.png").c_str());
                    al_draw_bitmap(bitmap, i*20, j*20, 0);
                    break;
                default://ground
                    bitmap = al_load_bitmap(("../Assets/Tiles/"+ to_string(level) + "/ground.png").c_str());
                    al_draw_bitmap(bitmap, i*20, j*20, 0);
                    break;
            }   
    al_flip_display();
}
            