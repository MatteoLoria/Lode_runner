#include "../Headers/GraphicManager.hpp"

int main()
{
    al_init();
    al_init_image_addon();
    ALLEGRO_DISPLAY * display = al_create_display(320, 560);
    char mat[16][28];
    for(int i = 0; i < 16; ++i)
        for(int j = 0; j < 28; ++j)
            mat[i][j] = '#';
    GraphicManager G(1);
    G.drawMap(mat);
    al_rest(5);
    al_destroy_display(display);

    return 0; 
}