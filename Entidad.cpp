#include "Entidad.h"

Entidad::Entidad(){
    initTextures();
    initAudio();
}
Entidad::~Entidad(){

}
void Entidad::initTextures(){
    texture.loadFromFile("Textures/Tren/Enemy-spritesheet.png");
    sprite.setTexture(texture);
    currentFrame = sf::IntRect(0,0,37,143);
    sprite.setTextureRect(currentFrame);
    sprite.setPosition(400.f,-50.f);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height);


}

void Entidad::initEnemy(float hp,float damage){
    this->hpMAX = hp;
    this->hp = this->hpMAX;
    flag = false;
    this->damage = damage;
}

void Entidad::initAudio(){
    sound.setSound("vaporTren2.wav",2);
}
///GETS

sf::Sprite Entidad::getSprite(){
    return sprite;
}

float Entidad::getMovementSpeed(){
    return movementSpeed;
}
float Entidad::getHP(){
    return hp;
}

float Entidad::getHPMAX(){
    return hpMAX;
}

float Entidad::getPoints(){
    return points;
}
float Entidad::getDamage(){
    return damage;
}

///SETS
void Entidad::setSpritePosition(float x,float y){
    sprite.setPosition(x,y);
}
void Entidad::setMovementSpeed(float movementSpeed){
    this->movementSpeed = movementSpeed;
}
void Entidad::setHP(float hp){
    this->hp = hp;
}
void Entidad::setHPMAX(float hpMAX){
    this->hpMAX = hpMAX;
}
void Entidad::setDamage(float damage){
    this->damage = damage;
}
void Entidad::setPoints(float points){
    this->points = points;
}

///METHODS
void Entidad::resetEntity(){
    sprite.setPosition(450.f,-50.f);
}
void Entidad::moves(sf::Vector2f playerPosition){
    sf::Vector2f movement(0.f,0.f);
    if(playerPosition.x > sprite.getPosition().x){
        movement.x += 1;
    }

    if(playerPosition.x < sprite.getPosition().x){
        movement.x -= 1;
    }

    if(sprite.getPosition().y - sprite.getGlobalBounds().height < 100)
        movement.y += 2;
    sprite.move(movement);
}

void Entidad::animation(){
    animationTimer = animationClock.getElapsedTime();
    if(animationTimer >= sf::seconds(0.2f)){
        currentFrame.left += 37;
        if(currentFrame.left >= 148.f){
            currentFrame.left = 0;
        }
        animationTimer = animationClock.restart();
        sprite.setTextureRect(currentFrame);
    }
}



void Entidad::updateEntity(sf::RenderWindow *window, float dt,float speed,sf::Vector2f playerPos){
    animation();
}

