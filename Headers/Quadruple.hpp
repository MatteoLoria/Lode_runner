#ifndef TRIPLE_H
#include <iostream>
#define TRIPLE_H
using namespace std;
class Quadruple
{
    friend ostream& operator<<(ostream &out,const Quadruple&);
    public:
        int first=0;
        int second=0;
        double third=0;
        bool already=false;
        Quadruple(int,int,double,bool);
        bool operator==(const Quadruple&);
};
#endif
