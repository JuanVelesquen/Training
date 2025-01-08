#include "Piedras.h"

///CONSTRUCTOR / DESCTRUCTOR
Piedra::Piedra(sf::RenderWindow *window, float dirX1, float dirX2, sf::Texture *texture,sf::Texture *textureDEAD,int type){
    sprite.setTexture(*texture);
    sprite.setPosition(rand() % static_cast<int>(dirX2) + dirX1, 0.f - rand() %  (static_cast<int>(sprite.getGlobalBounds().height * 2) + 1));
    spriteDEAD.setTexture(*textureDEAD);
    setPoints(5);
    setHP(3);
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
Piedra::~Piedra(){
}


///GETS
sf::Sprite Piedra::getSprite(){
    if(checkDead())
        return spriteDEAD;
    return sprite;
}


///SETS
void Piedra::setSprite(sf::Texture *texture){
    sprite.setTexture(*texture,true);
}

void Piedra::setSpriteDEADPosition(float x,float y){
    spriteDEAD.setPosition(x,y);
}

///METHODS

void Piedra::moves(float movementSpeed){
    if(checkDead())
        spriteDEAD.move(0.f,movementSpeed);
    sprite.move(0.f,movementSpeed);
}

void Piedra::update(){

}

sf::FloatRect Piedra::getBounds(){
    if(checkDead())
        return spriteDEAD.getGlobalBounds();
    return sprite.getGlobalBounds();
}

void Piedra::draw(sf::RenderTarget& target, sf::RenderStates states)const{

}
