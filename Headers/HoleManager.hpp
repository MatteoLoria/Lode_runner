#ifndef TRIPLE_H
#include <iostream>
#define TRIPLE_H
using namespace std;
class HoleManager
{
    friend ostream& operator<<(ostream &out,const HoleManager&);
    public:
        int first=0; //coordinata y
        int second=0; //coordinata x
        double third=0; //timer
        bool already=false; //se è già stato processato
        HoleManager(const int& ,const int& ,const double& ,const bool&);
        bool operator==(const HoleManager&);
};
#endif
