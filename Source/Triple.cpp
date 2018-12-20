#include "../Headers/Triple.hpp"

Triple::Triple(int first,int second, double third){
    this->first = first;
    this->second = second;
    this->third = third;
}

bool Triple::operator==(Triple t){
    if(t.first == first && t.second == second && t.third == third)
        return true;
    return false;
}
ostream& operator<<(ostream& out, const Triple& t){
    out<<t.first<<t.second<<t.third<<endl;
    return out;
}