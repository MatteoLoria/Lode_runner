#include "../Headers/Entity.hpp"

Entity::Entity() {}
Entity::Entity(int x, int y):init_x(x),init_y(y),x(x),y(y){}
int Entity::getFrame(){return frame;}
int Entity::getInitX(){return init_x;}
int Entity::getInitY(){return init_y;}
int Entity::getX(){return x;}
int Entity::getY(){return y;}
bool Entity::getMirrorX(){return mirrorX;}
bool Entity::getMirrorY(){return mirrorY;}
bool Entity::getMirrorRope(){return mirrorRope;}
bool Entity::getFall(){return isFalling;}
void Entity::setMirrorX(bool mirrorX){this->mirrorX = mirrorX;}
void Entity::setMirrorY(bool mirrorY){this->mirrorY = mirrorY;}
void Entity::setMirrorRope(bool mirrorRope){this->mirrorRope = mirrorRope;}
void Entity::setFall(bool isFalling){this->isFalling = isFalling;}
void Entity::setX(int x) {this->x = x;}
void Entity::setY(int y) {this->y = y;}
void Entity::setFrame(int frame) {this->frame = frame;}

