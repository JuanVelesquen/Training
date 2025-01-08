#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

 #include <iostream>
#include <cstdlib>

 #include <SFML/Graphics.hpp>
 #include <SFML/Window.hpp>
 #include <SFML/System.hpp>
 #include <SFML/Audio.hpp>

 #include "Sound.h"


 enum btn_states{btn_idle = 0, btn_active};

class Button: public sf::Drawable{
private:

    sf::Sprite spriteIdle;
    sf::Sprite spriteActive;

    sf::Sprite currentSprite;
    btn_states state;

    int AnimationCounter;

    int type;

    Sound click;
public:
   Button();
    ~Button();

    void setButton(sf::Texture *textureIdle, sf::Texture *textureActive,sf::Vector2f location,int type);

    void setState(btn_states);
    void setOutlineColor();
    void setOutlineThickness();

    sf::Sprite getSprite();

    btn_states getState();

    void checkClick(sf::Vector2f mousePos);
    bool isPressed(bool MBreleased,sf::Vector2f mousePos);


    void update(sf::Vector2f mousePos);

    ///RENDER BUTTON
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // BUTTON_H_INCLUDED
