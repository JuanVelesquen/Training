#include "Obstaculos.h"

///CONSTRUCTOR / DESCTRUCTOR
Obstacles::Obstacles(){
    dead = false;
}
Obstacles::~Obstacles(){
}

///GETS

float Obstacles::getHP(){
    return hp;
}

float Obstacles::getHPMAX(){
    return hpMAX;
}

int Obstacles::getPoints(){
    return points;
}
float Obstacles::getDamage(){
    return damage;
}
bool Obstacles::getDead(){return dead;}
///SETS

void Obstacles::setHP(float hp){
    this->hp = hp;
}
void Obstacles::setHPMAX(float hpMAX){
    this->hpMAX = hpMAX;
}
void Obstacles::setDamage(float damage){
    this->damage = damage;
}
void Obstacles::setPoints(int points){
    this->points = points;
}
bool Obstacles::checkDead(){
    if(dead)
        return true;
    return false;
}

void Obstacles::setDead(bool d){dead=d;}

