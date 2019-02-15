#ifndef TRIPLE_H
#include <iostream>
#define TRIPLE_H
using namespace std;
class HoleManager
{
    friend ostream& operator<<(ostream &out,const HoleManager&);
    public: //are we sure?
        int first=0;
        int second=0;
        double third=0;
        bool already=false;
        HoleManager(const int& ,const int& ,const double& ,const bool&);
        bool operator==(const HoleManager&);
};
#endif
