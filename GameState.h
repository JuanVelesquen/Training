#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "Jugador.h"
#include "Enemy.h"
#include "Arboles.h"
#include "Piedras.h"
#include "Savefile.h"
#include "ArchivoSavefile.h"
#include "Configuracion.h"
#include "ArchivoConfiguracion.h"
#include "States.h"
#include "Button.h"
struct spawnTimer{
    float spawnTimer;
    float spawnTimerMAX;
    float spawnTimerIncrement;
};

class GameState:public State{
private:
    ///TEXTURAS
    std::map<const char*,sf::Texture*> mTextures;

    ///HUD
    sf::Sprite meterBase;
    sf::Sprite needleMeter;
    sf::Font font;
    sf::Text textPoints;
    sf::Text textArbolesHarvested;
    sf::Text textPiedrasHarvested;
    sf::Text textDistance;
    sf::Text textSubtotal;
    sf::Text textPlayerMoney;
    sf::Text textTotal;
    sf::Text textUpgrades;

    ///VARIABLES HUD
    int distance;
    int arbolesHarvested;
    int piedrasHarvested;
    int total;
    ///GAMEOVER


    Button playAgain;
    Button returnMenu;
    Button BuyUpgrade;

    ///WORLD MAP
    sf::Sprite worldBackground;
    sf::Sprite pauseSprite;

    ///CHECKBOUNDS
    sf::Sprite checkboundLeft;
    sf::Sprite checkboundRight;


    ///MEJORAS DEL JUGADOR
    sf::Sprite atrapaVacas;
    sf::Sprite locomotora;
    sf::Sprite carbonera;
    sf::Sprite orugaLocomotora;
    sf::Sprite orugaCarbonera;
    Button botonMejoras[5];
    int btnMejoraPresionado;
    int upgradesPrice[5][2];
    bool flagUpgradeText;
    ///GAME OBJECTS

    ///JUGADOR PRINCIPAL
    int numeroJugador;
    Jugador jugador;
    sf::Clock clock;
    sf::Time timePlayed;

    ///OBSTACULOS

    std::vector<Piedra*> piedras;
    std::vector<Arbol*> arboles;

    ///ENEMIES

    Boss enemy;

    ///SPAWN TIMER DE LOS OBSTACULOS
    spawnTimer spawnTimerArboles;
    spawnTimer spawnTimerPiedras;

    ///MUSIC BACKGROUND
    Sound arcadeMusic;

public:
    ///Constructor / Destructor
    GameState(sf::RenderWindow*, std::stack<State*>* states);
    GameState(sf::RenderWindow*, std::stack<State*>* states,int jugadorJugando);
    virtual ~GameState();

    ///Methods

    ///RESET
    void reset();
    void resetObstacles();
    void resetHUD();

    ///SAVING MECHANICS
    void loadFile();
    void saveFile();

    ///BACKGROUND
    void backgroundLoop();

    ///UPDATE

    void updateObstacles();
    void checkObstaclesBounds();
    void moveObstacles();
    void respawnObstacles();

    void updatePlayer(float dt);
    void checkBoundsPlayer();
    void buyUpgrades();
    void setPlayerUpgrades();

    void checkForQuit(bool MBreleased);
    void endState();

    void checkBoundsEnemy();
    void checkBoundBullets();

    void updateEnemy(sf::RenderWindow *window,float dt);
    void updateUpgradeTextures();
    void updateUpgradedButtons(int btn);
    void updateButtons(bool MBreleased);
    void updateHUD(float dt);
    void updatePauseMenu();
    void updateInput(const float& dt,bool MBrealeased);
    void update(const float& dt,bool MBrealeased, sf::Event event);


    ///RENDER
    void renderUpgradedButtons();
    void renderPauseMenu();
    void renderBackground();
    void renderHUD();

    void render(sf::RenderTarget *target = nullptr);
private:
    ///INTIALIZE TEXTURES
    void initTextures();
    ///INTIALIZE BACKGROUND
    void initWorldBackground();
    ///INTIALIZE SPAWN TIMERS
    void initSpawnTimers();
    ///INTIALIZE RIGHT AND LEFT CHECKBOUND
    void initCheckBounds();
    ///INTIALIZE HUD
    void initHud();
    ///INTIALIZE PAUSE AND GAME OVER MENU
    void initPauseMenu();
    ///INTIALIZE UPGRADE TEXTURES
    void initUpgradesTextures();
    ///INTIALIZE PAUSE MENU UPGRADE BUTTONS
    void initUpgradesButtons();
    ///INTITALIZE PLAYER STATS
    void initPlayerVariables();
    ///INTIALIZE ENEMY
    void initEnemy();
};

#endif // GAMESTATE_H_INCLUDED
