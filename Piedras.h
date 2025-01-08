#ifndef PIEDRAS_H_INCLUDED
#define PIEDRAS_H_INCLUDED

#include "Obstaculos.h"
enum types{
        normales,
        cristalRojo,
        cristalAzul,
        cristalVioleta
};

class Piedra: public Obstacles,public sf::Drawable{
private:
    sf::Sprite sprite;
    sf::Sprite spriteDEAD;
    types rockTypes;
public:
    ///CONSTRUCTOR / DESCTRUCTOR
    Piedra(sf::RenderWindow *window,float dirX1,float dirX2, sf::Texture *texture, sf::Texture *textureDEAD,int type);
    ~Piedra();
    ///GETS
    sf::Sprite getSprite();
    ///SETS
    void setSprite(sf::Texture *texture);
    void setSpriteDEADPosition(float x,float y);
    ///METHODS

    void moves(float movementSpeed);

    void update();

    sf::FloatRect getBounds();

    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};


#endif // PIEDRAS_H_INCLUDED
