#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Entidad.h"
#include "Bullet.h"
#include "Effects.h"
#include "Sound.h"

class Boss:public Entidad{
    std::vector<Bullet*> bullets;
    sf::Texture texture;
    sf::Time time;
    sf::Clock clock;

    sf::Texture *textureTrail;

    std::vector<Effects*> trail;
    sf::Time trailSpawnTimer;
    sf::Clock trailClock;

    Sound shot;
public:
    Boss();
    ~Boss();

    ///METHODS


    void cooldown(float speed);
    void checkBounds(sf::RenderWindow *window);
    ///BULLETS
    void addBullets(float speed);
    void deleteBullet(int index);
    ///MISSILE IS SHOT
    void missileFired();
    void getBullet();

        ///CHECK
    void checkTrailBounds(sf::RenderWindow *window,float speed);
    bool checkBulletBounds(sf::FloatRect playerBounds);

    ///TRAIL TRACKS
    void addTrail();
    void updateTrail(sf::RenderWindow *window,float speed);
    void reset();

    ///UPDATE
    void updateBullets(float speed,sf::RenderWindow *window);
    void update(sf::RenderWindow *window,float dt,float speed,sf::Vector2f playerPos);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif // ENEMY_H_INCLUDED
