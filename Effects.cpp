#include "Effects.h"

///CONSTRUCTOR / DESTRUCTOR
Effects::Effects(sf::Texture *texture,float dirX,float dirY){
    sprite.setTexture(*texture);
    direcction.x = dirX;
    direcction.y = dirY;
    sprite.setPosition(dirX,dirY);
}
Effects::~Effects(){

}

///GETS
sf::Sprite Effects::getSprite(){
    return sprite;
}

sf::Vector2f Effects::getDirecction(){
    return direcction;
}

///METHODS

void Effects::update(float movementSpeed){
    ///MOVEMENT
    sprite.move(0.f,(movementSpeed));
}

