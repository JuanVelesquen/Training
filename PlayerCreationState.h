#ifndef PLAYERCREATIONSTATE_H_INCLUDED
#define PLAYERCREATIONSTATE_H_INCLUDED

#include "SavefileState.h"
#include "OptionsState.h"
#include "Configuracion.h"
#include "ArchivoConfiguracion.h"
#include "TextBox.h"
#include "Button.h"
#include "Sound.h"

class PlayerCreationState:public State{
private:
    TextBox textBox;

    sf::Texture mTexture[3];
    sf::Sprite mSprite;
    sf::Sprite mBackground;

    sf::Font font;
    sf::Text textName;
    int numeroJugador;

    Button nextArrow;
public:
    ///Constructor / Destructor
    PlayerCreationState(sf::RenderWindow*, std::stack<State*>* states);
    PlayerCreationState(sf::RenderWindow*, std::stack<State*>* states,int numeroJugador);
    virtual ~PlayerCreationState();

    ///Methods

    void save();

    void updateButtons(bool MBreleased);
    void renderButtons();

    void checkForQuit(bool MBreleased);
    void endState();
    void updateGUI();

    void updateInput(const float& dt, bool MBreleased);
    void update(const float& dt,bool MBreleased, sf::Event event);

    void renderGUI();
    void render(sf::RenderTarget *target = nullptr);

private:
    void initSavefiles();
    void initTextures();
    void initGUI();
};


#endif // PLAYERCREATIONSTATE_H_INCLUDED
