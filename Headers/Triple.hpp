#ifndef TRIPLE_H
#include <iostream>
#define TRIPLE_H
using namespace std;
class Triple
{
    friend ostream& operator<<(ostream &out,const Triple&);
    public:
        int first=0;
        int second=0;
        double third=0;
        Triple(int,int,double);
        bool operator==(Triple);
};
#endif
