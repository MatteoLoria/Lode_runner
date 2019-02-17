#include "../Headers/GraphicManager.hpp"
#include "../Headers/SoundManager.hpp"
#include <iostream>

GraphicManager::GraphicManager() {}

GraphicManager::GraphicManager(const int &scale_w, const int &scale_h, const int &scale_x, const int &scale_y, ALLEGRO_BITMAP *buffer, ALLEGRO_DISPLAY *display)
{
    this->scale_h = scale_h;
    this->scale_w = scale_w;
    this->scale_x = scale_x;
    this->scale_y = scale_y;
    this->buffer = buffer;
    this->display = display;
    this->font = al_load_ttf_font("../Assets/Fonts/Quantum.otf", 48, 0);
    if (!font)
    {
        exit(1);
    }
}

GraphicManager::~GraphicManager()
{
    al_destroy_font(font);
}

int GraphicManager::drawMenu(SoundManager &sound)
{
    if (!buffer)
        return 2;
    al_set_target_bitmap(buffer);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (!queue)
        return 2;
    sound.playMenu();
    ALLEGRO_BITMAP *menu = al_load_bitmap("../Assets/Tiles/Menu.png");
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(menu, 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(buffer, 0, 0, 560, 320, scale_x, scale_y, scale_w, scale_h, 0);
    al_flip_display();
    al_set_target_bitmap(buffer);
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    ALLEGRO_BITMAP *btp = al_create_bitmap(140, 40);
    while (true)
    {
        menu = al_load_bitmap("../Assets/Tiles/Menu.png");
        if (!menu)
            return 2;
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(menu, 0, 0, 0);
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);
        switch (ev.type)
        {
        case ALLEGRO_EVENT_MOUSE_AXES: //movimento mouse
            if (ev.mouse.x / (scale_w / 560) >= 250 && ev.mouse.x / (scale_w / 560) <= 390 && ev.mouse.y / (scale_h / 320) >= 85 && ev.mouse.y / (scale_h / 320) <= 140)
            {
                btp = al_create_bitmap(140, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120)); //choose color
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 190, 70, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 220 && ev.mouse.x / (scale_w / 560) <= 420 && ev.mouse.y / (scale_h / 320) >= 150 && ev.mouse.y / (scale_h / 320) <= 195)
            {
                btp = al_create_bitmap(195, 45);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 165, 128, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 250 && ev.mouse.x / (scale_w / 560) <= 390 && ev.mouse.y / (scale_h / 320) >= 210 && ev.mouse.y / (scale_h / 320) <= 260)
            {
                btp = al_create_bitmap(140, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 190, 190, 0);
            }
            else
            {
                if (btp != 0 || btp != NULL)
                {
                    al_set_target_bitmap(btp);
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                }
                al_set_target_bitmap(buffer);
            }
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            sound.playClick();
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                exit(1);
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if (ev.mouse.x / (scale_w / 560) >= 220 && ev.mouse.x / (scale_w / 560) <= 370 && ev.mouse.y / (scale_h / 320) >= 80 && ev.mouse.y / (scale_h / 320) <= 130)
            {
                sound.stopMenu();
                return 1; //first level
            }
            else if (ev.mouse.x / (scale_w / 560) >= 200 && ev.mouse.x / (scale_w / 560) <= 400 && ev.mouse.y / (scale_h / 320) >= 140 && ev.mouse.y / (scale_h / 320) <= 188)
                return 3; //credits
            else if (ev.mouse.x / (scale_w / 560) >= 220 && ev.mouse.x / (scale_w / 560) <= 370 && ev.mouse.y / (scale_h / 320) >= 200 && ev.mouse.y / (scale_h / 320) <= 250)
                return 2; //quit
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            sound.playClick();
            break;
        default:
            break;
        }
        al_set_target_bitmap(al_get_backbuffer(display));
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_scaled_bitmap(buffer, 0, 0, 560, 320, scale_x, scale_y, scale_w, scale_h, 0);
        al_flip_display();
        al_set_target_bitmap(buffer);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        if (btp != 0)
            al_destroy_bitmap(btp);
        if (menu != 0)
            al_destroy_bitmap(menu);
        btp = 0;
        menu = 0;
        al_flush_event_queue(queue);
    }
    al_destroy_event_queue(queue);
    return 1;
}
void GraphicManager::drawMap(char map[16][28], const int &level)
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
            case '$': //coins
                bitmap = al_load_bitmap(("../Assets/Tiles/Level" + to_string(level) + "/Tiles/coin.png").c_str());
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
            default: //clean space
                break;
            }
        }
    }
    al_set_target_backbuffer(this->display);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(buffer, 0, 0, 560, 320, scale_x, scale_y, scale_w, scale_h, 0);
}

void GraphicManager::drawStats(const int &coins, const int &lives, const int &level)
{
    al_draw_textf(font, al_map_rgb(145, 0, 0), 0, 0, 0, "Coins Remaining: %02d \t \t \t \t Lives: %02d \t \t \t Level: %02d", coins, lives, level);
}

void GraphicManager::drawFinalLadder(char map[16][28])
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            if (map[i][j] == 'S')
            {
                map[i][j] = 'H';
            }
        }
    }
}
void GraphicManager::drawEntity(Entity *E)
{
    al_set_target_bitmap(buffer);
    ALLEGRO_BITMAP *bitmap = al_load_bitmap(("../Assets/Characters/" + E->getEntity() + "/" + to_string(E->getFrame()) + ".png").c_str());
    if (E->getFrame() == 0 || E->getFrame() == 1 || E->getFrame() == 2 || E->getFrame() == 10)
        al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, E->getMirrorX()); // X e Y are always in pixel
    if (E->getEntity() == "Player")
    {
        if (E->getFrame() == 8)
            al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, 0);
        if (E->getFrame() == 9)
            al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, 0);
    }
    else
    {
        if (E->getFrame() == 8 || E->getFrame() == 9)
            al_draw_bitmap(bitmap, E->getX(), E->getY() - 18, E->getMirrorX());
    }
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

int GraphicManager::drawFinal(SoundManager &sound)
{
    
}

void GraphicManager::drawYouDied(SoundManager &sound)
{
    al_set_target_bitmap(al_get_backbuffer(display));
    int incr = 0.1;
    int alpha = 0.1;
    for (int i = 0; i < 5; i++)
    {
        ALLEGRO_BITMAP *b = al_load_bitmap("../Assets/Tiles/Died.png");
        //al_rest(0.02);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_tinted_scaled_bitmap(b, al_map_rgba_f(1, 1, 1, alpha), 0, 0, 560, 320, scale_x, scale_y, scale_w, scale_h, 0);
        alpha += incr;
        al_destroy_bitmap(b);
        al_flip_display();
    }
    ALLEGRO_EVENT_QUEUE *q = al_create_event_queue();
    al_register_event_source(q, al_get_mouse_event_source());
    al_register_event_source(q, al_get_keyboard_event_source());
    while (1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(q, &ev);
        switch (ev.type)
        {
        case ALLEGRO_EVENT_KEY_DOWN:
            sound.playClick();
            return;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            sound.playClick();
            return;
            break;
        default:
            break;
        }
    }
}