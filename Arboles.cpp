#include "Arboles.h"

///CONSTRUCTOR / DESCTRUCTOR
Arbol::Arbol(sf::RenderWindow *window, int dirX1,int dirX2,sf::Texture *texture, sf::Texture *textureDEAD,int type){
    sprite.setTexture(*texture);
    sprite.setPosition( rand() % dirX2 + dirX1, -30.f - rand() %  (static_cast<int>(sprite.getGlobalBounds().height * 2) + 1));
                       //(window->getSize().x - static_cast<int>(sprite.getGlobalBounds().width)), 0.f - rand() %  (static_cast<int>(sprite.getGlobalBounds().height * 2) + 1));
    spriteDEAD.setTexture(*textureDEAD);
    setPoints(1);
    setHP(2);
    setDamage(1);
    switch(type){
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            break;

    }
}
Arbol::~Arbol(){
}


///GETS
sf::Sprite Arbol::getSprite(){
    if(checkDead())
        return spriteDEAD;
    return sprite;
}


///SETS
void Arbol::setSprite(sf::Texture *texture){
    sprite.setTexture(*texture,true);
}

void Arbol::setSpriteDEADPosition(float x,float y){
    spriteDEAD.setPosition(x,y);
}

///METHODS

void Arbol::moves(float movementSpeed){
    if(checkDead())
        spriteDEAD.move(0.f,movementSpeed);
    sprite.move(0.f,movementSpeed);
}

void Arbol::update(){

}

sf::FloatRect Arbol::getBounds(){
    if(checkDead()){
        return spriteDEAD.getGlobalBounds();
    }
    return sprite.getGlobalBounds();
}

void Arbol::draw(sf::RenderTarget& target, sf::RenderStates states)const{

}
