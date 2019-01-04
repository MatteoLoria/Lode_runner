#include "../Headers/GameManager.hpp"
#include <iostream>
#include <fstream>
enum MYKEYS
{
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_X,
    KEY_Z
};
ALLEGRO_DISPLAY * d;
GameManager::GameManager() {}

GameManager::GameManager(Player p, vector<Enemy> enemies, GraphicManager graphic)
{
    this->player = p;
    for (auto i : enemies)
    {
        this->enemies.push_back(i);
    }
    this->graphic = graphic;
    this->points = 0;
}

void GameManager::run(int level, ALLEGRO_DISPLAY *display)
{
    bool redraw = false;
    d=display;
    bool lastIsLeft = false;
    bool lastIsDown = false;
    double delay = 0.0;
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 15);
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    if (level == 1)
    {
        this->loadMap("../Assets/Maps/level1.txt");
    }
    else if (level == 2)
    {
        this->loadMap("../Assets/Maps/level2.txt");
    }
    else
    {
        this->loadMap("../Assets/Maps/level3.txt");
    }
    pathFinder.setWorldSize({16, 28});
    pathFinder.setDiagonalMovement(false);
    al_start_timer(timer);
    bool close = false;
    while (!close)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            if (keys[KEY_RIGHT] && player.getX() < 540 && !player.getFall())
            {
                player.moveRight(map);
            }
            if (keys[KEY_LEFT] && player.getX() > 0 && !player.getFall())
            {
                player.moveLeft(map);
            }
            if (keys[KEY_UP] && !player.getFall())
            {
                player.moveUp(map, lastIsLeft);
            }
            if (keys[KEY_DOWN])
            {
                player.moveDown(map);
            }
            if (keys[KEY_X] && !player.getFall())
            {
                if (player.dig(map, false))
                {
                    player.setFrame(8);
                    holes.push_back({(player.getY() + 5) / 20,
                                     (player.getX() + 39) / 20, 0, 0});
                }
            }
            if (keys[KEY_Z] && !player.getFall())
            {
                if (player.dig(map, true))
                {
                    player.setFrame(9);
                    holes.push_back({(player.getY() + 5) / 20,
                                     (player.getX() / 20) - 1, 0, 0});
                }
            }
            delay += (double)1.0 / 10;
            if (delay >= (1.0 / 15) * 2)
            {
                for (auto &i : enemies)
                {
                    auto path = pathFinder.findPath({i.getY() / 20, i.getX() / 20}, {player.getY() / 20, player.getX() / 20});
                    if (path.size() > 1)
                        path.pop_back();
                    /*//debug
                    for (auto j : path)
                    {
                        ALLEGRO_BITMAP *b = al_create_bitmap(20, 20);
                        al_set_target_bitmap(b);
                        if (j.x == path.back().x && j.y == path.back().y)
                        {
                            al_clear_to_color(al_map_rgb(255, 255, 255));
                        }
                        else
                            al_clear_to_color(al_map_rgb(255, 0, 0));
                        if (j.x == player.getY() && j.y == player.getX())
                            al_clear_to_color(al_map_rgb(0, 0, 255));
                        al_set_target_bitmap(al_get_backbuffer(display));
                        al_draw_bitmap(b, j.y * 20, j.x * 20, 0);
                        al_destroy_bitmap(b);
                        al_flip_display();
                    }
                    //end debug*/
                    int x = path.back().x;
                    int y = path.back().y;
                    i.update(map, holes, player, x, y);
                }
                delay = 0;
            }
            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_X:
                keys[KEY_X] = true;
                break;
            case ALLEGRO_KEY_Z:
                keys[KEY_Z] = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[KEY_UP] = true;
                lastIsDown = false;
                lastIsLeft = false;
                break;

            case ALLEGRO_KEY_DOWN:
                keys[KEY_DOWN] = true;
                lastIsLeft = false;
                lastIsDown = true;
                break;

            case ALLEGRO_KEY_LEFT:
                keys[KEY_LEFT] = true;
                lastIsLeft = true;
                lastIsDown = false;
                break;

            case ALLEGRO_KEY_RIGHT:
                keys[KEY_RIGHT] = true;
                lastIsLeft = false;
                lastIsDown = false;
                break;

            case ALLEGRO_KEY_ESCAPE:
                close = true;
                break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            player.setFrame(player.getFrame() == 3 ? 3 : player.getFrame());
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_X:
                keys[KEY_X] = false;
                break;
            case ALLEGRO_KEY_Z:
                keys[KEY_Z] = false;
                break;
            case ALLEGRO_KEY_UP:
                keys[KEY_UP] = false;
                break;

            case ALLEGRO_KEY_DOWN:
                keys[KEY_DOWN] = false;
                break;

            case ALLEGRO_KEY_LEFT:
                keys[KEY_LEFT] = false;
                break;

            case ALLEGRO_KEY_RIGHT:
                keys[KEY_RIGHT] = false;
                break;
            }
        }
        if (redraw && al_is_event_queue_empty(queue))
        {
            redraw = false;
            if (player.getFall())
            {
                player.setY(player.getY() + 5);
                if (map[((player.getY() + 5) / 20)][(player.getX() / 20)] == '#' || map[((player.getY() + 5) / 20)][(player.getX() / 20)] == 'H' || map[((player.getY() + 5) / 20)][(player.getX() / 20)] == '@')
                    player.setFall(false);
                if (map[((player.getY() - 18) / 20)][(player.getX() / 20)] == '-' && map[((player.getY()) / 20)][(player.getX() / 20)] == '-')
                {
                    player.setFall(false);
                    player.setFrame(5);
                }
                if (map[((player.getY() - 18) / 20)][(player.getX() / 20)] == '-' && lastIsDown && map[((player.getY() + 5) / 20)][(player.getX() / 20)] != '#')
                {
                    player.setFall(true);
                    player.setFrame(4);
                }
            }
            if (!holes.empty())
            {
                for (list<Quadruple>::iterator i = holes.begin(); i != holes.end(); i++)
                {
                    i->third += 1.0 / 15;
                    if (map[i->first][i->second] == '7' && !i->already)
                    {
                        map[i->first][i->second] = ' ';
                    }
                    else if (map[i->first][i->second] != ' ' && map[i->first][i->second] != '/' && map[i->first][i->second] != '^' && map[i->first][i->second] != '#' && !i->already)
                    {
                        map[i->first][i->second]++;
                    }
                    if (3.0 > i->third && i->third > 2.8 && !i->already)
                    {
                        map[i->first][i->second] = '/';
                    }
                    else if (3.2 > i->third && i->third > 3.0 && !i->already)
                    {
                        map[i->first][i->second] = '^';
                    }
                    else if (i->third > 3.2 && !i->already)
                    {
                        map[i->first][i->second] = '#';
                        i->already = true;
                    }
                }
            }
            graphic.drawMap(map);
            graphic.drawEntity(&player);
            for (auto i : enemies)
            {
                graphic.drawEntity(&i);
            }
            al_flip_display();
        }
    }
}

void GameManager::loadMap(string path)
{
    ifstream input(path);
    if (input.is_open())
    {
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 28; j++)
            {
                char c = input.get();
                if (c != '\0')
                {
                    map[i][j] = c;
                }
                //ALLEGRO_BITMAP * f = al_create_bitmap(20,20);
                switch (c)
                {
                case '#':
                case '@':
                case '_':
                case 'X':
                    pathFinder.addCollision({i, j});
                    break;
                default:
                    break;
                }
            }
        }
        for(int i = 0; i < 16; i++)
            for(int j = 0; j < 28; j++)
                if(map[i][j] == ' ' && map[i+1][j] != '#' && map[i+1][j] != 'H' && map[i+1][j] != '@')
                    pathFinder.addCollision({i,j});
    }
    else
    {
        cout << "File " + path + " does not exist";
    }
}