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
ALLEGRO_DISPLAY *d;

GameManager::GameManager() {}

GameManager::GameManager(GraphicManager graphic) { this->graphic = graphic; }

GameManager::GameManager(Player p, vector<Enemy> enemies, GraphicManager graphic)
{
    this->player = p;
    for (auto i : enemies)
    {
        this->enemies.push_back(i);
    }
    this->graphic = graphic;
}

int GameManager::run(int level, ALLEGRO_DISPLAY *display)
{
    bool redraw = false;
    bool lastIsLeft = false;
    bool lastIsDown = false;
    double waitForDigDx = 2.1;
    double waitForDigSx = 2.1;
    double delay = 0.0;
    d = display;
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 15);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    createEntities(level);
    loadMap("../Assets/Maps/level" + to_string(level) + ".txt");
    pathFinder.setWorldSize({16, 28});
    al_start_timer(timer);
    bool close = false;
    while (!close)
    {
        waitForDigDx += 0.1;
        waitForDigSx += 0.1;
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            if (keys[KEY_RIGHT] && player.getX() < 540 && !player.getFall())
            {
                player.moveRight(map, false);
            }
            if (keys[KEY_LEFT] && player.getX() > 0 && !player.getFall())
            {
                player.moveLeft(map, false);
            }
            if (keys[KEY_UP] && !player.getFall())
            {
                player.moveUp(map, lastIsLeft, false);
            }
            if (keys[KEY_DOWN])
            {
                player.moveDown(map, false);
            }
            if (keys[KEY_X] && !player.getFall() && player.getFrame() != 4 && waitForDigDx > 2.0)
            {
                waitForDigDx = 0.0;
                if (player.dig(map, false))
                {
                    player.setFrame(8);
                    holes.push_back({(player.getY() + 5) / 20,
                                     (player.getX() + 39) / 20, 0, 0});
                }
            }
            if (keys[KEY_Z] && !player.getFall() && player.getFrame() != 4 && waitForDigSx > 2.0)
            {
                waitForDigSx = 0.0;
                if (player.dig(map, true))
                {
                    player.setFrame(9);
                    holes.push_back({(player.getY() + 5) / 20,
                                     (player.getX() / 20) - 1, 0, 0});
                }
            }
            if (map[player.getY() / 20][player.getX() / 20] == '$')
            {
                player.increasePoints();
                map[player.getY() / 20][player.getX() / 20] = ' ';
            }
            delay += (double)1.0 / 10;
            if (delay >= (1.0 / 15) * 2)
            {
                for (auto &i : enemies)
                {
                    /*if ((i.getMirrorX() && (i.getX() == player.getX()+15)  && i.getY() == player.getY()) || (!i.getMirrorX() && i.getX() + 15 == player.getX() && i.getY() == player.getY())
                        || (i.getY() + 15 == player.getY() && i.getX() == player.getX()) || (i.getY() == player.getY() + 15 && i.getX() == player.getX()))
                    {
                        player.decreaseLives();
                        if (player.getLives() == 0)//quando muore va controllato il keys[]
                            return 0;
                        else
                        {
                            restart();
                            loadMap(string("../Assets/Maps/level") + to_string(level) + ".txt");
                            break;
                        }
                    }
                    else if (i.getX() + 15 == player.getX() && i.getY() == player.getY())
                    {
                        player.decreaseLives();
                        if (player.getLives() == 0)
                            return 0;
                        else
                        {
                            restart();
                            loadMap(string("../Assets/Maps/level") + to_string(level) + ".txt");
                            break;
                        }
                    }*/
                    auto path = pathFinder.findPath({i.getY() / 20, i.getX() / 20}, {player.getY() / 20, (player.getX() + 10) / 20});
                    if (path.size() > 1)
                        path.pop_back(); //forse non serve più
                    else if (path.size() == 1 && !i.isInHole(holes, map, false) && !i.isInHole(holes, map, true))
                    {
                        player.decreaseLives();
                        if (player.getLives() == 0) //quando muore va controllato il keys[]
                            return 0;
                        else
                        {
                            restart();
                            loadMap(string("../Assets/Maps/level") + to_string(level) + ".txt");
                            break;
                        }
                    }
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
                    if (avaibleSpot(x, y))
                        i.update(map, holes, player, x, y);
                }
                delay = 0;
            }
            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            return 0;
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
            player.setFrame(player.getFrame() == 3 ? 3 : player.getFrame()); //bu
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
                sound.playFall();
                player.setY(player.getY() + 5);
                if (map[((player.getY() + 5) / 20)][(player.getX() / 20)] == '#' || map[((player.getY() + 5) / 20)][(player.getX() / 20)] == 'H' || map[((player.getY() + 5) / 20)][(player.getX() / 20)] == '@')
                {
                    player.setFall(false);
                    cout << "a";
                    sound.stopFall();
                }
                if (map[((player.getY() - 18) / 20)][(player.getX() / 20)] == '-' && map[((player.getY()) / 20)][(player.getX() / 20)] == '-')
                {
                    player.setFall(false);
                    cout << "b";
                    //sound.stopFall();
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
                    else if (map[i->first][i->second] != ' ' && map[i->first][i->second] != '/' && map[i->first][i->second] != '^' && map[i->first][i->second] != '#' && map[i->first][i->second] != '}' && !i->already)
                    {
                        map[i->first][i->second]++;
                    }
                    if (7.0 > i->third && i->third > 6.8 && !i->already)
                    {
                        map[i->first][i->second] = '/';
                    }
                    else if (7.2 > i->third && i->third > 7.0 && !i->already)
                    {
                        map[i->first][i->second] = '^';
                    }
                    else if (i->third > 7.2 && !i->already)
                    {
                        map[i->first][i->second] = '#';
                        i->already = true;
                    }
                }
            }
            if (player.getPoints() == coins)
            {
                graphic.drawFinalLadder(map);
            }
            if (player.getY() < 0)
            {
                restart();
                return 1;
            }
            if (player.getY() > 340 || map[player.getY() / 20][player.getX() / 20] == '#')
            {
                player.decreaseLives();
                if (player.getLives() == 0)
                { //quando muore va controllato il keys[]
                    player.setLives(3);
                    restart();
                    return 0;
                }
                else
                {
                    restart();
                    loadMap(string("../Assets/Maps/level") + to_string(level) + ".txt");
                }
            }
            graphic.drawMap(map, level);
            graphic.drawEntity(&player);
            graphic.drawStats(player.getPoints(), coins, player.getLives(), level);
            for (auto i : enemies)
            {
                graphic.drawEntity(&i);
            }
            al_flip_display();
        }
    }
    return -1;
}

