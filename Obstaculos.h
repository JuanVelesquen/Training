#ifndef OBSTACULOS_H_INCLUDED
#define OBSTACULOS_H_INCLUDED

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Obstacles{
private:

    float hp;
    float hpMAX;
    float damage;
    int points;
    bool dead;
public:
    ///CONSTRUCTOR / DESCTRUCTOR
    Obstacles();
    ~Obstacles();

    float getHP();
    float getHPMAX();
    float getDamage();
    ///GETS();
    int getPoints();
    bool getDead();
    ///SETS
    void setDamage(float damage);
    void setHP(float hp);
    void setHPMAX(float hpMAX);
    void setPoints(int points);
    void setDead(bool d);
    ///METHODS

    bool checkDead();
    virtual sf::FloatRect getBounds() = 0;
};

#endif // OBSTACULOS_H_INCLUDED
