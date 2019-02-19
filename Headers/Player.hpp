/*
 @authors Matteo Notaro               &  Matteo Loria
 @github  https://github.com/MattNot     https://github.com/MatteoLoria

 19/02/2019
*/

#include "Entity.hpp"

#ifndef PLAYER_H
#define PLAYER_H
class Player : public Entity
{
    private:
        int lives=3;  //vite del player
        int points=0; //monete raccolte
    public:
        Player();
        Player(const int&, const int&, string[10]);
        int getLives();
        string getEntity();      //restituisce il nome dell'entità(player)
        void setLives(const int&);
        void decreaseLives();
        void increasePoints();
        int getPoints();
        void setPoints(const int&);
        bool dig(char[16][28], const bool&); //restituisce true se si può fare dig
};
#endif