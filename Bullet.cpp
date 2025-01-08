#include "Bullet.h"

///CONSTRUCTOR / DESTRUCTOR
Bullet::Bullet(sf::Texture* texture,float dirX,float dirY,float movementSpeed){
    sprite.setTexture(*texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2,sprite.getPosition().y);
    direcction.x = dirX;
    direcction.y = dirY;
    sprite.setPosition(dirX,dirY);
    this->movementSpeed = movementSpeed;
}
Bullet::~Bullet(){

}

///GETS
sf::Sprite Bullet::getSprite(){
    return sprite;
}

sf::Vector2f Bullet::getDirecction(){
    return direcction;
}

float Bullet::getMovementSpeed(){
    return movementSpeed;
}

///METHODS

void Bullet::update(){
    ///MOVEMENT
    sprite.move(0.f,movementSpeed);
}
