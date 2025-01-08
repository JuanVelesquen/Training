#include "Game.h"
///Constructor
Game::Game()
:window(sf::VideoMode(816,624),"Training",sf::Style::Titlebar | sf::Style::Close){
    initWindow();
    initStates();
}
///Destructor
Game::~Game(){
    while(!states.empty()){
        delete this->states.top();
        states.pop();
    }
}

///Intialize window settings
void Game::initWindow(){
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    window.setKeyRepeatEnabled(false);
    keyReleased = true;
}

///Intialize GameState
void Game::initStates(){
    states.push(new MainMenuState(&window,&states));
}

void Game::endApplication(){
    std::cout<<"Ending Application"<<"\n";
    window.close();
}

///Update SFMl pollEvent
void Game::updateSFMLEvents(){
    sf::Event event;
    inputedEvent = event;
    while (window.pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                MBreleased = true;
                break;
            case sf::Event::MouseButtonPressed:
                MBreleased = false;
                break;
            case sf::Event::KeyReleased:
                keyReleased = true;
                break;
            case sf::Event::KeyPressed:
                keyReleased = false;
                break;
            case sf::Event::TextEntered:
                inputedEvent = event;
                break;
            default:
                break;
        }
    }
}

///Updates the dt variable with the time it takes to update and render on frame
void Game::updateDT(){
    dt = dtClock.restart().asSeconds();
    //std::cout<<dt<<"\n";
}

void Game::update(){
    updateSFMLEvents();

    if(!states.empty())
    {
        states.top()->update(dt,MBreleased,inputedEvent);
        if(states.top()->getQuit()){
            if(keyReleased){
                states.top()->endState();
                delete this->states.top();
                states.pop();
            }
        }
    }else{
      endApplication();
    }
}
void Game::render(){
    ///Clear old frames
    window.clear();
    ///Draw new frames
    if(!states.empty())
        states.top()->render();
    ///Display frames to the window
    window.display();
}
void Game::run(){
    while (window.isOpen())
    {
        updateDT();
        update();
        render();
    }
}
