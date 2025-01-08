#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "MainMenuState.h"
#include "Button.h"

class Game{
private:
    sf::RenderWindow window;
    sf::Clock dtClock;
    float dt;
    bool MBreleased;
    bool keyReleased;
    sf::Event inputedEvent;
    std::stack<State*> states;
public:
    ///Constructor/Destructor
    Game();
    ~Game();
    ///Methods

    ///END APPLICATION
    void endApplication();

    ///CORE
    void run();


    ///UPDATE
    void updateDT();
    void update();

    ///RENDER
    void render();
private:
    void updateSFMLEvents();
    void initWindow();
    void initStates();
};

#endif // GAME_H_INCLUDED
