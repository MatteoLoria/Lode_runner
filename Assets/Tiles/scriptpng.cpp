#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    al_init();
    al_init_image_addon();
    ALLEGRO_BITMAP * toSave=NULL;
    ALLEGRO_BITMAP * toCut = al_load_bitmap("3hole.png");
    if(!toCut)
        cerr<<"no";
    int k=8;
    for(int i=2; i<88;i+=44){
        for(int j=0; j<180; j+=20, k++){
            cout<<i<<" "<<j<<endl;
            toSave = al_create_sub_bitmap(toCut,j,i,20,40);
            al_save_bitmap((to_string(k)+".png").c_str(),toSave);
        }
    }
    return 0;
}
