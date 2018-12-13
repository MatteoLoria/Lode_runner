#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <iostream>
using namespace std;
string s[7]{
    "solidBrick.png",
    "normalBrick.png",
    "strangeLadder.png",
    "coin.png",
    "ladder.png",
    "rope.png",
    "ground.png"
};
int main(int argc, char const *argv[])
{
    al_init();
    al_init_image_addon();
    ALLEGRO_BITMAP * toSave=NULL;
    ALLEGRO_BITMAP * toCut = al_load_bitmap("1tile.png");
    if(!toCut)
        cerr<<"no";
    int k=0;
    for(int i=0; i<80;i+=20){
        for(int j=0; j<80; j+=20, k++){
            cout<<i<<" "<<j<<s[k]<<endl;
            toSave = al_create_sub_bitmap(toCut,j,i,20,20);
            al_save_bitmap(s[k].c_str(),toSave);
        }
    }
    return 0;
}
