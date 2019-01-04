#include "../Headers/Quadruple.hpp"

Quadruple::Quadruple(int first, int second, double third, bool already)
{
    this->first = first;
    this->second = second;
    this->third = third;
    this->already = already;
}

bool Quadruple::operator==(Quadruple t)
{
    if (t.first == first && t.second == second && t.third == third && t.already == already)
        return true;
    return false;
}
ostream &operator<<(ostream &out, const Quadruple &t)
{
    out << t.first << t.second << t.third << endl;
    return out;
}