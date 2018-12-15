#include "../Headers/GameManager.hpp"
#include <iostream>

int main()
{
    al_init();
    al_init_image_addon();
    ALLEGRO_DISPLAY * display = al_create_display(560, 320);
    char map[16][29] = {"                  S         ",
                        "    $             S         ",
                        "#@#@#@#H#######   S         ",
                        "       H----------S    $    ",
                        "       H    ##H   #######H##",
                        "       H    ##H          H  ",
                        "     0 H    ##H       $0 H  ",
                        "##H#####    ########H#######",
                        "  H                 H       ",
                        "  H           0     H       ",
                        "#########H##########H       ",
                        "         H          H       ",
                        "       $ H----------H   $   ",
                        "    H######         #######H",
                        "    H         &  $         H",
                        "############################"};
    
    GraphicManager Gr(1);
    string sprite[9] = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};
    Player P(14*20,13*20, sprite);
    GameManager G(P, *(new vector<Enemy>()), Gr, map);
    G.run(1, display);
    al_destroy_display(display);

    return 0; 
}