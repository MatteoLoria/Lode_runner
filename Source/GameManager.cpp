/*
 @authors Matteo Notaro               &  Matteo Loria
 @github  https://github.com/MattNot     https://github.com/MatteoLoria

 19/02/2019
*/

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

GameManager::GameManager() {}

void GameManager::setDiffulty(const int &difficulty)
{
    if (difficulty != 4)
        this->difficulty = difficulty;
}

int GameManager::run(const int &level, ALLEGRO_DISPLAY *display, SoundManager &sound, GraphicManager &graphic)
{
    bool redraw = false;
    bool lastIsLeft = false; //se è true si stava andando a sinistra
    bool lastIsDown = false; //se è true si stava andando sotto
    bool stair = false;
    bool bonus = false;
    double timeBonus = 0.0;    //quanto tempo rimane di bonus
    double waitForDigDx = 2.1; //contatore per il dig destro(serve per evitare di un abuso di dig)
    double waitForDigSx = 2.1; //contatore per il dig sinistro(serve per evitare di un abuso di dig)
    double delay = 0.0;        //scandisce il movimento dei nemici
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (!queue)
    {
        cout << "Failed to create the queue";
        exit(-1);
    }
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 15);
    if (!timer)
    {
        cout << "Failed to create the timer";
        exit(-1);
    }
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    loadMap("../Assets/Maps/level" + to_string(level) + ".txt"); //carica la mappa dal file di testo
    createEntities(level);
    pathFinder.setWorldSize({16, 28}); //setta la dimensione della mappa per Astar
    al_start_timer(timer);
    bool close = false;
    sound.playBackground(false);
    while (!close)
    {
        if (bonus)
        {
            graphic.drawBonus();
            timeBonus += 0.1;
        }
        if (timeBonus >= 40)
        { //bonus scaduto
            bonus = false;
            timeBonus = 0;
            sound.stopBackground();
            sound.playBackground(false);
        }
        waitForDigDx += 0.1;
        waitForDigSx += 0.1;
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_TIMER)
        { //movimento del player in base agli input
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
                if (player.dig(map, false)) //controllo se si può fare il dig
                {
                    sound.playDig();
                    player.setFrame(8);
                    holes.push_back({(player.getY() + 5) / 20,
                                     (player.getX() + 39) / 20, 0, 0}); //pusha la buca da gestire
                }
            }
            if (keys[KEY_Z] && !player.getFall() && player.getFrame() != 4 && waitForDigSx > 2.0)
            { //stessa cosa sopra
                waitForDigSx = 0.0;
                if (player.dig(map, true))
                {
                    sound.playDig();
                    player.setFrame(9);
                    holes.push_back({(player.getY() + 5) / 20,
                                     (player.getX() / 20) - 1, 0, 0});
                }
            }
            if (map[player.getY() / 20][player.getX() / 20] == '$')
            { //il player raccoglie la moneta
                sound.playCoin();
                player.increasePoints();
                coins--;
                map[player.getY() / 20][player.getX() / 20] = ' ';
            }
            if (map[player.getY() / 20][player.getX() / 20] == 'M')
            {
                map[player.getY() / 20][player.getX() / 20] = ' ';
                sound.playCoin();
                bonus = true;
                sound.stopBackground();
                sound.playBackground(true);
            }
            delay += (double)1.0 / 10;
            if (delay >= (1.0 / 15) * (2 + (3 * bonus)))
            {
                for (auto &i : enemies)
                {
                    auto path = pathFinder.findPath({i.getY() / 20, i.getX() / 20}, {player.getY() / 20, (player.getX() + 10) / 20}); //trova il percorso per raggiungere il player
                    if (path.size() > 1)
                        path.pop_back();
                    else if (path.size() == 1 && !i.isInHole(holes, map, false) && !i.isInHole(holes, map, true))
                    { //se il percorso dice che è arrivato significa che ha raggiunto il player, quindi collisione
                        sound.playDie();
                        if (player.getFall())
                            sound.stopFall();
                        player.decreaseLives();
                        if (player.getLives() == 0) //se ha esaurito le vite il gioco finisce
                        {
                            player.setLives(3);
                            restart();
                            sound.stopBackground();
                            sound.playGameover();
                            graphic.drawYouDied(sound);
                            al_destroy_timer(timer);
                            al_destroy_event_queue(queue);
                            return 0;
                        }
                        else //altrimenti ricostruisce il livello
                        {
                            restart();
                            if (difficulty == 3)
                                loadMap(string("../Assets/Maps/level") + to_string(level) + ".txt");
                            break;
                        }
                    }
                    int x = path.back().x; //le cordinate da seguire
                    int y = path.back().y;
                    if (avaibleSpot(x, y)) //controllo la prossima posizione
                        i.update(map, holes, player, x, y);
                    handleUp(i);
                }
                delay = 0;
            }
            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            al_destroy_timer(timer);
            al_destroy_event_queue(queue);
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
            case ALLEGRO_KEY_M: // Cambia livello senza giocarlo
                restart();
                sound.stopBackground();
                return 1;
                break;
            case ALLEGRO_KEY_ESCAPE:
                close = true;
                break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            player.setFrame(player.getFrame() == 3 ? 3 : player.getFrame()); //setta i frame ad ogni giro
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
            if (player.getFall()) //se sta cadendo gestisci i vari casi
            {
                sound.playFall();
                player.setY(player.getY() + 5);
                if (map[((player.getY() + 5) / 20)][(player.getX() / 20)] == '#' || map[((player.getY() + 5) / 20)][(player.getX() / 20)] == 'H' || map[((player.getY() + 5) / 20)][(player.getX() / 20)] == '@')
                { //arriva ad un blocco e si ferma
                    player.setFall(false);
                    sound.stopFall();
                }
                if (map[((player.getY() - 18) / 20)][(player.getX() / 20)] == '-' && map[((player.getY()) / 20)][(player.getX() / 20)] == '-')
                { //arriva ad una corda e si ferma
                    player.setFall(false);
                    sound.stopFall();
                    player.setFrame(5);
                }
                if (map[((player.getY() - 18) / 20)][(player.getX() / 20)] == '-' && lastIsDown && map[((player.getY() + 5) / 20)][(player.getX() / 20)] != '#')
                {
                    player.setFall(true);
                    player.setFrame(4);
                }
            }
            if (!holes.empty())
            { //scandisce l'animazione della buca che si distrugge e ricrea
                for (list<HoleManager>::iterator i = holes.begin(); i != holes.end(); i++)
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
            if (coins == 0 && !stair) //ha raccolto tutte le monete e attiva la scala finale
            {
                sound.playStair();
                graphic.drawFinalLadder(map);
                stair = true;
            }
            if (player.getY() < 0)
            { //supera il livello
                sound.stopBackground();
                sound.playWin();
                restart();
                if (difficulty == 1)
                    player.setLives(player.getLives() + 1);
                al_destroy_timer(timer);
                al_destroy_event_queue(queue);
                return 1;
            }
            if (player.getY() > 340 || map[player.getY() / 20][player.getX() / 20] == '#')
            { //cade sotto la mappa oppure viene rinchiuso all'interno di un blocco
                sound.stopFall();
                sound.playDie();
                player.decreaseLives();
                if (player.getLives() == 0) // se le vite sono finite torna al menù
                {
                    player.setLives(3);
                    sound.stopBackground();
                    restart();
                    sound.playGameover();
                    graphic.drawYouDied(sound);
                    al_destroy_timer(timer);
                    al_destroy_event_queue(queue);
                    return 0;
                }
                else
                {
                    restart();
                    if (difficulty == 3)
                        loadMap(string("../Assets/Maps/level") + to_string(level) + ".txt");
                }
            }
            graphic.drawMap(map);
            graphic.drawEntity(&player);
            graphic.drawStats(coins, player.getLives(), level);
            for (auto i : enemies)
            {
                graphic.drawEntity(&i);
            }
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return -1;
}

