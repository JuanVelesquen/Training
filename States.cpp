#include "States.h"
///Constructor/Destructor
State::State(sf::RenderWindow* window,std::stack<State*> *states){
    this->window = window;
    this->states = states;
    this->quit = false;
}
State::~State(){
    window = nullptr;
    delete this->window;
}

const bool& State::getQuit(){
    return quit;
}

void State::updateInput(const float& dt,bool MBreleased){
}

void State::updateMousePosition(){
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}
