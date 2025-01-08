#ifndef ENTIDAD_H_INCLUDED
#define ENTIDAD_H_INCLUDED

#include <vector>


#include "Configuracion.h"
#include "ArchivoConfiguracion.h"
#include "Sound.h"
class Entidad:public sf::Drawable{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect currentFrame;
    sf::Time animationTimer;
    sf::Clock animationClock;

    float movementSpeed;

    /// LIFE VARIABLE
    float hpMAX;
    float hp;

    ///SCORE VARIABLE
    float points;

    ///WEAPON
    float damage;

    ///TRAIN SOUND
    Sound sound;
    bool flag;
    ///
public:
    ///CONSTRUCTOR / DESCTRUCTOR
    Entidad();
    ~Entidad();

    //SETS
    void setDamage(float damage);
    void setSprite(sf::Texture texture);
    void setSpritePosition(float x,float y);
    void setMovementSpeed(float movementSpeed);
    void setHP(float HP);
    void setHPMAX(float HPMAX);
    void setPoints(float points);
    ///GETS
    float getDamage();
    sf::Sprite getSprite();
    sf::Vector2f getSpritePosition();
    float getMovementSpeed();
    float getHP();
    float getHPMAX();
    float getPoints();
    ///METHODS
    void moves(sf::Vector2f playerPosition);
    void initEnemy(float hp,float damage);

        ///JUGADOR ANIMATION SPRITE
    void animation();

     ///UPDATES
    void updateAudio();

    void updateEntity(sf::RenderWindow *window, float dt,float speed,sf::Vector2f playerPos);
    void initBoss();
    ///INTERSECTS OBSTACLES
    bool intersectsObstacles();
    void resetEntity();

private:
    void initTextures();
    void initAudio();



};

#endif // ENTIDAD_H_INCLUDED
