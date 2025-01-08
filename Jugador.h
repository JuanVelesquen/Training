#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <vector>

#include "Effects.h"
#include "Configuracion.h"
#include "ArchivoConfiguracion.h"
#include "Sound.h"
class Jugador:public sf::Drawable{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect currentFrame;
    sf::Time animationTimer;
    sf::Clock animationClock;

    sf::Texture *textureTrail;

    std::vector<Effects*> trail;
    sf::Time trailSpawnTimer;
    sf::Clock trailClock;

    float movementSpeed;

    float carbon;
    float carbonIncrement;
    float presion;
    float presionIncrement;
    float presionMAX;
    float presionCheck;

    sf::Time pressureLevelTime;
    sf::Clock pressureLevelClock;

    sf::Time UnderNormalPressureLevelTime;
    sf::Clock UnderNormalPressureLevelClock;

    ///Jugador LIFE VARIABLE
    float hpMAX;
    float hp;

    //
    int mejoras[5];
    int currentLevel;

    ///Jugador SCORE VARIABLE
    int score;
    int money;

    /// Jugador WEAPON
    bool kill;
    int damage;

    ///TRAIN SOUND
    Sound trainSound;
    bool flag;
    ///
public:
    ///CONSTRUCTOR / DESCTRUCTOR
    Jugador();
    ~Jugador();

    //SETS
    void setDamage(int damage);
    void setSprite(sf::Texture texture);
    void setSpritePosition(float x,float y);
    void setMovementSpeed(float movementSpeed);
    void setMoney(int money);
    void setMejoras(int mejora,int indice);
    void setCarbon(float carbon);
    void setCarbonIncrement(float carbonIncrement);
    void setCurrentLevel(int level);
    void setPresion(float presion);
    void setPresionIncrement(float presionIncrement);
    void setPresionMAX(float presionMAX);
    void setPresionCheck(float presionCheck);
    void setHP(float HP);
    void setHPMAX(float HPMAX);
    void setScore(int points);
    void setVapor(sf::Sound sound);
    void setKill(bool kill);
    ///GETS
    int getDamage();
    sf::Sprite getSprite();
    float getMovementSpeed();
    int getMoney();
    int getMejoras(int indice);
    float getCarbon();
    float getCarbonIncrement();
    int getCurrentLevel();
    float getPresion();
    float getPresionIncrement();
    float getPresionMAX();
    float getPresionCheck();
    const sf::FloatRect getBounds() const;
    float getHP();
    float getHPMAX();
    int getScore();
    sf::Sound getVapor();
    bool getKill();
    ///METHODS

    ///CHECK
    void checkTrailBounds(sf::RenderWindow *window);
    void checkPressureLevel();

    ///TRAIL TRACKS
    void addTrail();
    ///JUGADOR MOVES
    void moves(float dt);
    ///JUGADOR ANIMATION SPRITE
    void animation();

     ///UPDATES JUGADOR
    void updateAudio();
    void updateTrail(sf::RenderWindow *window);
    void updateVariables();
    void update(sf::RenderWindow *window, float dt);

    ///RENDER JUGADOR
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    ///INTERSECTS OBSTACLES
    bool intersectsObstacles();
    void reset();
private:
    void initTextures();
    void initVariables();
    void initAudio();
};


#endif // JUGADOR_H_INCLUDED
