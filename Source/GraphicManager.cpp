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
    //sound.stopMenu();
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
            if (ev.mouse.x / (scale_w / 560) >= 230 && ev.mouse.x / (scale_w / 560) <= 370 && ev.mouse.y / (scale_h / 320) >= 108 && ev.mouse.y / (scale_h / 320) <= 148)
            {
                btp = al_create_bitmap(140, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120)); //choose color
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 190, 90, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 205 && ev.mouse.x / (scale_w / 560) <= 400 && ev.mouse.y / (scale_h / 320) >= 165 && ev.mouse.y / (scale_h / 320) <= 210)
            {
                btp = al_create_bitmap(195, 45);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 165, 145, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 205 && ev.mouse.x / (scale_w / 560) <= 400 && ev.mouse.y / (scale_h / 320) >= 220 && ev.mouse.y / (scale_h / 320) <= 265)
            {
                btp = al_create_bitmap(195, 45);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 165, 200, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 238 && ev.mouse.x / (scale_w / 560) <= 358 && ev.mouse.y / (scale_h / 320) >= 277 && ev.mouse.y / (scale_h / 320) <= 317)
            {
                btp = al_create_bitmap(120, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 198, 260, 0);
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
            if (ev.mouse.x / (scale_w / 560) >= 230 && ev.mouse.x / (scale_w / 560) <= 370 && ev.mouse.y / (scale_h / 320) >= 108 && ev.mouse.y / (scale_h / 320) <= 148)
            {
                sound.stopMenu();
                return 1; //first level
            }
            else if (ev.mouse.x / (scale_w / 560) >= 205 && ev.mouse.x / (scale_w / 560) <= 400 && ev.mouse.y / (scale_h / 320) >= 165 && ev.mouse.y / (scale_h / 320) <= 210)
                return 4; //options
            else if (ev.mouse.x / (scale_w / 560) >= 205 && ev.mouse.x / (scale_w / 560) <= 400 && ev.mouse.y / (scale_h / 320) >= 220 && ev.mouse.y / (scale_h / 320) <= 265)
                return 3; //credits
            else if (ev.mouse.x / (scale_w / 560) >= 238 && ev.mouse.x / (scale_w / 560) <= 358 && ev.mouse.y / (scale_h / 320) >= 277 && ev.mouse.y / (scale_h / 320) <= 317)
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

int GraphicManager::drawOptions(SoundManager &sound)
{
    al_set_target_bitmap(buffer);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_BITMAP *options = al_load_bitmap("../Assets/Tiles/Options.png");
    int diff = 4; //guardare set di gameManager
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(options, 0, 0, 0);
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
        options = al_load_bitmap("../Assets/Tiles/Options.png");
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(options, 0, 0, 0);
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);
        switch (ev.type)
        {
        case ALLEGRO_EVENT_MOUSE_AXES: //movimento mouse
            if (ev.mouse.x / (scale_w / 560) >= 205 && ev.mouse.x / (scale_w / 560) <= 403 && ev.mouse.y / (scale_h / 320) >= 77 && ev.mouse.y / (scale_h / 320) <= 117)
            {
                btp = al_create_bitmap(198, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 165, 60, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 175 && ev.mouse.x / (scale_w / 560) <= 440 && ev.mouse.y / (scale_h / 320) >= 145 && ev.mouse.y / (scale_h / 320) <= 185)
            {
                btp = al_create_bitmap(265, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 137, 125, 0);
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
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                return diff;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if (ev.mouse.x / (scale_w / 560) >= 205 && ev.mouse.x / (scale_w / 560) <= 403 && ev.mouse.y / (scale_h / 320) >= 77 && ev.mouse.y / (scale_h / 320) <= 117)
                diff = drawAssets(sound); //assets
            else if (ev.mouse.x / (scale_w / 560) >= 175 && ev.mouse.x / (scale_w / 560) <= 440 && ev.mouse.y / (scale_h / 320) >= 145 && ev.mouse.y / (scale_h / 320) <= 185)
                diff = drawDifficulty(sound); //difficolta
            else if (ev.mouse.x / (scale_w / 560) >= 250 && ev.mouse.x / (scale_w / 560) <= 390 && ev.mouse.y / (scale_h / 320) >= 210 && ev.mouse.y / (scale_h / 320) <= 260)
                return diff; //non cambia il livello di difficoltà
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
        if (options != 0)
            al_destroy_bitmap(options);
        btp = 0;
        options = 0;
        al_flush_event_queue(queue);
    }
    al_destroy_event_queue(queue);
    return diff;
}

int GraphicManager::drawAssets(SoundManager &sound)
{
    al_set_target_bitmap(buffer);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_BITMAP *assets = al_load_bitmap("../Assets/Tiles/Assets.png");
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(assets, 0, 0, 0);
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
        assets = al_load_bitmap("../Assets/Tiles/Assets.png");
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(assets, 0, 0, 0);
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);
        switch (ev.type)
        {
        case ALLEGRO_EVENT_MOUSE_AXES: //movimento mouse
            if (ev.mouse.x / (scale_w / 560) >= 205 && ev.mouse.x / (scale_w / 560) <= 405 && ev.mouse.y / (scale_h / 320) >= 60 && ev.mouse.y / (scale_h / 320) <= 100)
            {
                btp = al_create_bitmap(200, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 165, 45, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 140 && ev.mouse.x / (scale_w / 560) <= 485 && ev.mouse.y / (scale_h / 320) >= 125 && ev.mouse.y / (scale_h / 320) <= 165)
            {
                btp = al_create_bitmap(345, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 100, 105, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 145 && ev.mouse.x / (scale_w / 560) <= 480 && ev.mouse.y / (scale_h / 320) >= 180 && ev.mouse.y / (scale_h / 320) <= 220)
            {
                btp = al_create_bitmap(335, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 105, 165, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 238 && ev.mouse.x / (scale_w / 560) <= 358 && ev.mouse.y / (scale_h / 320) >= 235 && ev.mouse.y / (scale_h / 320) <= 275)
            {
                btp = al_create_bitmap(120, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 198, 225, 0);
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
                return 4;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if (ev.mouse.x / (scale_w / 560) >= 205 && ev.mouse.x / (scale_w / 560) <= 405 && ev.mouse.y / (scale_h / 320) >= 60 && ev.mouse.y / (scale_h / 320) <= 100)
            {
                sound.playClick();
                tiles = "classic";
                return 4;
            }
            else if (ev.mouse.x / (scale_w / 560) >= 140 && ev.mouse.x / (scale_w / 560) <= 485 && ev.mouse.y / (scale_h / 320) >= 125 && ev.mouse.y / (scale_h / 320) <= 165)
            {
                sound.playClick();
                tiles = "professional";
                return 4;
            }
            else if (ev.mouse.x / (scale_w / 560) >= 145 && ev.mouse.x / (scale_w / 560) <= 480 && ev.mouse.y / (scale_h / 320) >= 180 && ev.mouse.y / (scale_h / 320) <= 220)
            {
                sound.playClick();
                tiles = "championship";
                return 4;
            }
            else if (ev.mouse.x / (scale_w / 560) >= 238 && ev.mouse.x / (scale_w / 560) <= 358 && ev.mouse.y / (scale_h / 320) >= 235 && ev.mouse.y / (scale_h / 320) <= 275)
                return 4;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
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
        if (assets != 0)
            al_destroy_bitmap(assets);
        btp = 0;
        assets = 0;
        al_flush_event_queue(queue);
    }
    al_destroy_event_queue(queue);
    return 4;
}

int GraphicManager::drawDifficulty(SoundManager &sound)
{
    al_set_target_bitmap(buffer);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_BITMAP *difficulty = al_load_bitmap("../Assets/Tiles/Difficulty.png");
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(difficulty, 0, 0, 0);
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
        difficulty = al_load_bitmap("../Assets/Tiles/Difficulty.png");
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(difficulty, 0, 0, 0);
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);
        switch (ev.type)
        {
        case ALLEGRO_EVENT_MOUSE_AXES: //movimento mouse
            if (ev.mouse.x / (scale_w / 560) >= 225 && ev.mouse.x / (scale_w / 560) <= 370 && ev.mouse.y / (scale_h / 320) >= 65 && ev.mouse.y / (scale_h / 320) <= 105)
            {
                btp = al_create_bitmap(145, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 190, 50, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 200 && ev.mouse.x / (scale_w / 560) <= 405 && ev.mouse.y / (scale_h / 320) >= 125 && ev.mouse.y / (scale_h / 320) <= 165)
            {
                btp = al_create_bitmap(195, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 165, 110, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 225 && ev.mouse.x / (scale_w / 560) <= 370 && ev.mouse.y / (scale_h / 320) >= 180 && ev.mouse.y / (scale_h / 320) <= 220)
            {
                btp = al_create_bitmap(145, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 185, 165, 0);
            }
            else if (ev.mouse.x / (scale_w / 560) >= 238 && ev.mouse.x / (scale_w / 560) <= 358 && ev.mouse.y / (scale_h / 320) >= 235 && ev.mouse.y / (scale_h / 320) <= 275)
            {
                btp = al_create_bitmap(120, 40);
                al_set_target_bitmap(btp);
                al_clear_to_color(al_map_rgba(120, 120, 120, 120));
                al_set_target_bitmap(buffer);
                al_draw_bitmap(btp, 198, 225, 0);
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
                return 4; //se ritorna 4 non cambia nulla(guardare il set nel gameManager)
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            sound.playClick();
            if (ev.mouse.x / (scale_w / 560) >= 205 && ev.mouse.x / (scale_w / 560) <= 405 && ev.mouse.y / (scale_h / 320) >= 60 && ev.mouse.y / (scale_h / 320) <= 100)
                return 1;
            else if (ev.mouse.x / (scale_w / 560) >= 140 && ev.mouse.x / (scale_w / 560) <= 485 && ev.mouse.y / (scale_h / 320) >= 125 && ev.mouse.y / (scale_h / 320) <= 165)
                return 2;
            else if (ev.mouse.x / (scale_w / 560) >= 145 && ev.mouse.x / (scale_w / 560) <= 480 && ev.mouse.y / (scale_h / 320) >= 180 && ev.mouse.y / (scale_h / 320) <= 220)
                return 3;
            else if (ev.mouse.x / (scale_w / 560) >= 238 && ev.mouse.x / (scale_w / 560) <= 358 && ev.mouse.y / (scale_h / 320) >= 235 && ev.mouse.y / (scale_h / 320) <= 275)
                return 4; //se ritorna 4 non cambia nulla(guardare il set nel gameManager)
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
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
        if (difficulty != 0)
            al_destroy_bitmap(difficulty);
        btp = 0;
        difficulty = 0;
        al_flush_event_queue(queue);
    }
    al_destroy_event_queue(queue);
    return 4;
}

void GraphicManager::drawMap(char map[16][28])
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
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Tiles/normalBrick.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '@': //solid brick
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Tiles/solidBrick.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case 'H': //ladder
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Tiles/ladder.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '-': //rope
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Tiles/rope.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '$': //coins
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Tiles/coin.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '1':
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Hole/Destructions/0.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '2':
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Hole/Destructions/1.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '3':
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Hole/Destructions/2.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '4':
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Hole/Destructions/3.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '5':
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Hole/Destructions/4.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '6':
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Hole/Destructions/5.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '7':
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Hole/Destructions/6.png").c_str());
                al_draw_bitmap(bitmap, j * 20, (i - 1) * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '/':
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Hole/Creations/0.png").c_str());
                al_draw_bitmap(bitmap, j * 20, i * 20, 0);
                al_destroy_bitmap(bitmap);
                break;
            case '^':
                bitmap = al_load_bitmap(("../Assets/Tiles/" + tiles + "/Hole/Creations/1.png").c_str());
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
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    ALLEGRO_BITMAP *credits = al_load_bitmap("../Assets/Tiles/Final.png");
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(credits, 0, 0, 0);
    ALLEGRO_EVENT_QUEUE *q = al_create_event_queue();
    al_register_event_source(q, al_get_keyboard_event_source());
    al_register_event_source(q, al_get_mouse_event_source());
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_scaled_bitmap(buffer, 0, 0, 560, 320, scale_x, scale_y, scale_w, scale_h, 0);
    al_flip_display();
    while (1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(q, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            sound.playClick();
            return 0;
        }
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            sound.playClick();
            return 0;
        }
    }
    return 2;
}

int GraphicManager::drawCredits(SoundManager &sound)
{
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    ALLEGRO_BITMAP *credits = al_load_bitmap("../Assets/Tiles/Credits.png");
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(credits, 0, 0, 0);
    ALLEGRO_EVENT_QUEUE *q = al_create_event_queue();
    al_register_event_source(q, al_get_keyboard_event_source());
    al_register_event_source(q, al_get_mouse_event_source());
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_scaled_bitmap(buffer, 0, 0, 560, 320, scale_x, scale_y, scale_w, scale_h, 0);
    al_flip_display();
    while (1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(q, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            sound.playClick();
            return 0;
        }
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            sound.playClick();
            return 0;
        }
    }
    return 2;
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