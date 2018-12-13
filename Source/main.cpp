#include "../Headers/GraphicManager.hpp"

int main()
{
    al_init();
    al_init_image_addon();
    ALLEGRO_DISPLAY * display = al_create_display(320, 560);
    char mat[16][28] = {'#'};
    GraphicManager G(1);
    G.drawMap(mat);
    al_rest(5);
    al_destroy_display(display);

    return 0; 
}