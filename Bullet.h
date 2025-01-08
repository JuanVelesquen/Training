#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

#include <SFML/graphics.hpp>
#include <SFML/window.hpp>
#include <SFML/system.hpp>
#include <SFML/audio.hpp>

class Bullet{
private:
    sf::Sprite sprite;
    sf::Texture* texture;
    sf::Vector2f direcction;
    float movementSpeed;
    float windowSizey;
public:
    ///CONSTRUCTOR / DESTRUCTOR
    Bullet(sf::Texture* texture,float dirX,float dirY,float movementSpeed);
    virtual ~Bullet();
    ///SETS

    ///GETS
    sf::Sprite getSprite();
    sf::Vector2f getDirecction();
    float getMovementSpeed();

    ///METHODS
    void update();


};

#endif // BULLET_H_INCLUDED
