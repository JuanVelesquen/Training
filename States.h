#ifndef STATES_H_INCLUDED
#define STATES_H_INCLUDED

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class State{
protected:
    std::stack<State*> *states;
    std::vector<sf::Texture> textures;
    sf::RenderWindow* window;
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

public:
    ///Constructor / Destructor
    State(sf::RenderWindow*, std::stack<State*>* states);
    virtual ~State();
    ///Methods
    const bool& getQuit();
    virtual void endState() = 0;
    virtual void updateMousePosition();
    virtual void updateInput(const float& dt, bool MBreleased) = 0;
    virtual void checkForQuit(bool MBreleased) = 0;
    virtual void update(const float& dt, bool MBrealeased,sf::Event event)  = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

#endif // STATES_H_INCLUDED
