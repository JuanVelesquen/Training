#include "PlayerCreationState.h"

PlayerCreationState::PlayerCreationState(sf::RenderWindow* window, std::stack<State*>* states)
:State(window,states),
textBox(42,sf::Color::Black,true){
    initTextures();
    initGUI();
}

PlayerCreationState::PlayerCreationState(sf::RenderWindow* window, std::stack<State*>* states,int numeroJugador)
:State(window,states),
textBox(42,sf::Color::Black,true){
    this->numeroJugador = numeroJugador;
    initTextures();
    initGUI();
}

PlayerCreationState::~PlayerCreationState(){}

///INTIALIZE VARIABLES

void PlayerCreationState::initTextures(){
    ///BACKGROUND TEXTURE
    mTexture[0].loadFromFile("Textures/Background/training_menu.png");


   ///SAVE BUTTON
    mTexture[1].loadFromFile("Textures/CargarPartida/boton_partidaguardada_empty.png");

        ///ORUGA CARBONERA 3
    mTexture[2].loadFromFile("Textures/Extras/flecha.png");
}

void PlayerCreationState::initGUI(){
    ///INIT BACKGROUND
    mBackground.setTexture(mTexture[0]);
    mBackground.setScale(window->getSize().x / mBackground.getGlobalBounds().width,window->getSize().y / mBackground.getGlobalBounds().height);

    ///INIT GUI
    mSprite.setTexture(mTexture[1]);
    mSprite.setOrigin(mSprite.getGlobalBounds().width / 2,mSprite.getGlobalBounds().height / 2);
    mSprite.setPosition(window->getSize().x / 2, window->getSize().x / 3);

    ///INIT TEXT
    font.loadFromFile("Fonts/Minecraft.ttf");
    textName.setFont(font);
    textName.setCharacterSize(42);
    textName.setFillColor(sf::Color::Black);
    textName.setString("Name: ");
    textName.setPosition(mSprite.getPosition().x - mSprite.getGlobalBounds().width / 2.1, mSprite.getPosition().y - mSprite.getGlobalBounds().height / 3);

    textBox.setLimit(true,8);
    textBox.setPosition(textName.getPosition().x + textName.getGlobalBounds().width , mSprite.getPosition().y - mSprite.getGlobalBounds().height / 3);


    ///INIT BUTTON
    nextArrow.setButton(&mTexture[2],&mTexture[2],sf::Vector2f(mSprite.getPosition().x + mSprite.getGlobalBounds().width / 2.5, mSprite.getPosition().y - mSprite.getGlobalBounds().height / 4),1);
}

void PlayerCreationState::save(){
    Savefile objSave;
    ArchivoSavefile arkSave("savefile.dat");
    objSave = arkSave.leerRegistro(numeroJugador);
    objSave.setNombre(textBox.getText().c_str());
    arkSave.modificarRegistro(objSave,numeroJugador);
    std::cout<<"Nombre: "<<textBox.getText().c_str();
}

///METHODS


/// CHECK IF WE POP THE STACK
void PlayerCreationState::checkForQuit(bool MBreleased){

}

///WE POP THE STACK
void PlayerCreationState::endState(){
    this->quit = true;
}

///UPDATE
void PlayerCreationState::updateGUI(){
    textBox.setSelected(true);
}

void PlayerCreationState::updateButtons(bool MBreleased){
    nextArrow.update(mousePosView);
    if(nextArrow.isPressed(MBreleased,mousePosView)){
        save();
        this->endState();
        states->push(new GameState(window,states,numeroJugador));
    }
}

void PlayerCreationState::updateInput(const float& dt, bool MBreleased){
    this->checkForQuit(MBreleased);
}

void PlayerCreationState::update(const float& dt,bool MBreleased,sf::Event event){
    if(event.type == sf::Event::TextEntered)
        textBox.typedOn(event);
    this->updateMousePosition();
    this->updateInput(dt,MBreleased);
    this->updateButtons(MBreleased);
    this->updateGUI();
}


///RENDER
///RENDER TEXT
void PlayerCreationState::renderGUI(){
    window->draw(mSprite);
    window->draw(textName);
    window->draw(textBox);
    window->draw(nextArrow);
}

void PlayerCreationState::renderButtons(){

}


///RENDER MAIN
void PlayerCreationState::render(sf::RenderTarget *target){
    if(!target)
        target = this->window;

    target->draw(mBackground);
    renderButtons();
    renderGUI();
}
