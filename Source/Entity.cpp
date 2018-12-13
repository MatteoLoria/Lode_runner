#include "../Headers/Entity.hpp"

Entity::Entity() {}
Entity::Entity(int x, int y):init_x(x),init_y(y),x(x),y(y){}
Entity::~Entity() {}
int Entity::getFrame(){return frame;}
int Entity::getInitX(){return init_x;}
int Entity::getInitY(){return init_y;}
int Entity::getX(){return x;}
int Entity::getY(){return y;}
void Entity::setX(int x) {this->x = x;}
void Entity::setY(int y) {this->y = y;}
void Entity::setFrame(int frame) {this->frame = frame;}
