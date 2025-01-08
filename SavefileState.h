#ifndef SAVEFILESTATE_H_INCLUDED
#define SAVEFILESTATE_H_INCLUDED

#include "GameState.h"
#include "PlayerCreationState.h"
#include "Savefile.h"
#include "ArchivoSavefile.h"
#include "Button.h"

class SavefileState:public State{
private:
    std::map<const char*,sf::Texture*> mTextures;
    sf::Sprite background;

    sf::Sprite saveBorder;
    ///SAVE BUTTON
    Button btnSave[3];
    sf::Font font;

    sf::Text textPlayerName[3];
    int saveSpot;

    ///MEJORAS DEL JUGADOR
    sf::Sprite atrapaVacas[3];
    sf::Sprite locomotora[3];
    sf::Sprite carbonera[3];
    sf::Sprite orugaLocomotora[3];
    sf::Sprite orugaCarbonera[3];

    ///RELOJ
    sf::Sprite reloj[3];
    sf::Text textTimePlayed[3];

public:
    ///Constructor / Destructor
    SavefileState(sf::RenderWindow*, std::stack<State*>* states);
    virtual ~SavefileState();

    ///Methods

    void save();
    void updateUpgradesSprites();
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
    void initBackground();
    void initGUI();
};

#endif // SAVEFILESTATE_H_INCLUDED
