/*
 @authors Matteo Notaro               &  Matteo Loria
 @github  https://github.com/MattNot     https://github.com/MatteoLoria

 19/02/2019
*/

#include "../Headers/HoleManager.hpp"

HoleManager::HoleManager(const int &first, const int &second, const double &third, const bool &already)
{
    this->first = first;
    this->second = second;
    this->third = third;
    this->already = already;
}

bool HoleManager::operator==(const HoleManager &t)
{
    if (t.first == first && t.second == second && t.third == third && t.already == already)
        return true;
    return false;
}

ostream &operator<<(ostream &out, const HoleManager &t)
{
    out << t.first << t.second << t.third << endl;
    return out;
}