bool GameManager::avaibleSpot(int y, int x)
{
    for (auto i : enemies)
    {
        if (x == i.getX() / 20 && y == i.getY() / 20)
            return false;
    }
    return true;
}

void GameManager::restart()
{
    coins = 0;
    player.setX(player.getInitX());
    player.setY(player.getInitY());
    player.setFall(false);
    player.setFrame(0);
    player.setPoints(0);
    for (auto &i : enemies)
    {
        i.setFrame(0);
        i.setX(i.getInitX());
        i.setY(i.getInitY());
        i.setFall(false);
        i.setFallen(0);
    }
    holes.clear();
}

void GameManager::loadMap(string path)
{
    pathFinder.clearCollisions();
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
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 28; j++)
            {
                if (map[i][j] == ' ' && map[i + 1][j] != '#' && map[i + 1][j] != 'H' && map[i + 1][j] != '@')
                    pathFinder.addCollision({i, j});
                if (map[i][j] == '$')
                    ++coins;
            }
    }
    else
    {
        cout << "File " + path + " does not exist";
        exit(1);
    }
}

void GameManager::createEntities(int level)
{
    enemies.clear();
    if (level == 1)
    {
        player.setInitX(14 * 20);
        player.setInitY((14 * 20) + 18);
        Enemy e1(14 * 20, (9 * 20) + 18);
        Enemy e2(23 * 20, (6 * 20) + 18);
        Enemy e3(5 * 20, (6 * 20) + 18);
        enemies.push_back(e1);
        enemies.push_back(e2);
        enemies.push_back(e3);
    }
    else if (level == 2)
    {
        player.setInitX(14 * 20);
        player.setInitY((14 * 20) + 18);
        Enemy e1(4 * 20, (3 * 20) + 18);
        Enemy e2(4 * 20, (8 * 20) + 18);
        Enemy e3(20 * 20, (5 * 20) + 18);
        enemies.push_back(e1);
        enemies.push_back(e2);
        enemies.push_back(e3);
    }
    else if (level == 3)
    {
        player.setInitX(12 * 20);
        player.setInitY((14 * 20) + 18);
        Enemy e1(4 * 20, (11 * 20) + 18);
        Enemy e2(13 * 20, (2 * 20) + 18);
        Enemy e3(22 * 20, (3 * 20) + 18);
        enemies.push_back(e1);
        enemies.push_back(e2);
        enemies.push_back(e3);
    }
    else if (level == 4)
    {
        player.setInitX(12 * 20);
        player.setInitY((14 * 20) + 18);
        Enemy e1(9 * 20, (1 * 20) + 18);
        Enemy e2(19 * 20, (1 * 20) + 18);
        Enemy e3(16 * 20, (8 * 20) + 18);
        enemies.push_back(e1);
        enemies.push_back(e2);
        enemies.push_back(e3);
    }
    else if (level == 5)
    {
        player.setInitX(12 * 20);
        player.setInitY((14 * 20) + 18);
        Enemy e1(9 * 20, (11 * 20) + 18);
        Enemy e2(7 * 20, (4 * 20) + 18);
        Enemy e3(26 * 20, (6 * 20) + 18);
        enemies.push_back(e1);
        enemies.push_back(e2);
        enemies.push_back(e3);
    }
}