bool GameManager::avaibleSpot(const int &y, const int &x)
{
    for (auto i : enemies)
    {
        if (x == i.getX() / 20 && y == i.getY() / 20)
            return false;
    }
    return true;
}

void GameManager::handleUp(Enemy &i)
{
    if (i.isInHole(holes, map, false)) //gestione animazione caduta nella buca
    {
        i.setFallen(i.getFallen() + 0.1); //serve per scandire i frame, il setMirrorY li alterna
        if (2.8 < i.getFallen() && i.getFallen() <= 2.9)
        {
            i.setFrame(3);
            i.setY(i.getY() - 3);
            i.setFall(false);
        }
        if (2.9 < i.getFallen() && i.getFallen() <= 3.0)
        {
            i.setY(i.getY() - 3);
            i.setMirrorY(true);
        }
        if (3.1 < i.getFallen() && i.getFallen() <= 3.2)
        {
            i.setY(i.getY() - 3);
            i.setMirrorY(false);
        }
        if (3.2 < i.getFallen() && i.getFallen() <= 3.3)
        {
            i.setY(i.getY() - 3);
            i.setMirrorY(true);
        }
        if (3.3 < i.getFallen() && i.getFallen() <= 3.4)
        {
            i.setY(i.getY() - 3);
            i.setMirrorY(false);
        }
        if (3.4 < i.getFallen() && i.getFallen() <= 3.5)
        {
            i.setY(i.getY() - 3);
            i.setMirrorY(true);
        }
        if (3.6 < i.getFallen())
        {
            //puo cominciare a risalire dal buco
            i.setFallen(0);
            i.setY(i.getY() - 2);
            //viene deciso dove farlo spwanare(destra o sinistra)
            if (player.getX() > i.getX() && map[(i.getY()) / 20][(i.getX() / 20) + 1] != '#' && avaibleSpot(i.getY() / 20, (i.getX() / 20) + 1))
            {
                i.setX(i.getX() + 20);
                if (map[(i.getY() / 20) + 1][(i.getX() / 20) - 1] == '}')
                {
                    map[(i.getY() / 20) + 1][(i.getX() / 20) - 1] = ' ';
                }
            }
            else if (player.getX() < i.getX() && map[(i.getY()) / 20][(i.getX() / 20) - 1] != '#' && avaibleSpot(i.getY() / 20, (i.getX() - 15) / 20))
            {
                i.setX(i.getX() - 15);
                if (map[(i.getY() / 20) + 1][(i.getX() + 15) / 20] == '}')
                {
                    map[(i.getY() / 20) + 1][(i.getX() + 15) / 20] = ' ';
                }
            }
            i.setFall(false);
        }
    }
}

