#ifndef EFFECTS_H_INCLUDED
#define EFFECTS_H_INCLUDED

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
class Effects{
private:
    sf::Sprite sprite;
    sf::Texture* texture;
    sf::Vector2f direcction;
public:
    ///CONSTRUCTOR / DESTRUCTOR
    Effects(sf::Texture* texture,float dirX,float dirY);
    virtual ~Effects();
    ///SETS

    ///GETS
    sf::Sprite getSprite();
    sf::Vector2f getDirecction();

    ///METHODS
    void update(float movementSpeed);


};

#endif // EFFECTS_H_INCLUDED
