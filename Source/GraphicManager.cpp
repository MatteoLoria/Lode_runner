#include "../Headers/GraphicManager.hpp"
#include <iostream>

GraphicManager::GraphicManager(){}

GraphicManager::GraphicManager(int level) {this->level = level;}

void GraphicManager::drawMap(char map[16][28])
{
    al_clear_to_color(al_map_rgb(0,0,0));
    ALLEGRO_BITMAP * bitmap = NULL;
    for(int i = 0; i < 16; ++i)
        for(int j = 0; j < 28; ++j)
            switch(map[i][j])
            {
                case '#'://normal brick
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Tiles/normalBrick.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '@'://solid brick
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Tiles/solidBrick.png").c_str());
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
                case '1':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Hole/Destructions/0.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '2':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Hole/Destructions/1.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '3':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Hole/Destructions/2.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '4':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Hole/Destructions/3.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '5':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Hole/Destructions/4.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '6':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Hole/Destructions/5.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '7':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Hole/Destructions/6.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '/':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Hole/Creations/0.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                case '^':
                    bitmap = al_load_bitmap(("../Assets/Tiles/Level"+ to_string(level) + "/Hole/Creations/1.png").c_str());
                    al_draw_bitmap(bitmap, j*20, i*20, 0);
                    al_destroy_bitmap(bitmap);
                    break;
                default://clean space
                    break;
            }
}

void GraphicManager::drawEntity(Entity * E)
{
    ALLEGRO_BITMAP * bitmap = al_load_bitmap(("../Assets/Characters/" + E->getEntity() + "/" + to_string(E->getFrame()) + ".png").c_str());
    if(E->getFrame() == 0 || E->getFrame() == 1 || E->getFrame() == 2)
        al_draw_bitmap(bitmap, E->getX(), E->getY()-18, E->getMirrorX());// X e Y are always in pixel
    if(E->getFrame() == 3)
        al_draw_bitmap(bitmap, E->getX(), E->getY()-18, E->getMirrorY());
    if(E->getFrame() == 4)
        al_draw_bitmap(bitmap, E->getX(), E->getY()-18, E->getMirrorX());
    if(E->getFrame() == 5 || E->getFrame() == 6 || E->getFrame() == 7)
        al_draw_bitmap(bitmap, E->getX(), E->getY()-18, E->getMirrorRope());
    al_destroy_bitmap(bitmap);
}