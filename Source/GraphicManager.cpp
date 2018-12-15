#include "../Headers/GraphicManager.hpp"
#include <iostream>

GraphicManager::GraphicManager(){}

GraphicManager::GraphicManager(int level) {this->level = level;}

void GraphicManager::drawMap(char map[16][29])
{
    al_clear_to_color(al_map_rgb(0,0,0));
    ALLEGRO_BITMAP * bitmap = NULL;
    for(int i = 0; i < 16; ++i)
        for(int j = 0; j < 29; ++j)
            switch(map[i][j])
            {
                case '#'://normal brick
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/tiles/normalBrick.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '@'://solid brick
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/tiles/solidBrick.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case 'H'://ladder
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Tiles/ladder.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '-'://rope
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Tiles/rope.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case 'X'://troll brick
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Tiles/normalBrick.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '$'://coins
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Tiles/coin.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '_':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Tiles/ground.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                default://clean space
                    break;
            }
}

void GraphicManager::drawEntity(Entity * E, bool mirror)
{
    ALLEGRO_BITMAP * bitmap = al_load_bitmap(("../Assets/Characters/" + E->getEntity() + "/" + to_string(E->getFrame()) + ".png").c_str());
    al_draw_bitmap(bitmap, E->getX(), E->getY(), mirror);// X e Y sono sempre pixel
    al_destroy_bitmap(bitmap);
}