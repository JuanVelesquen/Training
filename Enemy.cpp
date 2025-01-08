#include "Enemy.h"

Boss::Boss(){
    texture.loadFromFile("Textures/Efectos/shot.png");
    textureTrail = new sf::Texture();
    textureTrail->loadFromFile("Textures/Efectos/rastros-tren2.png");
    shot.setSound("shots.ogg",2);
}
Boss::~Boss(){
    ///DELETE BULLETS
    for(auto *i: bullets){
        delete i;
    }
    for(auto *i: trail){
        delete i;
    }
    delete textureTrail;
}

///BULETS HANDLING
void Boss::cooldown(float speed){

    time =  clock.getElapsedTime();
    if(time >= sf::seconds(0.3f)){
        time = clock.restart();
        shot.playAudio();
        addBullets(speed);
    }

}
///ADD BULLETS
void Boss::addBullets(float speed){

        bullets.push_back(new Bullet(&texture,getSprite().getPosition().x,
                                               getSprite().getPosition().y,speed));
}
///DELETE BULLET
void Boss::deleteBullet(int index){
    bullets.erase(bullets.begin() + index);
    //std::cout<<"Size: "<<bullets.size()<<"\n";
}

///Bullets updated


void Boss::missileFired(){
    for (long long unsigned i = 0; i < bullets.size(); i++){
        bullets[i]->update();
    }
}
///CHECK BOUNDS FOR SPACESHIP AND DELETE BULLETS
void Boss::checkBounds(sf::RenderWindow *window){
    ///CHECK BOUNDS FOR Boss SPACESHIP
    if(getSprite().getPosition().x <= 0){
        setSpritePosition(0.f,getSprite().getPosition().y);
    }
    if(getSprite().getPosition().y <= 0){
        setSpritePosition(getSprite().getPosition().x,0.f);
    }
    if(getSprite().getPosition().x >= window->getSize().x - getSprite().getGlobalBounds().width){
        setSpritePosition(window->getSize().x - getSprite().getGlobalBounds().width,getSprite().getPosition().y);
    }
    if(getSprite().getPosition().y >= window->getSize().y - getSprite().getGlobalBounds().height){
        setSpritePosition(getSprite().getPosition().x,window->getSize().y - getSprite().getGlobalBounds().height);
    }

    ///DELETE MISSILE THAT ARE NO LONGER IN THE WINDOW
    for(long long unsigned i = 0; i < bullets.size(); i++){
        missileFired();
    }
     for(long long unsigned i = 0; i < bullets.size(); i++){
        if(bullets[i]->getSprite().getPosition().y + bullets[i]->getSprite().getGlobalBounds().height > window->getSize().y)
        {
            deleteBullet(i);
        }
    }

}

bool Boss::checkBulletBounds(sf::FloatRect playerBounds){
    for(long long unsigned i = 0; i < bullets.size();i++){
        if(bullets[i]->getSprite().getGlobalBounds().intersects(playerBounds)){
            deleteBullet(i);
            return true;
        }
    }
    return false;
}

void Boss::addTrail(){
    trailSpawnTimer = trailClock.getElapsedTime();
    if(trailSpawnTimer >= sf::seconds(0.1f)){
        trail.push_back(new Effects(textureTrail,getSprite().getPosition().x - textureTrail->getSize().x / 2,
                                               getSprite().getPosition().y));
        trailSpawnTimer = trailClock.restart();
    }
}
void Boss::checkTrailBounds(sf::RenderWindow *window,float speed){
    if(!trail.empty()){
        for(long long unsigned i = 0; i < trail.size();i++){
            trail[i]->update(speed);
        }

        for(long long unsigned i = 0; i < trail.size();i++){
            if(trail[i]->getSprite().getPosition().y > window->getSize().y)
            {
                trail.erase(trail.begin() + i);
                break;
            }
        }
    }
}

void Boss::updateTrail(sf::RenderWindow *window,float speed){
    if(getHP() > 0){
        addTrail();
        checkTrailBounds(window,speed);
    }
}

void Boss::updateBullets(float speed,sf::RenderWindow *window){
    cooldown(speed);
}

void Boss::update(sf::RenderWindow *window,float dt,float speed,sf::Vector2f playerPos){
    updateEntity(window,dt,speed,playerPos);
    moves(playerPos);
    updateBullets(speed,window);
    updateTrail(window,speed);
    checkBounds(window);
}
void Boss::reset(){
    resetEntity();
    for(long long unsigned i = 0; i < trail.size();i++){
            trail.erase(trail.begin() + i);
            i--;
            //std::cout<<"T size: "<<trail.size()<<"\n";
    }
    for (long long unsigned i = 0; i < bullets.size(); i++){
        deleteBullet(i);
        i--;

    }
    shot.endAudio();

}
void Boss::draw(sf::RenderTarget& target, sf::RenderStates states)const{

    for(long long unsigned i = 0;i < trail.size();i++){
        target.draw(trail[i]->getSprite(),states);
    }

    for(long long unsigned i = 0;i < bullets.size();i++){
        target.draw(bullets[i]->getSprite(),states);
    }

}
