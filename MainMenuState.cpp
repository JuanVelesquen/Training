#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
:State(window,states),
mainMenuMusic(){
    initTextures();
    initBackground();
    initButtons();
    initAudio();
}

MainMenuState::~MainMenuState(){
    for(auto &i : mTextures){
        delete i.second;
    }
}

///INTIALIZE VARIABLES
void MainMenuState::initAudio(){
    ///Audio
    mainMenuMusic.setSound("musicaMenu.ogg",1);
    mainMenuMusic.playAudio();
}
void MainMenuState::initTextures(){
    ///TEXTURES

    ///BACKGROUND TEXTURE
     mTextures["BACKGROUND"] = new sf::Texture();
    mTextures["BACKGROUND"]->loadFromFile("Textures/Background/training_menu.png");


    ///BUTTONS TEXTURES

    ///START BUTTON

    ///START BUTTON IDLE
    mTextures["START_IDLE"] = new sf::Texture();
    mTextures["START_IDLE"]->loadFromFile("Textures/botones/start1.png");

    ///START BUTTON ACTIVE
    mTextures["START_ACTIVE"] = new sf::Texture();
    mTextures["START_ACTIVE"]->loadFromFile("Textures/botones/start2.png");

     ///OPTIONS BUTTON

    ///OPTIONS BUTTON IDLE
    mTextures["OPTION_IDLE"] = new sf::Texture();
    mTextures["OPTION_IDLE"]->loadFromFile("Textures/botones/config1.png");

    ///OPTIONS BUTTON ACTIVE
    mTextures["OPTION_ACTIVE"] = new sf::Texture();
    mTextures["OPTION_ACTIVE"]->loadFromFile("Textures/botones/config2.png");

    ///QUIT BUTTON

    ///QUIT BUTTON IDLE
    mTextures["QUIT_IDLE"] = new sf::Texture();
    mTextures["QUIT_IDLE"]->loadFromFile("Textures/botones/quit1.png");

    ///QUIT BUTTON ACTIVE
    mTextures["QUIT_ACTIVE"] = new sf::Texture();
    mTextures["QUIT_ACTIVE"]->loadFromFile("Textures/botones/quit2.png");

    ///SCORE BUTTON

    ///SCORE BUTTON IDLE
    mTextures["SCORE_IDLE"] = new sf::Texture();
    mTextures["SCORE_IDLE"]->loadFromFile("Textures/botones/score1.png");

    ///LEADERBOARD BUTTON ACTIVE
    mTextures["SCORE_ACTIVE"] = new sf::Texture();
    mTextures["SCORE_ACTIVE"]->loadFromFile("Textures/botones/score2.png");

}

void MainMenuState::initBackground(){
    background.setTexture(*mTextures["BACKGROUND"]);
    background.setScale(window->getSize().x / background.getGlobalBounds().width,window->getSize().y / background.getGlobalBounds().height);
}

void MainMenuState::initButtons(){
    ///START BUTTON
    btnStart.setButton(mTextures["START_IDLE"], mTextures["START_ACTIVE"], sf::Vector2f(window->getSize().x / 2 ,window->getSize().y / 3),0);

    ///OPTIONS BUTTON
    btnOptions.setButton(mTextures["OPTION_IDLE"], mTextures["OPTION_ACTIVE"], sf::Vector2f(window->getSize().x / 2, btnStart.getSprite().getPosition().y * 1.8),0);

    ///QUIT BUTTON
    btnQuit.setButton(mTextures["QUIT_IDLE"], mTextures["QUIT_ACTIVE"],sf::Vector2f(btnStart.getSprite().getPosition().x,btnStart.getSprite().getPosition().y * 1.8),0);

    ///SCORE BUTTON
    btnScore.setButton(mTextures["SCORE_IDLE"], mTextures["SCORE_ACTIVE"],sf::Vector2f(btnStart.getSprite().getPosition().x + btnStart.getSprite().getGlobalBounds().width ,btnStart.getSprite().getPosition().y * 1.8),0);
}

///METHODS

/// CHECK IF WE POP THE STACK
void MainMenuState::checkForQuit(bool MBreleased){
    if(btnQuit.isPressed(MBreleased,mousePosView))
        this->quit = true;

}

///WE POP THE STACK
void MainMenuState::endState(){
    this->quit = true;
}

///UPDATE
void MainMenuState::updateAudio(){
    mainMenuMusic.update();
}
void MainMenuState::updateButtons(bool MBreleased){
    btnStart.update(mousePosView);
    if(btnStart.isPressed(MBreleased,mousePosView))
    {
        mainMenuMusic.endAudio();
        states->push(new SavefileState(window,states));


    }
    btnQuit.update(mousePosView);
    if(btnQuit.isPressed(MBreleased,mousePosView))
    {
        endState();
    }
     btnOptions.update(mousePosView);
    if(btnOptions.isPressed(MBreleased,mousePosView))
    {
        states->push(new Options(window,states));
    }
    btnScore.update(mousePosView);
    if(btnScore.isPressed(MBreleased,mousePosView))
    {
        states->push(new Score(window,states));
    }
}

void MainMenuState::updateInput(const float& dt,bool MBreleased){
    this->checkForQuit(MBreleased);
}

void MainMenuState::update(const float& dt,bool MBreleased,sf::Event event){
    this->updateMousePosition();
    this->updateInput(dt,MBreleased);
    this->updateAudio();
    this->updateButtons(MBreleased);

}


///RENDER

///RENDER BUTTONS
void MainMenuState::renderButtons(){
    window->draw(btnStart);
    window->draw(btnQuit);
    window->draw(btnOptions);
    window->draw(btnScore);
}

///RENDER MAIN
void MainMenuState::render(sf::RenderTarget *target){
    if(!target)
        target = this->window;

    target->draw(background);
    renderButtons();
}