void GameManager::restart()
{
    fill(keys, keys + 6, false);
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
        if (difficulty == 3)
            i.setRedHat(false);
    }
    for (auto i : holes)
    {
        if (!i.already)
            map[i.first][i.second] = '#';
    }
    holes.clear();
    if (difficulty == 3)
        coins = 0;
}

void GameManager::loadMap(string path)
{
    coins = 0;
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
        exit(-1);
    }
}

void GameManager::createEntities(const int &level)
{
    enemies.clear();
    if (level == 1)
    {
        player.setInitX(14 * 20);
        player.setInitY((14 * 20) + 18);
        Enemy e1(14 * 20, (9 * 20) + 18);
        Enemy e2(23 * 20, (6 * 20) + 18);
        Enemy e3(5 * 20, (6 * 20) + 18);
        map[e1.getY() / 20][(e1.getX() / 20) + 1] = 'M';
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
        map[e1.getY() / 20][(e1.getX() / 20) + 1] = 'M';
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
        map[e1.getY() / 20][(e1.getX() / 20) + 1] = 'M';
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
        map[e1.getY() / 20][(e1.getX() / 20) + 1] = 'M';
        enemies.push_back(e1);
        enemies.push_back(e2);
        enemies.push_back(e3);
    }
    else if (level == 5)
    {
        player.setInitX(12 * 20);
        player.setInitY((14 * 20) + 18);
        Enemy e1(0 * 20, (5 * 20) + 18);
        Enemy e2(19 * 20, (6 * 20) + 18);
        Enemy e3(27 * 20, (13 * 20) + 18);
        map[e1.getY() / 20][(e1.getX() / 20) + 1] = 'M';
        enemies.push_back(e1);
        enemies.push_back(e2);
        enemies.push_back(e3);
    }
}