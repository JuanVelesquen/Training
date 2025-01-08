#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED

#include "Obstaculos.h"

enum treeTypes{
    secos,
    pinos,
    robles
};

class Arbol: public Obstacles,public sf::Drawable{
private:
    sf::Sprite sprite;
    sf::Sprite spriteDEAD;
    treeTypes treeTypes;


public:
    ///CONSTRUCTOR / DESCTRUCTOR
    Arbol(sf::RenderWindow *window,int dirX1,int dirX2, sf::Texture *texture, sf::Texture *textureDEAD,int type);
    ~Arbol();
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

#endif // ARBOLES_H_INCLUDED
