#ifndef MAINMENUSTATE_H_INCLUDED
#define MAINMENUSTATE_H_INCLUDED

#include <map>

#include "SavefileState.h"
#include "ScoreState.h"
#include "OptionsState.h"
#include "Configuracion.h"
#include "ArchivoConfiguracion.h"
#include "Button.h"
#include "Sound.h"

class MainMenuState:public State{
private:
    ///TEXTURES
    std::map<const char*,sf::Texture*> mTextures;
    sf::Sprite background;

    ///BUTTONS
    Button btnStart;
    Button btnOptions;
    Button btnQuit;
    Button btnScore;


    ///MUSIC
    Sound mainMenuMusic;
    int timer;
public:
    ///Constructor / Destructor
    MainMenuState(sf::RenderWindow*, std::stack<State*>* states);
    virtual ~MainMenuState();

    ///Methods
    void updateAudio();
    void updateButtons(bool MBreleased);
    void renderButtons();

    void checkForQuit(bool MBreleased);
    void endState();
    void updateInput(const float& dt,bool MBrealeased);
    void update(const float& dt,bool MBrealeased,sf::Event event);
    void render(sf::RenderTarget *target = nullptr);

private:
    void initButtons();
    void initTextures();
    void initBackground();
    void initAudio();
};

#endif // MAINMENUSTATE_H_INCLUDED
